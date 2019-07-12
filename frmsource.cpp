#include "Debug.h"
#include "frmsource.h"

#include <QFileDialog>

#include <TString.h>
#include <TObjArray.h>
#include <TChain.h>
#include <TChainElement.h>
#include <TKey.h>
#include <TH1.h>

#include "cmssw/SiStripFedKey.h"
#include "cmssw/SiStripFecKey.h"

SourceDisplay::SourceDisplay(QWidget* p, QString c, QString r, const QVector<QPair<QString, QString> >& d, const QVector<QPair<unsigned, unsigned> >& k, const QString & partition): 
    QConnectedTabWidget(p),
    currun(c),
    refrun(r),
    partition(partition),
    refexists(false),
    iscurrent(true),
    updatehistitem(false),
    histitem("")
{
    setupUi(this);

    selModel = new QStandardItemModel(0, 2,this);
    selView->setModel(selModel);
    selView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    selView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(selView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(deviceChanged(QModelIndex,QModelIndex)));
    connect(selModel,SIGNAL(itemChanged(QStandardItem*)),SLOT(updatePlot(QStandardItem*)));

    for (int i = 0; i < d.size(); i++) devices.push_back(QPair<QString , QString >(d[i].first, d[i].second));
    for (int i = 0; i < k.size(); i++) keys   .push_back(QPair<unsigned, unsigned>(k[i].first, k[i].second));

    if (refrun != "") refexists = true;

    for (int i = 0; i < devices.size(); i++) {
        QList<QStandardItem*> list;
        QStandardItem* detid = new QStandardItem(devices[i].first);
        QStandardItem* i2cad = new QStandardItem(devices[i].second);
        detid->setCheckable(refexists);
        detid->setCheckState(Qt::Unchecked);
        list.append(detid);
        list.append(i2cad);
        selModel->appendRow(list);
    }

    selModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Detid"));
    selModel->setHeaderData(1, Qt::Horizontal, QObject::tr("I2CAddress"));

    if (currun != "") curclient = getClientFile(currun,partition);
    if (refexists   ) refclient = getClientFile(refrun,partition);

    if (!curclient || !curclient->IsOpen()) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to open client file of run " << currun;
    }        
    if (refexists && (!refclient || !refclient->IsOpen())) {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to open client file of run " << refrun;
    } 

    selView->selectRow(0);
}

SourceDisplay::~SourceDisplay() {
}

TFile* SourceDisplay::getClientFile(QString run, QString partition = "") {

  TString filePath = Form("/exports/Data/%d/SiStripCommissioningClient*.root", run.toInt());
  TChain chain;
  TChain chain_2;
  chain.Add(filePath);
  TObjArray *fileElements = chain.GetListOfFiles();
  
  if(fileElements->GetEntries() > 1){ // use the partition to solve ambiguity
    filePath = Form("/exports/Data/%d/SiStripCommissioningClient*%s*.root",run.toInt(),partition.toStdString().c_str());
    chain_2.Add(filePath);
    fileElements = chain_2.GetListOfFiles();    
  }
    
  if(fileElements->GetEntries() > 1){
    if (Debug::Inst()->getEnabled()) qDebug() << "Multiple client files found for run " << run;
    return NULL;
  }
  
  if (fileElements->GetEntries() == 0) {
    if (Debug::Inst()->getEnabled()) qDebug() << "No client file found for run " << run;
    return NULL;
  }        
  
  TIter thefile(fileElements);
  TChainElement* chEl= (TChainElement*)thefile();
  return TFile::Open(chEl->GetTitle());
}

void SourceDisplay::deviceChanged(QModelIndex current, QModelIndex) {
    if (selModel->item(current.row(), 0)->checkState() != Qt::Checked ) iscurrent = true ;
    if (selModel->item(current.row(), 0)->checkState() == Qt::Checked ) iscurrent = false;

    if ( iscurrent && (!curclient || !curclient->IsOpen()) ) return;
    if (!iscurrent && (!refclient || !refclient->IsOpen()) ) return;

    if (histitem == "") updatehistitem = true;
    else updatehistitem = false;
    source->clear();
    for (int i = 0; i < devices.size(); i++) {
        if (devices[i].first == selModel->item(current.row(),0)->text() && devices[i].second == selModel->item(current.row(),1)->text()) {
            SiStripFecKey feckey(keys[i].first);            
            TString path = Form("DQMData/Collate/SiStrip/ControlView/FecCrate%d/FecSlot%d/FecRing%d/CcuAddr%d/CcuChan%d", feckey.fecCrate(), feckey.fecSlot(), feckey.fecRing(), feckey.ccuAddr(), feckey.ccuChan());
            
            TDirectory* dir;
            if (iscurrent) dir = (TDirectory*)curclient->Get(path);
            else           dir = (TDirectory*)refclient->Get(path);
            if (!dir) {
                if (Debug::Inst()->getEnabled()) qDebug() << "TDirectory not found : " << path.Data();
            }
            else {
                TIter next(dir->GetListOfKeys());
                TKey* dirkey;
                while ((dirkey = (TKey*)next())) {
                    TH1* obj = (TH1*)dirkey->ReadObj();
                    QString identifier = QString("%1").arg(keys[i].second, 8, 16, QChar('0'))+"_LldChannel"+QString::number(feckey.lldChan());
                    if (QString(obj->GetName()).contains(identifier)) {
                        QString histname(obj->GetName());
                        QString comboname(obj->GetName());
                        comboname = comboname.remove("ExpertHisto_");
                        comboname = comboname.remove("_FedKey0x");
                        comboname = comboname.remove(identifier);
                        if (histname.contains("Apv")) {
                            if (histname.contains(QString("Apv")+devices[i].second)) {
                                comboname = comboname.remove(QString("_Apv")+devices[i].second);
                                source->addItem(comboname, QString(path.Data())+"/"+histname);
                            }
                            else if (histname.contains(QString("Apv")+QString::number(devices[i].second.toInt()%2))) {
                                comboname = comboname.remove(QString("_Apv")+QString::number(devices[i].second.toInt()%2));
                                source->addItem(comboname, QString(path.Data())+"/"+histname);
                            }
                            else if (histname.contains("ApvTiming")) source->addItem(comboname, QString(path.Data())+"/"+histname);
                        }
                        else source->addItem(comboname, QString(path.Data())+"/"+histname);
                    } 
                    else if (QString(obj->GetName()).contains(QString("%1").arg(keys[i].second, 8, 16, QChar('0'))) && QString(obj->GetName()).contains(QString("Apv"+devices[i].second)) ) {
                        QString histname(obj->GetName());
                        QString comboname(obj->GetName());
                        comboname = comboname.remove("ExpertHisto_");
                        comboname = comboname.remove("_FedKey0x");
                        comboname = comboname.remove(QString("%1").arg(keys[i].second, 8, 16, QChar('0')));
                        comboname = comboname.remove(QString("_Apv"+devices[i].second));
                        source->addItem(comboname, QString(path.Data())+"/"+histname);

                    }
                }
            }
        }
    }

    if (histitem != "") {
        int idx = source->findText(histitem);
        if (idx != -1) source->setCurrentIndex(idx);
    }
    histitem = source->currentText();

    qtCanvas->GetCanvas()->cd();
    TH1* hist;
    if (iscurrent) hist = (TH1*)curclient->Get(source->itemData(source->currentIndex()).toString().toStdString().c_str());
    else           hist = (TH1*)refclient->Get(source->itemData(source->currentIndex()).toString().toStdString().c_str());
    if (hist) {
        QString title = QString("Run ") + (iscurrent ? currun : refrun) + QString(": ") + source->currentText().toStdString().c_str();
        hist->GetXaxis()->SetTitle(title.toStdString().c_str());
        hist->Draw();
        qtCanvas->GetCanvas()->Modified();
        qtCanvas->GetCanvas()->Update();
    }
    else {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to find histogram " << source->itemData(source->currentIndex()).toString().toStdString().c_str();
    }   

    updatehistitem = true;
}

void SourceDisplay::updatePlot(QStandardItem* item) {
    QModelIndexList idxlist = selView->selectionModel()->selectedIndexes();
    if (idxlist.size() > 0 && selModel->item(idxlist[0].row(), 0) == item) deviceChanged(idxlist[0], idxlist[0]);
}

void SourceDisplay::on_source_currentIndexChanged(int) { 
    if (updatehistitem && histitem != source->currentText()) {
        histitem = source->currentText();

        if ( iscurrent && (!curclient || !curclient->IsOpen()) ) return;
        if (!iscurrent && (!refclient || !refclient->IsOpen()) ) return;
        
        qtCanvas->GetCanvas()->cd();
        TH1* hist;
        if ( iscurrent) hist = (TH1*)curclient->Get(source->itemData(source->currentIndex()).toString().toStdString().c_str());
        else            hist = (TH1*)refclient->Get(source->itemData(source->currentIndex()).toString().toStdString().c_str());
        if (!hist) {
            if (Debug::Inst()->getEnabled()) qDebug() << "Unable to find histogram " << source->itemData(source->currentIndex()).toString().toStdString().c_str();
            return;
        }
        QString title = QString("Run ") + (iscurrent ? currun : refrun) + QString(": ") + source->currentText().toStdString().c_str();
        hist->GetXaxis()->SetTitle(title.toStdString().c_str());
        hist->Draw();
        qtCanvas->GetCanvas()->Modified();
        qtCanvas->GetCanvas()->Update();
    }
}

void SourceDisplay::on_btnPrint_clicked() {
    char* curDir;
    curDir = getenv("PWD");
    QString saveFileName = (QFileDialog::getSaveFileName(this, tr("Save Image"), curDir, tr("Image files (*.png *.jpg)")));
    if (Debug::Inst()->getEnabled()) qDebug() << saveFileName;
    if (saveFileName.isEmpty() or saveFileName.isNull()) return;
    else qtCanvas->GetCanvas()->Print(saveFileName.toStdString().c_str());
}

