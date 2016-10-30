// Project includes
#include "Debug.h"
#include "cmssw/SiStripFecKey.h"
#include "cmssw/SiStripFedKey.h"
#include "FedView.h"
#include "TreeBuilder.h"
#include "frmtreeviewer.h"
#include "frmreferencechooser.h"
#include "frmruninfo.h"
#include "frmdetails.h"
#include "frmtkmap.h"
#include "frmfedmap.h"

// Qt includes
#include <QWhatsThis>
#include <QToolTip>
#include <QTextEdit>
#include <QSplitter>
#include <QScrollBar>
#include <QContextMenuEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QtSql/QSqlQuery>

// ROOT includes
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TEventList.h>
#include <TH1.h>
#include <TKey.h>
#include <TEnv.h>
#include <TStyle.h>
#include <TChain.h>
#include <TChainElement.h>

TreeViewer::TreeViewer(const QString& tmpfilename, bool useCache, QWidget* parent):
    QConnectedTabWidget(parent),
    useCachedTrees(useCache),
    invChecked(false),
    xBins(-1), yBins(-1), zBins(-1),
    treeInfo(tmpfilename),
    X(), Y(), Z(),
    curX(), curY(), curZ(),
    curDrawX(), curDrawY(), curDrawZ(),
    curRefX(false), curRefY(false), curRefZ(false),
    curDiffX(false), curDiffY(false), curDiffZ(false),
    sameRefRunType(false),
    xboundmin(0.), xboundmax(0.), yboundmin(0.), yboundmax(0.)
{
    setupUi(this); 
    qtCanvas->setContextMenuPolicy(Qt::NoContextMenu);
    qtCanvas->setTakeoverMouse(true);

    connect(qtCanvas, SIGNAL(selectSignal(QPoint, QPoint)), this, SLOT(catchSelect(QPoint, QPoint)));
    connect(qtCanvas, SIGNAL(zoomoutSignal()), this, SLOT(catchZoomout()));

    cmbCutOpt->addItem("select","select");
    cmbCutOpt->addItem("unselect","unselect");
    
    setDrawOptions(1);
    btnTkMap->setEnabled(true);

    clientFile = NULL;
}

TreeViewer::~TreeViewer() {
    if (clientFile != NULL) clientFile->Close();
}

void TreeViewer::closeEvent(QCloseEvent*) {
    if (clientFile != NULL) clientFile->Close();
    treeInfo.closeTree(false);
}

TCanvas* TreeViewer::getCanvas() { 
    return qtCanvas->GetCanvas(); 
}

void TreeViewer::updateCanvas() {
    this->getCanvas()->Modified();
    this->getCanvas()->Update();
}

bool TreeViewer::addRun(QString partitionName, QString runNumber, bool isCurrent) {

    if (runNumber.toInt() == sistrip::CURRENTSTATE || runNumber.toInt() == sistrip::LASTO2O) {
        btnGetSelected->setEnabled(false);
        btnRef->setEnabled(false);
        //btnTkMap->setEnabled(false);
    }
    else {
        btnGetSelected->setEnabled(true);
        btnRef->setEnabled(true);
        //btnTkMap->setEnabled(true);
    }

    QRunId runId(partitionName,runNumber);
    if (Debug::Inst()->getEnabled()) qDebug() << "Loading analysis for " << runId.first << ":" << runId.second;
    QString analysisTreeFilename = TreeBuilder::Inst()->loadAnalysis(runId, useCachedTrees);
    if(analysisTreeFilename == "") { 
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to load analysis " << runId.first << ":" << runId.second << " ... analysis may already be loaded or can't be accessed";
        return false;
    }
    QPair<QString, QString> treePath;
    treePath.first = analysisTreeFilename;
    treePath.second = "DBTree";

    treeInfo.buildTreeInfo(runId, treePath, isCurrent);
    TObjArray* branchList = ( isCurrent ? treeInfo.getCurrentTree()->GetListOfBranches() : treeInfo.getReferenceTree()->GetListOfBranches() );

    if (isCurrent) {
        if (selMap.size() != 0) selMap.clear();
        for (int i = 0; i < treeInfo.getCurrentTree()->GetEntries(); i++) selMap.push_back(0);

        if (varList.size() != 0) varList.clear();
        for(Int_t i = 0; i < branchList->GetEntries(); ++i ) {
            TBranch *branch = static_cast<TBranch*>(branchList->At(i));
            varList.push_back(QPair<QString, QString>(branch->GetName(), branch->GetClassName()));
        }

        fillBranchNames(true, 'x'); fillBranchNames(true, 'y'); fillBranchNames(true, 'z');

        if      (runNumber.toInt() == sistrip::CURRENTSTATE) btnRunInfo->setText(partitionName+QString(": Curr. DB State"));
        else if (runNumber.toInt() == sistrip::LASTO2O     ) btnRunInfo->setText(partitionName+QString(": Last O2O State"));
        else btnRunInfo->setText(partitionName+QString(": ")+runNumber);
        lblInfo->setText(QString("Tree with ")+QString::number(treeInfo.getCurrentTree()->GetEntries())+QString(" devices loaded"));

        fillSummaryHists(runNumber);
    }

    else {
        if (refVarList.size() != 0) refVarList.clear();
        for(Int_t i = 0; i < branchList->GetEntries(); ++i ) {
            TBranch *branch = static_cast<TBranch*>(branchList->At(i));
            refVarList.push_back(QPair<QString, QString>(branch->GetName(), branch->GetClassName()));
        }

        btnRef->setText("Ref: " + runId.second);
        
        chkDiffX->setEnabled(sameRefRunType); chkDiffY->setEnabled(sameRefRunType); chkDiffZ->setEnabled(sameRefRunType);
        chkRefX->setEnabled(true); chkRefY->setEnabled(true); chkRefZ->setEnabled(true);
        if (!sameRefRunType) {
            chkDiffX->setCheckState(Qt::Unchecked); chkDiffY->setCheckState(Qt::Unchecked); chkDiffZ->setCheckState(Qt::Unchecked);
        }

    }

    return true;
}

void TreeViewer::fillBranchNames(bool isCurrent, char axis) {
    if (Debug::Inst()->getEnabled()) qDebug() << "(Re)populating the variable list";

    if (axis == 'x') cmbX->clear();
    if (axis == 'y') cmbY->clear();
    if (axis == 'z') cmbZ->clear();

    if (axis == 'x') cmbX->addItem("(NONE)", QString(""));
    if (axis == 'y') cmbY->addItem("(NONE)", QString(""));
    if (axis == 'z') cmbZ->addItem("(NONE)", QString(""));
  
    if (isCurrent) { 
        if (varList.size() == 0) return;
        
        for(int i = 0; i < varList.size(); i++) {
            if (axis == 'x') cmbX->addItem(varList[i].first.toStdString().c_str(), varList[i].second.toStdString().c_str());
            if (axis == 'y') cmbY->addItem(varList[i].first.toStdString().c_str(), varList[i].second.toStdString().c_str());
            if (axis == 'z') cmbZ->addItem(varList[i].first.toStdString().c_str(), varList[i].second.toStdString().c_str());
        }
    }
    else { 
        if (refVarList.size() == 0) return;
        
        for(int i = 0; i < refVarList.size(); i++) {
            if (axis == 'x') cmbX->addItem(refVarList[i].first.toStdString().c_str(), refVarList[i].second.toStdString().c_str());
            if (axis == 'y') cmbY->addItem(refVarList[i].first.toStdString().c_str(), refVarList[i].second.toStdString().c_str());
            if (axis == 'z') cmbZ->addItem(refVarList[i].first.toStdString().c_str(), refVarList[i].second.toStdString().c_str());
        }
    }
}

void TreeViewer::fillSummaryHists(const QString& runNumber) {

    if (runNumber.toInt() == sistrip::CURRENTSTATE || runNumber.toInt() == sistrip::LASTO2O) return; 

    if (summaryHists.size() > 0) summaryHists.clear(); 
    btnShowSummary->setEnabled(false);
    cmbSummaryHists->setEnabled(false);

    TString filePath = Form("/opt/cmssw/Data/%d/SiStripCommissioningClient*.root", runNumber.toInt());
    TChain chain;
    chain.Add(filePath);
    TObjArray *fileElements=chain.GetListOfFiles();
    if (fileElements->GetEntries() > 1)  {
        if (Debug::Inst()->getEnabled()) qDebug() << "Multiple client files found for run " << runNumber;
        return;
    }        
    if (fileElements->GetEntries() == 0) {
        if (Debug::Inst()->getEnabled()) qDebug() << "No client file found for run " << runNumber;
        return;
    }        
    
    TIter thefile(fileElements);
    TChainElement* chEl= (TChainElement*)thefile();
    clientFile = TFile::Open(chEl->GetTitle());
    if (!clientFile || !clientFile->IsOpen()) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to open client file " << chEl->GetTitle();
        return;
    }        
    else {
        if (Debug::Inst()->getEnabled()) qDebug() << "Client file for run " << runNumber << " successfully opened";
    }   
    
    TDirectory *dir = clientFile->GetDirectory("/DQMData/Collate/SiStrip/ControlView");
    if (dir == NULL) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Directory /DQMData/Collate/SiStrip/ControlView does not exist in file" << ' ' << clientFile->GetName();
        return;
    }
    
    dir->cd();
    QString title = "SummaryHisto_Histo";
    TIter nextkey(dir->GetListOfKeys());
    TKey *key, *oldkey=0;
    while ((key = (TKey*)nextkey())) {
        if (oldkey && QString(oldkey->GetName()) != QString(key->GetName())) continue; 	    
        TObject *obj = key->ReadObj();
        if (obj) {
            QString temp(obj->GetName());
            if(temp.contains(title)) {
                TH1* hist = static_cast<TH1*>(obj);
                summaryHists.push_back(hist);
            } 
        } 
        if (Debug::Inst()->getEnabled()) qDebug() << "Object from key " << key->GetName() << " does not exist";
    } 
    
    if (summaryHists.size() == 0) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to find histogramm(s) for " << title; 
    }
    else {
        if (Debug::Inst()->getEnabled()) qDebug() << "Summary histograms loaded";
    }
        
    cmbSummaryHists->clear();
    if (summaryHists.size() > 0) {
        for (int i = 0; i < summaryHists.size(); i++) {
            std::string sumHistCmbName(summaryHists[i]->GetName());
            cmbSummaryHists->addItem(sumHistCmbName.substr(sumHistCmbName.find_last_of('_')+1).c_str(), summaryHists[i]->GetName());
        }
    }

    btnShowSummary->setEnabled(true);
    cmbSummaryHists->setEnabled(true);
}

void TreeViewer::draw(bool firstDraw, bool is1D) {
    gStyle->SetOptStat("mrie");
    gStyle->SetStatColor(0);
    double xcurrentmin = getCanvas()->PadtoX(getCanvas()->GetUxmin());            
    double xcurrentmax = getCanvas()->PadtoX(getCanvas()->GetUxmax() - 1e-6);            
    double ycurrentmin = getCanvas()->PadtoY(getCanvas()->GetUymin());            
    double ycurrentmax = getCanvas()->PadtoY(getCanvas()->GetUymax() - 1e-6); 

    TH1* oldh1 = (TH1*)gDirectory->Get("h1");
    if (oldh1) oldh1->Delete();
    TH1* oldh2 = (TH1*)gDirectory->Get("h2");
    if (oldh2) oldh2->Delete();

    lblInfo->setText(QString("Drawing: ")+curDrawX+QString(" ")+curDrawY+QString(" ")+curDrawZ);
    TTree* tree = NULL; 
    if (treeInfo.getCurrentTree()) tree = treeInfo.getCurrentTree();
    if (!tree) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to get hold of the tree";
        return;
    }

    if (firstDraw) {
        cutString = "";
        invChecked = chkShowInvalid->isChecked();
    }
    TEventList evtlist("eventList", "eventList");

    QString drawString = getDrawString("h1");
    if (Debug::Inst()->getEnabled()) {
        qDebug() << "CutString : " << cutString;
        qDebug() << "DrawString: " << drawString;
    }

    getCanvas()->cd();
    tree->SetMarkerStyle(7);
    tree->SetLineColor(kBlack);
    tree->SetMarkerColor(kBlack);
    tree->Draw(qPrintable(drawString), qPrintable(getInvalidCutString(invChecked)), qPrintable(drawOpt));

    TH1* h1 = static_cast<TH1*>(qtCanvas->GetCanvas()->GetPrimitive("h1"));
    QString xdiffstr = "";
    QString ydiffstr = "";
    if (chkDiffX->isChecked()) xdiffstr = "Diff ";
    if (chkDiffY->isChecked()) ydiffstr = "Diff ";

    if (!h1) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to extract histogram from the canvas ... quiting draw";
        return;
    }

    h1->GetXaxis()->SetTitle(qPrintable(xdiffstr + curX));
    if (!is1D) h1->GetYaxis()->SetTitle(qPrintable(ydiffstr + curY));

    if (!firstDraw) {
        h1->GetXaxis()->SetRangeUser(xcurrentmin, xcurrentmax);
        h1->GetYaxis()->SetRangeUser(ycurrentmin, ycurrentmax);

        QString drawSelectedString;
        if (is1D) drawSelectedString = getDrawString("h2", h1->GetNbinsX(), h1->GetBinLowEdge(1), h1->GetBinLowEdge(h1->GetNbinsX())+h1->GetBinWidth(h1->GetNbinsX()));
        else drawSelectedString = getDrawString("");
        if(Debug::Inst()->getEnabled()) {
            qDebug() << "Selection CutString : " << cutString;
            qDebug() << "Selection DrawString: " << drawSelectedString;
        }
        tree->Draw(">>evtlist", qPrintable(cutString + " && " + getInvalidCutString(invChecked)));
        evtlist.Add((TEventList*)gDirectory->Get("evtlist"));
        evtlist.Sort();
        for (int i = 0; i < selMap.size() ; i++) selMap[i] = 0;
        for (int i = 0; i < evtlist.GetN(); i++) selMap[evtlist.GetEntry(i)] = 1;
        tree->SetLineColor(kRed);
        tree->SetMarkerColor(kRed);
        tree->Draw(qPrintable(drawSelectedString), qPrintable(cutString + " && " + getInvalidCutString(invChecked)), qPrintable(drawOpt+" P SAME"));

        if (is1D) {
            TH1* h2 = static_cast<TH1*>(qtCanvas->GetCanvas()->GetPrimitive("h2"));
            h1->Draw(qPrintable(drawOpt));
            h2->Draw(qPrintable(drawOpt+" SAME"));
        }
    }

    updateCanvas();
    if (firstDraw) {
        xboundmin = getCanvas()->PadtoX(getCanvas()->GetUxmin());
        xboundmax = getCanvas()->PadtoX(getCanvas()->GetUxmax() - 1e-6);
        yboundmin = getCanvas()->PadtoY(getCanvas()->GetUymin());
        yboundmax = getCanvas()->PadtoY(getCanvas()->GetUymax() - 1e-6);
    }
}

QString TreeViewer::setText(const QString &text, char axis) {
    if (text == "(NONE)") return QString("");
    
    if (axis == 'x') {
        int index = cmbX->findText(text);
        if (index == -1) return QString("");
    
        QString data = cmbX->itemData(index).toString();
        if (data == QString("TObjString")) return QString(text)+QString(".fString");
        return text;
    }
    else if (axis == 'y') {
        int index = cmbY->findText(text);
        if (index == -1) return QString("");
    
        QString data = cmbY->itemData(index).toString();
        if (data == QString("TObjString")) return QString(text)+QString(".fString");
        return text;
    }
    else {
        int index = cmbZ->findText(text);
        if (index == -1) return QString("");
    
        QString data = cmbZ->itemData(index).toString();
        if (data == QString("TObjString")) return QString(text)+QString(".fString");
        return text;
    }
}

void TreeViewer::varChanged(const QString& text, QString &var, int &bins, QSpinBox *box, QLabel *label, char axis) {
    bool e = (text != "(NONE)");
    var = setText(text, axis);
    bins = -1;
    box->setEnabled(e); 
    label->setEnabled(e);
    box->setValue(-1); 
    
    int dim = 0;
    if (cmbX->currentText() != "(NONE)") ++dim;
    if (cmbY->currentText() != "(NONE)") ++dim;
    if (cmbZ->currentText() != "(NONE)") ++dim;
    setDrawOptions(dim);
}

void TreeViewer::setDrawOptions(int d) {
    cmbDrawOpt->clear();
    if (d == 1) {
        cmbDrawOpt->addItem("HIST");  
        cmbDrawOpt->addItem("E");     
        cmbDrawOpt->addItem("HISTTEXT");
    }
    else if (d == 2) {
        cmbDrawOpt->addItem("");
        cmbDrawOpt->addItem("COLZ");
    }
    else if (d == 3) {
        cmbDrawOpt->addItem("");
        cmbDrawOpt->addItem("COLZ");
    }
    return;
}

QString TreeViewer::getInvalidCutString(bool showInvalid) {
    QString cutstr = "(";
    if (!showInvalid) {
        if (!curX.contains("fString")) cutstr += QString("TMath::Abs(")+ curDrawX +QString(" - 65535) > 1e-6");
        else cutstr += "1";
        if (!curY.isEmpty() && !curY.contains("fString") ) cutstr += " && " +QString("TMath::Abs(")+ curDrawY +QString(" - 65535) > 1e-6");
        if (!curZ.isEmpty() && !curZ.contains("fString") ) cutstr += " && " +QString("TMath::Abs(")+ curDrawZ +QString(" - 65535) > 1e-6");
    }
    else cutstr += "1";
    
    cutstr += ")";

    return cutstr;
}

QString TreeViewer::getDimString(char axis) {

    QString base;
    QString dimstring;

    bool isDiffEnabled = false;
    bool isRefEnabled  = false;

    if (axis == 'x') {
        base = X;
        if (chkDiffX->isChecked()) isDiffEnabled = true;
        if (chkRefX ->isChecked()) isRefEnabled  = true;
    }        
    else if (axis == 'y') {
        base = Y;
        if (chkDiffY->isChecked()) isDiffEnabled = true;
        if (chkRefY ->isChecked()) isRefEnabled  = true;
    }        
    else {
        base = Z;
        if (chkDiffZ->isChecked()) isDiffEnabled = true;
        if (chkRefZ ->isChecked()) isRefEnabled  = true;
    }        

    dimstring = base;
    if (isRefEnabled) dimstring.prepend("ref.");
    if (isDiffEnabled && isRefEnabled) {
        dimstring.prepend("(");
        dimstring.append (QString(" - ") + base + ")");
    }
    if (isDiffEnabled && !isRefEnabled) {
        dimstring.prepend("(");
        dimstring.append (QString(" - ref.") + base + ")");
    }
    
    return dimstring;
}

QString TreeViewer::getDrawString(QString histname, unsigned int bins, double min, double max) {
    QString drawString = "";
    QString sep        = ":";
    QString binning    = "";

    if (!curY.isEmpty() && !curZ.isEmpty()) {
        drawString = curDrawY+sep+curDrawX+sep+curDrawZ;
        gEnv->SetValue("Hist.Binning.3D.x",yBins != -1 ? yBins : 20);
        gEnv->SetValue("Hist.Binning.3D.y",xBins != -1 ? xBins : 20);
        gEnv->SetValue("Hist.Binning.3D.z",zBins != -1 ? zBins : 20);
    } 
    else if (!curY.isEmpty() && curZ.isEmpty()){
        drawString = curDrawY+sep+curDrawX; 
        gEnv->SetValue("Hist.Binning.2D.x",xBins != -1 ? xBins : 40);
        gEnv->SetValue("Hist.Binning.2D.y",yBins != -1 ? yBins : 40);
    }   
    else {
        drawString = curDrawX;
        gEnv->SetValue("Hist.Binning.1D.x",xBins != -1 ? xBins : 100);
    }

    if (histname != "") {
        drawString += ">>";
        drawString += histname;
        if (bins > 0) {
            QString hists = "(";
            hists += bins;
            hists += ",";
            hists += min;
            hists += ",";
            hists += max;
            hists += ")";
            drawString += hists;
        }
    }

    return drawString;
}

void TreeViewer::on_btnDraw_clicked() {
    if ((X == "(NONE)" || X.isEmpty()) && (Y == "(NONE)" || Y.isEmpty()) && (Z == "(NONE)" || Z.isEmpty())) {
        if (Debug::Inst()->getEnabled()) qDebug() << "You need to select a variable to plot.";
        QMessageBox::warning(this, "Plotting Error", "You need to select a variable to plot.", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if ((X == "(NONE)" || X.isEmpty()) && ((Y != "(NONE)" && !Y.isEmpty()) || (Z != "(NONE)" && !Z.isEmpty()))) {
        if (Debug::Inst()->getEnabled()) qDebug() << "The x-axis needs to be always defined.";
        QMessageBox::warning(this, "Plotting Error", "The x-axis needs to be always defined.", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }        
    if ((X != "(NONE)" && !X.isEmpty()) && (Y == "(NONE)" || Y.isEmpty()) && (Z != "(NONE)" && !Z.isEmpty())) {
        if (Debug::Inst()->getEnabled()) qDebug() << "The y-axis needs to be defined for a 2D plot.";
        QMessageBox::warning(this, "Plotting Error", "The y-axis needs to be defined for a 2D plot.", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }        

    curX = X;
    curY = Y;
    curZ = Z;

    curDrawX = getDimString('x');
    curDrawY = getDimString('y');
    curDrawZ = getDimString('z');

    curRefX = chkRefX->isChecked();
    curRefY = chkRefY->isChecked();
    curRefZ = chkRefZ->isChecked();

    curDiffX = chkDiffX->isChecked();
    curDiffY = chkDiffY->isChecked();
    curDiffZ = chkDiffZ->isChecked();

    if (!treeInfo.getCurrentTree() || selMap.size() != treeInfo.getCurrentTree()->GetEntries()) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to setup the selection map";
        return;
    }
    else {
        for (int i = 0; i < selMap.size(); i++) selMap[i] = 0;
    }

    if ((Y != "(NONE)" && !Y.isEmpty()) || (Z != "(NONE)" && !Z.isEmpty())) qtCanvas->setLockY(false);
    else qtCanvas->setLockY(true);

    drawOpt = cmbDrawOpt->currentText(); 

    draw(true, (Y == "(NONE)" || Y.isEmpty()) && (Z == "(NONE)" || Z.isEmpty()));

    btnPrintToFile->setEnabled(true);
    if (treeInfo.getCurrentRunNumber().toInt() != sistrip::CURRENTSTATE && treeInfo.getCurrentRunNumber().toInt() != sistrip::LASTO2O) btnGetSelected->setEnabled(true);
    cmbCutOpt->setEnabled(true);
    chkSelMode->setEnabled(true);
}

void TreeViewer::on_btnRef_clicked() {
    if (treeInfo.getCurrentRunNumber().isEmpty() || treeInfo.getCurrentPartition().isEmpty()) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to get the ID of the current run";
        return;
    }        

    ReferenceChooser* refchooser = new ReferenceChooser();
    refchooser->addReferenceRuns(treeInfo.getCurrentPartition(), treeInfo.getCurrentRunNumber());
    connect(refchooser, SIGNAL(refSignal(QString, QString, bool)), this, SLOT(catchRef(QString, QString, bool)));
    refchooser->show();
}

void TreeViewer::on_btnShowSummary_clicked() {
    if (summaryHists.size() == 0) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to find summary histogramm(s)"; 
    }
    else {
        getCanvas()->cd();
        for (int i = 0; i < summaryHists.size(); i++) {
            if (cmbSummaryHists->itemData(cmbSummaryHists->currentIndex()).toString() == summaryHists[i]->GetName()) summaryHists[i]->Draw();   
        }
        updateCanvas();
    }
    btnPrintToFile->setEnabled(true);
    if (chkSelMode->isChecked()) chkSelMode->setCheckState(Qt::Unchecked);
    chkSelMode->setEnabled(false);
    btnGetSelected->setEnabled(false);
    cmbCutOpt->setEnabled(false);
}

void TreeViewer::on_btnPrintToFile_clicked() {
    char* curDir;
    curDir = getenv("PWD");
    QString saveFileName = (QFileDialog::getSaveFileName(this, tr("Save Image"), curDir, tr("Image files (*.png *.jpg)")));
    if (Debug::Inst()->getEnabled()) qDebug() << saveFileName;
    if (saveFileName == NULL) return;
    else getCanvas()->Print(saveFileName.toStdString().c_str());
}

void TreeViewer::on_btnRunInfo_clicked() {
    if (treeInfo.getCurrentRunNumber().toInt() != sistrip::CURRENTSTATE && treeInfo.getCurrentRunNumber().toInt() != sistrip::LASTO2O) {
        RunInfo* runInfo = new RunInfo();
        runInfo->setCurrentRun(treeInfo.getCurrentRunNumber());
        runInfo->displayRunInfo();
        emit showTabSignal(runInfo, "Run Info");
    }
}

void TreeViewer::on_btnGetSelected_clicked() {
    TTree* tree = NULL; 
    if (treeInfo.getCurrentTree()) tree = treeInfo.getCurrentTree();
    if (!tree) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to get hold of the tree";
        return;
    }
    QVector<int> smap;
    if (selMap.size() > 0) smap = selMap;   
    else {
        if (Debug::Inst()->getEnabled()) qDebug() << "Invalid selection map";
        return;
    }

    SelectionDetails* details = new SelectionDetails(NULL, treeInfo);
    details->populate(tree, smap, curX);
    emit showTabSignal(details, "Selection Info");
}

void TreeViewer::on_cmbX_currentIndexChanged(const QString & text) { 
    varChanged(text, X, xBins, xSpinBins, lblXBins, 'x'); 
}

void TreeViewer::on_cmbY_currentIndexChanged(const QString & text) { 
    varChanged(text, Y, yBins, ySpinBins, lblYBins, 'y'); 
}

void TreeViewer::on_cmbZ_currentIndexChanged(const QString & text) { 
    varChanged(text, Z, zBins, zSpinBins, lblZBins, 'z'); 
}

void TreeViewer::on_xSpinBins_valueChanged(int bins) { 
    xBins = bins; 
}

void TreeViewer::on_ySpinBins_valueChanged(int bins) { 
    yBins = bins; 
}

void TreeViewer::on_zSpinBins_valueChanged(int bins) { 
    zBins = bins; 
}

void TreeViewer::on_chkLogX_stateChanged(int state) {
    if (state == Qt::Unchecked) getCanvas()->SetLogx(0);
    else getCanvas()->SetLogx(1);

    xboundmin = getCanvas()->PadtoX(getCanvas()->GetUxmin());            
    xboundmax = getCanvas()->PadtoX(getCanvas()->GetUxmax() - 1e-6);            
    yboundmin = getCanvas()->PadtoY(getCanvas()->GetUymin());            
    yboundmax = getCanvas()->PadtoY(getCanvas()->GetUymax() - 1e-6); 

    updateCanvas();
}

void TreeViewer::on_chkLogY_stateChanged(int state) {
    if (state == Qt::Unchecked) getCanvas()->SetLogy(0);
    else {
        TH1* h1 = static_cast<TH1*>(qtCanvas->GetCanvas()->GetPrimitive("h1"));
        if (h1 != NULL && yboundmin == 0) h1->GetYaxis()->SetRangeUser(1e-1, yboundmax);
        getCanvas()->SetLogy(1);
    }

    xboundmin = getCanvas()->PadtoX(getCanvas()->GetUxmin());            
    xboundmax = getCanvas()->PadtoX(getCanvas()->GetUxmax() - 1e-6);            
    yboundmin = getCanvas()->PadtoY(getCanvas()->GetUymin());            
    yboundmax = getCanvas()->PadtoY(getCanvas()->GetUymax() - 1e-6); 

    updateCanvas();
}

void TreeViewer::on_chkLogZ_stateChanged(int state) {
    if (state == Qt::Unchecked) getCanvas()->SetLogz(0);
    else getCanvas()->SetLogz(1);
    updateCanvas();
}

void TreeViewer::on_chkRefX_stateChanged(int state) {
    if (state != Qt::Unchecked) fillBranchNames(false, 'x');
    else fillBranchNames(true, 'x');
}

void TreeViewer::on_chkRefY_stateChanged(int state) {
    if (state != Qt::Unchecked) fillBranchNames(false, 'y');
    else fillBranchNames(true, 'y');
}

void TreeViewer::on_chkRefZ_stateChanged(int state) {
    if (state != Qt::Unchecked) fillBranchNames(false, 'z');
    else fillBranchNames(true, 'z');
}

void TreeViewer::catchRef(QString refpart, QString refrun, bool sametype) {
    if (Debug::Inst()->getEnabled()) qDebug() << "Ref. Partition : " << refpart << ", Ref. run: " << refrun;
    sameRefRunType = sametype;
    if (!refpart.isEmpty() && !refrun.isEmpty()) addRun(refpart, refrun, false);
}

void TreeViewer::catchSelect(QPoint origin, QPoint endpoint) {
    if (!chkSelMode->isChecked()) {
        double xmin = getCanvas()->AbsPixeltoX(origin.x() < endpoint.x() ? origin.x() : endpoint.x());
        double xmax = getCanvas()->AbsPixeltoX(origin.x() > endpoint.x() ? origin.x() : endpoint.x());

        double ymin =  getCanvas()->AbsPixeltoY(origin.y());
        double ymax =  getCanvas()->AbsPixeltoY(endpoint.y());

        if (ymin > ymax) {
            double ytmp = ymin;
            ymin = ymax;
            ymax = ytmp;
        }

        if (getCanvas()->GetLogx()) {
            xmin = getCanvas()->PadtoX(xmin);
            xmax = getCanvas()->PadtoX(xmax);
        }

        if (getCanvas()->GetLogy()) {
            ymin = getCanvas()->PadtoY(ymin);
            ymax = getCanvas()->PadtoY(ymax);
        }

        if (xmin == xmax || ymin == ymax) return;
        else {
            TH1* h1 = static_cast<TH1*>(qtCanvas->GetCanvas()->GetPrimitive("h1"));
            if (h1) {
                h1->GetXaxis()->SetRangeUser(xmin, xmax);
                h1->GetYaxis()->SetRangeUser(ymin, ymax);
                updateCanvas();
                return;
            }
        }
        return;
    }        

    if (curX.toStdString().find("fString") != std::string::npos) return;

    if (drawOpt == "COLZ") return;

    if ((curY == "(NONE)" || curY.isEmpty()) && (curZ == "(NONE)" || curZ.isEmpty())) {
        double xmin = getCanvas()->AbsPixeltoX(origin.x() < endpoint.x() ? origin.x() : endpoint.x());
        double xmax = getCanvas()->AbsPixeltoX(origin.x() > endpoint.x() ? origin.x() : endpoint.x());
        if (getCanvas()->GetLogx()) {
            xmin = getCanvas()->PadtoX(xmin);
            xmax = getCanvas()->PadtoX(xmax);
        }

        TH1* hist = (TH1*)getCanvas()->GetPrimitive("h1");
        if (!hist) {
            if (Debug::Inst()->getEnabled()) qDebug() << "Unable to get hold of the histogram";
            return;
        }

        double xminedge = hist->GetBinLowEdge(hist->FindBin(xmin));
        double xmaxedge = hist->GetBinLowEdge(hist->FindBin(xmax)) + hist->GetBinWidth(hist->FindBin(xmax));

        if (xmin == xmax) return;

        if (Debug::Inst()->getEnabled()) qDebug() << curX << "[" << xminedge << ", " << xmaxedge << ")";

        QString varx, cvarx, rvarx;
        cvarx = curX.toStdString().c_str();
        rvarx = QString("ref.") + curX.toStdString().c_str();

        if      ( curRefX &&  curDiffX) varx = "(" + rvarx + " - " + cvarx + ")";
        else if ( curRefX && !curDiffX) varx = rvarx;
        else if (!curRefX &&  curDiffX) varx = "(" + cvarx + " - " + rvarx + ")";
        else                            varx = cvarx;

        cutString.prepend("(");
        if (cmbCutOpt->currentText() == "select") {
            if (cutString != "(") cutString += " || ";
            cutString += "(" + varx + " >= " + QString::number(xminedge) + " && " + varx + " < "  + QString::number(xmaxedge) + ")";
        }
        else {
            if (cutString != "(") cutString += " && ";
            cutString += "(" + varx + " < "  + QString::number(xminedge) + " || " + varx + " >= " + QString::number(xmaxedge) + ")";
        }
        cutString += ")";

        draw(false, true);
    }

    else if (curY != "(NONE)" && !curY.isEmpty()) {
        double xmin = getCanvas()->AbsPixeltoX(origin.x() < endpoint.x() ? origin.x() : endpoint.x());
        double xmax = getCanvas()->AbsPixeltoX(origin.x() > endpoint.x() ? origin.x() : endpoint.x());

        double ymin =  getCanvas()->AbsPixeltoY(origin.y());
        double ymax =  getCanvas()->AbsPixeltoY(endpoint.y());

        if (ymin > ymax) {
            double ytmp = ymin;
            ymin = ymax;
            ymax = ytmp;
        }

        if (getCanvas()->GetLogx()) {
            xmin = getCanvas()->PadtoX(xmin);
            xmax = getCanvas()->PadtoX(xmax);
        }

        if (getCanvas()->GetLogy()) {
            ymin = getCanvas()->PadtoY(ymin);
            ymax = getCanvas()->PadtoY(ymax);
        }

        if (xmin == xmax || ymin == ymax) return;

        if (Debug::Inst()->getEnabled()) qDebug() << curX << "[" << xmin << ", " << xmax << ")";
        if (Debug::Inst()->getEnabled()) qDebug() << curY << "[" << ymin << ", " << ymax << ")";

        QString varx, cvarx, rvarx;
        QString vary, cvary, rvary;
        cvarx = curX.toStdString().c_str();
        cvary = curY.toStdString().c_str();
        rvarx = QString("ref.") + curX.toStdString().c_str();
        rvary = QString("ref.") + curY.toStdString().c_str();

        if      ( curRefX &&  curDiffX) varx = "(" + rvarx + " - " + cvarx + ")";
        else if ( curRefX && !curDiffX) varx = rvarx;
        else if (!curRefX &&  curDiffX) varx = "(" + cvarx + " - " + rvarx + ")";
        else                            varx = cvarx;

        if      ( curRefY &&  curDiffY) vary = "(" + rvary + " - " + cvary + ")";
        else if ( curRefY && !curDiffY) vary = rvary;
        else if (!curRefY &&  curDiffY) vary = "(" + cvary + " - " + rvary + ")";
        else                            vary = cvary;

        cutString.prepend("(");
        if (cmbCutOpt->currentText() == "select") {
            if (cutString != "(") cutString += " || ";
            cutString += "(";
            cutString += varx + " >= " + QString::number(xmin) + " && " + varx + " < "  + QString::number(xmax);
            cutString += " && ";
            cutString += vary + " >= " + QString::number(ymin) + " && " + vary + " < "  + QString::number(ymax);
            cutString += ")";
        }
        else {
            if (cutString != "(") cutString += " && ";
            cutString += "(";
            cutString += varx + " < "  + QString::number(xmin) + " || " + varx + " >= " + QString::number(xmax);
            cutString += " || ";
            cutString += vary + " < "  + QString::number(ymin) + " || " + vary + " >= " + QString::number(ymax);
            cutString += ")";
        }
        cutString += ")";
        draw(false, false);
    }
}

void TreeViewer::catchZoomout() {
    if (xboundmin == xboundmax || yboundmin == yboundmax) return;

    TH1* h1 = static_cast<TH1*>(qtCanvas->GetCanvas()->GetPrimitive("h1"));
    if (h1) {
        if (xboundmin != getCanvas()->PadtoX(getCanvas()->GetUxmin()) || xboundmax != getCanvas()->PadtoX(getCanvas()->GetUxmax()) - 1e-6) h1->GetXaxis()->SetRangeUser(xboundmin, xboundmax);
        if (yboundmin != getCanvas()->PadtoY(getCanvas()->GetUymin()) || yboundmax != getCanvas()->PadtoY(getCanvas()->GetUymax()) - 1e-6) h1->GetYaxis()->SetRangeUser(yboundmin, yboundmax);
        updateCanvas();
        return;
    }
}

void TreeViewer::on_btnTkMap_clicked() {
    if (curX == "") {
        QMessageBox::warning(this, "Tracker Map Error", "You need to draw a variable before making the tracker map", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    TkMap* tkmap = new TkMap(0, treeInfo.getCurrentTree(), selMap, curX, xboundmin, xboundmax, treeInfo.getCurrentRunNumber());
    emit showTabSignal(tkmap, "Tracker Map");
}

void TreeViewer::on_btnFedMap_clicked() {
    TTree* tree = NULL; 
    if (treeInfo.getCurrentTree()) tree = treeInfo.getCurrentTree();
    if (!tree) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to get hold of the tree";
        return;
    }
    QVector<int> smap;
    if (selMap.size() > 0) smap = selMap;   
    else {
        if (Debug::Inst()->getEnabled()) qDebug() << "Invalid selection map";
        return;
    }

    FedMap* fmap = new FedMap(smap, QPair<QString, QString>(treeInfo.getCurrentPartition(), treeInfo.getCurrentRunNumber()), tree);
    emit showTabSignal(fmap, "FED Map");
}

