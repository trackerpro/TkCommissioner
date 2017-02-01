#include "Debug.h"
#include "frmtreeviewer.h"
#include "frmdetails.h"
#include "frmtkmap.h"

#include <QWhatsThis>
#include <QToolTip>
#include <QTextEdit>
#include <QSplitter>
#include <QScrollBar>
#include <QContextMenuEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>


#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TCutG.h>
#include <TEventList.h>
#include <TH1.h>
#include <TKey.h>
#include <TEnv.h>
#include <TChain.h>
#include <TChainElement.h>
#include <THStack.h>

#include <set>
#include <iostream>
#include <sstream>

TreeViewer::TreeViewer(QWidget* parent):
    QConnectedTabWidget(parent),
    xBins(-1), yBins(-1), zBins(-1),
    X(), Y(), Z(),
    curX(), curY(), curZ(),
    curDrawX(), curDrawY(), curDrawZ(),
    curRefX(false), curRefY(false), curRefZ(false),
    curDiffX(false), curDiffY(false), curDiffZ(false),
    xboundmin(0.), xboundmax(0.), yboundmin(0.), yboundmax(0.)
{
    setupUi(this); 
    qtCanvas->setContextMenuPolicy(Qt::NoContextMenu);
    qtCanvas->setTakeoverMouse(true);

    connect(qtCanvas, SIGNAL(selectSignal(QPoint, QPoint)), this, SLOT(catchSelect(QPoint, QPoint)));
    connect(qtCanvas, SIGNAL(zoomoutSignal()), this, SLOT(catchZoomout()));

    cmbCutOpt->addItem("select","select");
    cmbCutOpt->addItem("unselect","unselect");
    
    setDrawOptions(_1D);

    btnRef->setEnabled(false);
}

TreeViewer::~TreeViewer() {
}

void TreeViewer::closeEvent(QCloseEvent*) {
    freeTrees();
}

TCanvas* TreeViewer::getCanvas() { 
    return qtCanvas->GetCanvas(); 
}

void TreeViewer::update() {
    this->getCanvas()->Modified();
    this->getCanvas()->Update();
}

bool TreeViewer::setTree(const QString& tmpFileName_, std::vector<QPair<QString, QString> > treePaths_) {
    if (treePaths_.size() == 0) return false;

    treebuilder.buildTree(tmpFileName_, treePaths_);
    if (treebuilder.getCurrentTree()   == NULL) return false;

    TObjArray* branchList = treebuilder.getCurrentTree()->GetListOfBranches();
    if (varList.size() != 0) varList.clear();
    for(Int_t i = 0; i < branchList->GetEntries(); ++i ) {
        TBranch *branch = static_cast<TBranch*>(branchList->At(i));
        QString branchName(branch->GetName());
        QString branchClassName(branch->GetClassName());
        varList.push_back(QPair<QString, QString>(branchName, branchClassName));
    }

    chkRefX ->setEnabled(false);
    chkRefY ->setEnabled(false);
    chkRefZ ->setEnabled(false);

    fillBranchNames(true, _dimX);
    fillBranchNames(true, _dimY);
    fillBranchNames(true, _dimZ);

    lblInfo->setText(QString("Tree with ")+QString::number(treebuilder.getCurrentTree()->GetEntries())+QString(" entries loaded"));

    if (treePaths_.size() == 1) return true;

    if (treebuilder.getReferenceTree() == NULL) {
        if (treePaths_[1].first == "" || treePaths_[1].second == "") return true;
        else return false;
    }        

    TObjArray* refBranchList = treebuilder.getReferenceTree()->GetListOfBranches();
    if (refVarList.size() != 0) refVarList.clear();
    for(Int_t i = 0; i < refBranchList->GetEntries(); ++i ) {
        TBranch *branch = static_cast<TBranch*>(refBranchList->At(i));
        QString branchName(branch->GetName());
        QString branchClassName(branch->GetClassName());
        refVarList.push_back(QPair<QString, QString>(branchName, branchClassName));
    }

    chkRefX ->setEnabled(true);
    chkRefY ->setEnabled(true);
    chkRefZ ->setEnabled(true);

    if (treebuilder.isRefTreeTypeSame()) {
        chkDiffX->setEnabled(true);
        chkDiffY->setEnabled(true);
        chkDiffZ->setEnabled(true);
    }        
    else {
        chkDiffX->setEnabled(false);
        chkDiffY->setEnabled(false);
        chkDiffZ->setEnabled(false);
    }

    return true;
}

void TreeViewer::freeTrees() {
    treebuilder.closeTree(false);
}

void TreeViewer::fillBranchNames(bool isCurrent, unsigned int axis) {
    if(Debug::Inst()->getEnabled()) std::cout << "(Re)populating the variable list" << std::endl;

    if (axis == _dimX) cmbX->clear();
    if (axis == _dimY) cmbY->clear();
    if (axis == _dimZ) cmbZ->clear();

    if (axis == _dimX) cmbX->addItem(none, QString(""));
    if (axis == _dimY) cmbY->addItem(none, QString(""));
    if (axis == _dimZ) cmbZ->addItem(none, QString(""));
   
    if (isCurrent) {   
        for(std::size_t i = 0; i < varList.size(); i++) {
            if (axis == _dimX) cmbX->addItem(varList[i].first.toStdString().c_str(), varList[i].second.toStdString().c_str());
            if (axis == _dimY) cmbY->addItem(varList[i].first.toStdString().c_str(), varList[i].second.toStdString().c_str());
            if (axis == _dimZ) cmbZ->addItem(varList[i].first.toStdString().c_str(), varList[i].second.toStdString().c_str());
        }
    }
    else {
        for(std::size_t i = 0; i < refVarList.size(); i++) {
            if (axis == _dimX) cmbX->addItem(refVarList[i].first.toStdString().c_str(), varList[i].second.toStdString().c_str());
            if (axis == _dimY) cmbY->addItem(refVarList[i].first.toStdString().c_str(), varList[i].second.toStdString().c_str());
            if (axis == _dimZ) cmbZ->addItem(refVarList[i].first.toStdString().c_str(), varList[i].second.toStdString().c_str());
        }
    }
}

void TreeViewer::draw(bool firstDraw, bool is1D) {
    double xcurrentmin = getCanvas()->PadtoX(getCanvas()->GetUxmin());            
    double xcurrentmax = getCanvas()->PadtoX(getCanvas()->GetUxmax() - 1e-6);            
    double ycurrentmin = getCanvas()->PadtoY(getCanvas()->GetUymin());            
    double ycurrentmax = getCanvas()->PadtoY(getCanvas()->GetUymax() - 1e-6); 

    TH1* oldh1 = (TH1*)gDirectory->Get("h1");
    if (oldh1) oldh1->Delete();
    TH1* oldh2 = (TH1*)gDirectory->Get("h2");
    if (oldh2) oldh2->Delete();

    TTree* tree = treebuilder.getCurrentTree(); 
    if (!tree) {
        std::cerr << "Unable to get hold of the tree" << std::endl;
        return;
    }

    if (firstDraw) cutString = "";
    treebuilder.getEventList()->Reset();

    QString drawString = getDrawString("h1");
    if(Debug::Inst()->getEnabled()) std::cout << "DrawString: " << drawString.toStdString() << std::endl;
    lblInfo->setText(QString("Drawing: ")+getDrawString(""));

    treebuilder.useEventList(false);
    tree->SetMarkerStyle(7);
    tree->SetLineColor(kBlack);
    tree->SetLineWidth(2);
    tree->SetMarkerColor(kBlack);
    tree->Draw(qPrintable(drawString), "(1)", qPrintable(drawOpt));

    TH1* h1 = static_cast<TH1*>(qtCanvas->GetCanvas()->GetPrimitive("h1"));
    h1->GetXaxis()->SetTitle(qPrintable(curX));
    if (!is1D) h1->GetYaxis()->SetTitle(qPrintable(curY)); 

    if (!firstDraw) {
        h1->GetXaxis()->SetRangeUser(xcurrentmin, xcurrentmax);
        h1->GetYaxis()->SetRangeUser(ycurrentmin, ycurrentmax);

        QString drawSelectedString;
        if (is1D) drawSelectedString = getDrawString("h2", h1->GetNbinsX(), h1->GetBinLowEdge(1), h1->GetBinLowEdge(h1->GetNbinsX())+h1->GetBinWidth(h1->GetNbinsX())); 
        else drawSelectedString = getDrawString("");
        if(Debug::Inst()->getEnabled()) {
            std::cout << "Selection CutString : " << cutString.toStdString()  << std::endl;
            std::cout << "Selection DrawString: " << drawSelectedString.toStdString() << std::endl;
        } 
        tree->Draw(">>evtlist", qPrintable(cutString));
        TEventList *evtlist = (TEventList*)gDirectory->Get("evtlist");
        if (evtlist) evtlist->Sort();
        if (treebuilder.getEventList()) treebuilder.getEventList()->Sort();
        treebuilder.getEventList()->Add(evtlist);
        tree->SetLineColor(kRed);
        tree->SetLineWidth(2);
        tree->SetMarkerColor(kRed);
        tree->Draw(qPrintable(drawSelectedString), qPrintable(cutString), qPrintable(drawOpt+" P SAME"));
        
        if (is1D) {
            TH1* h2 = static_cast<TH1*>(qtCanvas->GetCanvas()->GetPrimitive("h2"));
            h1->Draw(qPrintable(drawOpt));
            h2->Draw(qPrintable(drawOpt+" SAME"));
        }
    }

    update();
    if (firstDraw) {
        xboundmin = getCanvas()->PadtoX(getCanvas()->GetUxmin());            
        xboundmax = getCanvas()->PadtoX(getCanvas()->GetUxmax() - 1e-6);            
        yboundmin = getCanvas()->PadtoY(getCanvas()->GetUymin());            
        yboundmax = getCanvas()->PadtoY(getCanvas()->GetUymax() - 1e-6);
    }
}

QString TreeViewer::setText(const QString &text, unsigned int axis) {
    if (text == none) return QString("");
    
    if (axis == _dimX) {
        int index = cmbX->findText(text);
        if (index == -1) return QString("");
    
        QString data = cmbX->itemData(index).toString();
        if (data == QString("TObjString")) return QString(text)+QString(".fString");
        return text;
    }
    else if (axis == _dimY) {
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

void TreeViewer::varChanged(const QString& text, QString &var, int &bins, QSpinBox *box, QLabel *label, unsigned int axis) {
    bool e = (text != none);
    var = setText(text, axis);
    bins = -1;
    box->setEnabled(e); 
    label->setEnabled(e);
    box->setValue(-1); 
    
    Dimension dim = 0;
    if (cmbX->currentText() != none) ++dim;
    if (cmbY->currentText() != none) ++dim;
    if (cmbZ->currentText() != none) ++dim;
    setDrawOptions(dim);
}

void TreeViewer::setDrawOptions(Dimension d) {
    cmbDrawOpt->clear();
    if (d == _1D) {
        cmbDrawOpt->addItem("HIST");  
        cmbDrawOpt->addItem("E");     
        cmbDrawOpt->addItem("HISTTEXT");
    }
    else if (d == _2D) {
        cmbDrawOpt->addItem("");
        cmbDrawOpt->addItem("COLZ");
    }
    else if (d == _3D) {
        cmbDrawOpt->addItem("");
        cmbDrawOpt->addItem("COLZ");
    }
    return;
}

QString TreeViewer::getDimString(unsigned int axis) {
    QString base;
    QString dimstring;

    bool isDiffEnabled = false;
    bool isRefEnabled  = false;

    if (axis == _dimX) {
        base = X;
        if (chkDiffX->isChecked()) isDiffEnabled = true;
        if (chkRefX ->isChecked()) isRefEnabled  = true;
    }        
    else if (axis == _dimY) {
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
            std::stringstream histss;
            histss << "(" << bins << "," << min << "," << max << ")";
            drawString += histss.str().c_str();
        }
    }

    return drawString;
}

void TreeViewer::on_btnDraw_clicked() {
    if ((X == none || X.isEmpty()) && (Y == none || Y.isEmpty()) && (Z == none || Z.isEmpty())) {
        if(Debug::Inst()->getEnabled()) std::cout << "You need to select a variable to plot." << std::endl;
        QMessageBox::warning(this, "Plotting Error", "You need to select a variable to plot.", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if ((X == none || X.isEmpty()) && ((Y != none && !Y.isEmpty()) || (Z != none && !Z.isEmpty()))) {
        if(Debug::Inst()->getEnabled()) std::cout << "The x-axis needs to be always defined." << std::endl;
        QMessageBox::warning(this, "Plotting Error", "The x-axis needs to be always defined.", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }        
    if ((X != none && !X.isEmpty()) && (Y == none || Y.isEmpty()) && (Z != none && !Z.isEmpty())) {
        if(Debug::Inst()->getEnabled()) std::cout << "The y-axis needs to be defined for a 2D plot." << std::endl;
        QMessageBox::warning(this, "Plotting Error", "The y-axis needs to be defined for a 2D plot.", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }        

    curX = X;
    curY = Y;
    curZ = Z;

    curDrawX = getDimString(_dimX);
    curDrawY = getDimString(_dimY);
    curDrawZ = getDimString(_dimZ);

    curRefX = chkRefX->isChecked();
    curRefY = chkRefY->isChecked();
    curRefZ = chkRefZ->isChecked();

    curDiffX = chkDiffX->isChecked();
    curDiffY = chkDiffY->isChecked();
    curDiffZ = chkDiffZ->isChecked();

    if ((Y != none && !Y.isEmpty()) || (Z != none && !Z.isEmpty())) qtCanvas->setLockY(false);
    else qtCanvas->setLockY(true);

    drawOpt = cmbDrawOpt->currentText(); 

    draw(true, (Y == none || Y.isEmpty()) && (Z == none || Z.isEmpty()));

    btnPrintToFile->setEnabled(true);
    btnGetSelected->setEnabled(true);
    cmbCutOpt->setEnabled(true);
    chkSelMode->setEnabled(true);
}

void TreeViewer::on_btnPrintToFile_clicked() {
    char* curDir;
    curDir = getenv("PWD");
    QString saveFileName = (QFileDialog::getSaveFileName(this, tr("Save Image"), curDir, tr("Image files (*.png *.jpg)")));
    if(Debug::Inst()->getEnabled()) std::cout << saveFileName.toStdString() << std::endl;
    if (saveFileName == NULL) return;
    else getCanvas()->Print(saveFileName.toStdString().c_str());
}

void TreeViewer::on_cmbX_currentIndexChanged(const QString & text) { 
    varChanged(text, X, xBins, xSpinBins, lblXBins, _dimX); 
}

void TreeViewer::on_cmbY_currentIndexChanged(const QString & text) { 
    varChanged(text, Y, yBins, ySpinBins, lblYBins, _dimY); 
}

void TreeViewer::on_cmbZ_currentIndexChanged(const QString & text) { 
    varChanged(text, Z, zBins, zSpinBins, lblZBins, _dimZ); 
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

    update();
}

void TreeViewer::on_chkLogY_stateChanged(int state) {
    if (state == Qt::Unchecked) getCanvas()->SetLogy(0);
    else {
        TH1* h1 = static_cast<TH1*>(qtCanvas->GetCanvas()->GetPrimitive("h1"));
        if (yboundmin == 0) h1->GetYaxis()->SetRangeUser(1e-1, yboundmax);
        getCanvas()->SetLogy(1);
    }        

    xboundmin = getCanvas()->PadtoX(getCanvas()->GetUxmin());            
    xboundmax = getCanvas()->PadtoX(getCanvas()->GetUxmax() - 1e-6);            
    yboundmin = getCanvas()->PadtoY(getCanvas()->GetUymin());            
    yboundmax = getCanvas()->PadtoY(getCanvas()->GetUymax() - 1e-6); 

    update();
}

void TreeViewer::on_chkLogZ_stateChanged(int state) {
    if (state == Qt::Unchecked) getCanvas()->SetLogz(0);
    else getCanvas()->SetLogz(1);
    update();
}

void TreeViewer::on_chkRefX_stateChanged(int state) {
    if (state != Qt::Unchecked) fillBranchNames(false, _dimX);
    else fillBranchNames(true, _dimX);
}

void TreeViewer::on_chkRefY_stateChanged(int state) {
    if (state != Qt::Unchecked) fillBranchNames(false, _dimY);
    else fillBranchNames(true, _dimY);
}

void TreeViewer::on_chkRefZ_stateChanged(int state) {
    if (state != Qt::Unchecked) fillBranchNames(false, _dimZ);
    else fillBranchNames(true, _dimZ);
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
                update();
                return;
            }
        }
        return;
    }        

    if (curX.toStdString().find("fString") != std::string::npos) return;

    if (drawOpt == "COLZ") return;

    if ((curY == none || curY.isEmpty()) && (curZ == none || curZ.isEmpty())) {
        double xmin = getCanvas()->AbsPixeltoX(origin.x() < endpoint.x() ? origin.x() : endpoint.x());
        double xmax = getCanvas()->AbsPixeltoX(origin.x() > endpoint.x() ? origin.x() : endpoint.x());
        if (getCanvas()->GetLogx()) {
            xmin = getCanvas()->PadtoX(xmin);
            xmax = getCanvas()->PadtoX(xmax);
        }

        TH1* hist = (TH1*)getCanvas()->GetPrimitive("h1");
        if (!hist) {
            std::cerr << "Unable to get hold of the histogram" << std::endl;
            return;
        }
        
        double xminedge = hist->GetBinLowEdge(hist->FindBin(xmin));
        double xmaxedge = hist->GetBinLowEdge(hist->FindBin(xmax)) + hist->GetBinWidth(hist->FindBin(xmax));
        
        if (xmin == xmax) return;
        
        if(Debug::Inst()->getEnabled()) std::cout << curX.toStdString() << "[" << xminedge << ", " << xmaxedge << ")" << std::endl;
        
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
    else if (curY != none && !curY.isEmpty()) {
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
        
        if(Debug::Inst()->getEnabled()) std::cout << curX.toStdString() << "[" << xmin << ", " << xmax << ")" << std::endl;
        if(Debug::Inst()->getEnabled()) std::cout << curY.toStdString() << "[" << ymin << ", " << ymax << ")" << std::endl;
        
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
        update();
        return;
    }
}

void TreeViewer::on_btnGetSelected_clicked() {
    treebuilder.useEventList(true);
    if (treebuilder.getCurrentTree()) {
        SelectionDetails* details = new SelectionDetails();
        details->populate(treebuilder.getCurrentTree(), treebuilder.getEventList());
        emit showTabSignal(details, "Selection Info");
    }
}

void TreeViewer::on_btnTkMap_clicked() {
    if (curX == "") {
        QMessageBox::warning(this, "Tracker Map Error", "You need to draw a variable before making the tracker map", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if (treebuilder.getCurrentTree()) {
        TkMap* tkmap = new TkMap(0, treebuilder.getCurrentTree(), treebuilder.getEventList(), curX, xboundmin, xboundmax);
        emit showTabSignal(tkmap, "Tracker Map");
    }

}

