#include "frmdbupload.h"
#include "frmterminaldialog.h"
#include "frmaddskip.h"
#include "frmterminal.h"
#include "TreeBuilder.h"
#include "cmssw/SiStripFedKey.h"
#include "cmssw/SiStripFecKey.h"
#include <fstream>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardItem>
#include <QTextCursor>
#include <QTextTable>
#include <QMessageBox>
#include <QDir>

DBUpload::DBUpload(QWidget* parent):
    QConnectedTabWidget(parent),
    currentRun(""),
    currentPartition(""),
    analysisType(""),
    selLevel("FULL")
{
    setupUi(this);

    skipModel = new QStandardItemModel(0, 7,this);
    skipModel->setHeaderData(0, Qt::Horizontal, QObject::tr("FED Id"));
    skipModel->setHeaderData(1, Qt::Horizontal, QObject::tr("FEC Crate"));
    skipModel->setHeaderData(2, Qt::Horizontal, QObject::tr("FEC Slot"));
    skipModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Ring"));
    skipModel->setHeaderData(4, Qt::Horizontal, QObject::tr("CCU"));
    skipModel->setHeaderData(5, Qt::Horizontal, QObject::tr("CCU Chan"));
    skipModel->setHeaderData(6, Qt::Horizontal, QObject::tr("LLD Chan"));
    
    skipList->setModel(skipModel);
    skipList->setSelectionMode(QAbstractItemView::SingleSelection);
    skipList->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    skipList->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(skipModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(channelCheckChanged(QStandardItem*)));
}

DBUpload::~DBUpload() {
}

void DBUpload::setCurrentRun(const QString& r) {
    currentRun = r;
}

void DBUpload::setCurrentPartition(const QString& p) {
    currentPartition = p;
}

void DBUpload::setTree(TTree* t) {
    tree = t;
}

void DBUpload::setSelMap(QVector<int> sm) {
    for (int i = 0; i < sm.size(); i++) selMap.push_back(sm[i]);
}

QString DBUpload::getCurrentRun() {
    return currentRun;
}

QString DBUpload::getCurrentPartition() {
    return currentPartition;
}

bool DBUpload::fillSkipList() {

    if(Debug::Inst()->getEnabled()) qDebug() << "Selection level set to : " << selLevel << "\n";

    selLevelMap.clear();
    if (skipModel->rowCount() > 0) skipModel->removeRows(0, skipModel->rowCount());

    if (tree == NULL) {
        if(Debug::Inst()->getEnabled()) qDebug() << "Invalid tree - cannot fill the table of skipped channels\n";
        return false;
    }

    if (selMap.size() == 0) {
        if(Debug::Inst()->getEnabled()) qDebug() << "Selection map has 0 size - cannot fill the table of skipped channels\n";
        return false;
    }

    TBranch* bdevId          = tree->GetBranch("DeviceId");
    TBranch* bdetId          = tree->GetBranch("Detid");
    TBranch* bFecCrate       = tree->GetBranch("FecCrate");
    TBranch* bFec            = tree->GetBranch("Fec");
    TBranch* bRing           = tree->GetBranch("Ring");
    TBranch* bCcu            = tree->GetBranch("Ccu");
    TBranch* bCcuArrangement = tree->GetBranch("CcuArrangement");
    TBranch* bI2CChannel     = tree->GetBranch("I2CChannel");
    TBranch* bI2CAddress     = tree->GetBranch("I2CAddress");
    TBranch* blasChan        = tree->GetBranch("lasChan");
    TBranch* bFedId          = tree->GetBranch("FedId");
    TBranch* bFeUnit         = tree->GetBranch("FeUnit");
    TBranch* bFeChan         = tree->GetBranch("FeChan");
    TBranch* bFeApv          = tree->GetBranch("FeApv");
    
    double devId          = 0.0;
    double detId          = 0.0;
    double FecCrate       = 0.0;
    double Fec            = 0.0;
    double Ring           = 0.0;
    double Ccu            = 0.0;
    double CcuArrangement = 0.0;
    double I2CChannel     = 0.0;
    double I2CAddress     = 0.0;
    double lasChan        = 0.0;
    double FedId          = 0.0;
    double FeUnit         = 0.0;
    double FeChan         = 0.0;
    double FeApv          = 0.0;
    
    bdevId         ->SetAddress(&devId);
    bdetId         ->SetAddress(&detId);
    bFecCrate      ->SetAddress(&FecCrate);
    bFec           ->SetAddress(&Fec);
    bRing          ->SetAddress(&Ring);
    bCcu           ->SetAddress(&Ccu);
    bCcuArrangement->SetAddress(&CcuArrangement);
    bI2CChannel    ->SetAddress(&I2CChannel);
    bI2CAddress    ->SetAddress(&I2CAddress);
    blasChan       ->SetAddress(&lasChan);
    bFedId         ->SetAddress(&FedId);
    bFeUnit        ->SetAddress(&FeUnit);
    bFeChan        ->SetAddress(&FeChan);
    bFeApv         ->SetAddress(&FeApv);

    for(int i = 0; i < tree->GetEntries(); i++) {
        bdevId         ->GetEvent(i);
        bdetId         ->GetEvent(i);
        bFecCrate      ->GetEvent(i);
        bFec           ->GetEvent(i);
        bRing          ->GetEvent(i);
        bCcu           ->GetEvent(i);
        bCcuArrangement->GetEvent(i);
        bI2CChannel    ->GetEvent(i);
        bI2CAddress    ->GetEvent(i);
        blasChan       ->GetEvent(i);
        bFedId         ->GetEvent(i);
        bFeUnit        ->GetEvent(i);
        bFeChan        ->GetEvent(i);
        bFeApv         ->GetEvent(i);
    
        if (selMap[i] == 0) continue;
   
        if      (selLevel == "FULL") {
            SiStripFedKey fedkey(int(FedId), int(FeUnit), int(FeChan), 0);
            SiStripFecKey feckey(int(FecCrate), int(Fec), int(Ring), int(Ccu), int(I2CChannel), int(lasChan)+1, 0);
            selLevelMap[feckey.key()] = fedkey.key();
        }
        else if (selLevel == "CCUCHAN") {
            SiStripFedKey fedkey(int(FedId), int(FeUnit), int(FeChan), 0);
            SiStripFecKey feckey(int(FecCrate), int(Fec), int(Ring), int(Ccu), int(I2CChannel), 0             , 0);
            selLevelMap[feckey.key()] = fedkey.key();
        }
        else if (selLevel == "CCU") {
            SiStripFedKey fedkey(int(FedId), int(FeUnit), int(FeChan), 0);
            SiStripFecKey feckey(int(FecCrate), int(Fec), int(Ring), int(Ccu), 0              , 0             , 0);
            selLevelMap[feckey.key()] = fedkey.key();
        }
        else if (selLevel == "RING") {
            SiStripFedKey fedkey(int(FedId), int(FeUnit), int(FeChan), 0);
            SiStripFecKey feckey(int(FecCrate), int(Fec), int(Ring), 0       , 0              , 0             , 0);
            selLevelMap[feckey.key()] = fedkey.key();
        }
        else if (selLevel == "FEC") {
            SiStripFedKey fedkey(int(FedId), int(FeUnit), int(FeChan), 0);
            SiStripFecKey feckey(int(FecCrate), int(Fec), 0        , 0       , 0              , 0             , 0);
            selLevelMap[feckey.key()] = fedkey.key();
        }
        else if (selLevel == "FED") {
            SiStripFedKey fedkey(int(FedId), 0, 0, 0);
            selLevelMap[fedkey.key()] = fedkey.key();
        }
    
    }

    QMap<unsigned, unsigned>::const_iterator map_iter = selLevelMap.constBegin();
    while (map_iter != selLevelMap.constEnd()) {
        QList<QStandardItem*> itemrow;

        QStandardItem* feditem     = new QStandardItem("");
        QStandardItem* crateitem   = new QStandardItem("");
        QStandardItem* fecitem     = new QStandardItem("");
        QStandardItem* ringitem    = new QStandardItem("");
        QStandardItem* ccuitem     = new QStandardItem("");
        QStandardItem* ccuchanitem = new QStandardItem("");
        QStandardItem* llditem     = new QStandardItem("");

        feditem     ->setEditable(false);
        crateitem   ->setEditable(false);
        fecitem     ->setEditable(false);
        ringitem    ->setEditable(false);
        ccuitem     ->setEditable(false);
        ccuchanitem ->setEditable(false);
        llditem     ->setEditable(false);
            
        itemrow.append(feditem    );
        itemrow.append(crateitem  );
        itemrow.append(fecitem    );
        itemrow.append(ringitem   );
        itemrow.append(ccuitem    );
        itemrow.append(ccuchanitem);
        itemrow.append(llditem    );

        SiStripFecKey feckey(map_iter.key());
        SiStripFedKey fedkey(map_iter.value());

        fecitem->setData(feckey.key());

        if      (selLevel == "FED") {
            feditem->setCheckable(true);
            feditem->setCheckState(Qt::Checked);
            feditem->setText(QString::number(fedkey.fedId()));
            skipModel->appendRow(itemrow);
        }    

        else if (selLevel == "FULL") {
            feditem->setCheckable(true);
            feditem->setCheckState(Qt::Checked);
            feditem     ->setText(QString::number(fedkey.fedId()));
            crateitem   ->setText(QString::number(feckey.fecCrate()));
            fecitem     ->setText(QString::number(feckey.fecSlot()));
            ringitem    ->setText(QString::number(feckey.fecRing()));
            ccuitem     ->setText(QString::number(feckey.ccuAddr()));
            ccuchanitem ->setText(QString::number(feckey.ccuChan()));
            llditem     ->setText(QString::number(feckey.lldChan()));
            skipModel->appendRow(itemrow);
        }   

        else if (selLevel == "CCUCHAN") {
            crateitem->setCheckable(true);
            crateitem->setCheckState(Qt::Checked);
            crateitem   ->setText(QString::number(feckey.fecCrate()));
            fecitem     ->setText(QString::number(feckey.fecSlot()));
            ringitem    ->setText(QString::number(feckey.fecRing()));
            ccuitem     ->setText(QString::number(feckey.ccuAddr()));
            ccuchanitem ->setText(QString::number(feckey.ccuChan()));
            skipModel->appendRow(itemrow);
        }  

        else if (selLevel == "CCU") {
            crateitem->setCheckable(true);
            crateitem->setCheckState(Qt::Checked);
            crateitem   ->setText(QString::number(feckey.fecCrate()));
            fecitem     ->setText(QString::number(feckey.fecSlot()));
            ringitem    ->setText(QString::number(feckey.fecRing()));
            ccuitem     ->setText(QString::number(feckey.ccuAddr()));
            skipModel->appendRow(itemrow);
        }

        else if (selLevel == "RING") {
            crateitem->setCheckable(true);
            crateitem->setCheckState(Qt::Checked);
            crateitem   ->setText(QString::number(feckey.fecCrate()));
            fecitem     ->setText(QString::number(feckey.fecSlot()));
            ringitem    ->setText(QString::number(feckey.fecRing()));
            skipModel->appendRow(itemrow);
        }

        else if (selLevel == "FEC") {
            crateitem->setCheckable(true);
            crateitem->setCheckState(Qt::Checked);
            crateitem   ->setText(QString::number(feckey.fecCrate()));
            fecitem     ->setText(QString::number(feckey.fecSlot()));
            skipModel->appendRow(itemrow);
        }    

        ++map_iter;
    }

    return true;
}

void DBUpload::on_radFed_toggled(bool) {
    if (radFed->isChecked()) {
        unselLevelMap.clear();
        addLevelMap.clear();
        selLevel = "FED";
        fillSkipList();
    }
}

void DBUpload::on_radFec_toggled(bool) {
    if (radFec->isChecked()) {
        unselLevelMap.clear();
        addLevelMap.clear();
        selLevel = "FEC";
        fillSkipList();
    }
}

void DBUpload::on_radRing_toggled(bool) {
    if (radRing->isChecked()) {
        unselLevelMap.clear();
        addLevelMap.clear();
        selLevel = "RING";
        fillSkipList();
    }
}

void DBUpload::on_radCcu_toggled(bool) {
    if (radCcu->isChecked()) {
        unselLevelMap.clear();
        addLevelMap.clear();
        selLevel = "CCU";
        fillSkipList();
    }
}

void DBUpload::on_radCcuChan_toggled(bool) {
    if (radCcuChan->isChecked()) {
        unselLevelMap.clear();
        addLevelMap.clear();
        selLevel = "CCUCHAN";
        fillSkipList();
    }
}

void DBUpload::on_radAll_toggled(bool) {
    if (radAll->isChecked()) {
        unselLevelMap.clear();
        addLevelMap.clear();
        selLevel = "FULL";
        fillSkipList();
    }
}

void DBUpload::channelCheckChanged(QStandardItem* item) {
    if (item->isCheckable()) {
        if (item->checkState() == Qt::Unchecked) {
            if (selLevel == "FED") {
                SiStripFedKey fedkey(skipModel->item(item->row(),0)->text().toUInt(), 0, 0, 0);
                if (item->foreground().color() == Qt::black) unselLevelMap[fedkey.key()] = 1;
                if (item->foreground().color() == Qt::blue ) addLevelMap.remove(fedkey.key());
            }
            else {
                SiStripFecKey feckey(skipModel->item(item->row(),2)->data().toUInt());
                if (item->foreground().color() == Qt::black) unselLevelMap[feckey.key()] = 1;
                if (item->foreground().color() == Qt::blue ) addLevelMap.remove(feckey.key());
            }
        }
        else {
            if (selLevel == "FED") {
                SiStripFedKey fedkey(skipModel->item(item->row(),0)->text().toUInt(), 0, 0, 0);
                if (item->foreground().color() == Qt::black) unselLevelMap.remove(fedkey.key());
                if (item->foreground().color() == Qt::blue ) addLevelMap[fedkey.key()] = 1;
            }
            else {
                SiStripFecKey feckey(skipModel->item(item->row(),2)->data().toUInt());
                if (item->foreground().color() == Qt::black) unselLevelMap.remove(feckey.key());
                if (item->foreground().color() == Qt::blue ) addLevelMap[feckey.key()] = 1;
            }
        }
    }
}

void DBUpload::on_btnAddSkip_clicked() {
    bool fed     = false;
    bool crate   = false;
    bool fec     = false;
    bool ring    = false;
    bool ccu     = false;
    bool ccuchan = false;
    bool lldchan = false;

    if (selLevel == "FED") {
        fed     = true;
    }
    else if (selLevel == "FEC") {
        crate   = true;
        fec     = true;
    }
    else if (selLevel == "RING") {
        crate   = true;
        fec     = true;
        ring    = true;
    }
    else if (selLevel == "CCU") {
        crate   = true;
        fec     = true;
        ring    = true;
        ccu     = true;
    }
    else if (selLevel == "CCUCHAN") {
        crate   = true;
        fec     = true;
        ring    = true;
        ccu     = true;
        ccuchan = true;
    }
    else if (selLevel == "FULL") {
        crate   = true;
        fec     = true;
        ring    = true;
        ccu     = true;
        ccuchan = true;
        lldchan = true;
    }

    AddSkipChannel* addskip = new AddSkipChannel(fed, crate, fec, ring, ccu, ccuchan, lldchan);
    connect(addskip, SIGNAL(key(QPair<unsigned,unsigned>)), this, SLOT(addSkipChannel(QPair<unsigned,unsigned>)));
    addskip->exec();
}

void DBUpload::addSkipChannel(QPair<unsigned, unsigned> keys) {
    if (selLevel == "FED") addLevelMap[keys.first]  = keys.first;
    else                   addLevelMap[keys.second] = keys.first;

    QList<QStandardItem*> itemrow;

    QStandardItem* feditem     = new QStandardItem("");
    QStandardItem* crateitem   = new QStandardItem("");
    QStandardItem* fecitem     = new QStandardItem("");
    QStandardItem* ringitem    = new QStandardItem("");
    QStandardItem* ccuitem     = new QStandardItem("");
    QStandardItem* ccuchanitem = new QStandardItem("");
    QStandardItem* llditem     = new QStandardItem("");
    
    feditem     ->setEditable(false);
    crateitem   ->setEditable(false);
    fecitem     ->setEditable(false);
    ringitem    ->setEditable(false);
    ccuitem     ->setEditable(false);
    ccuchanitem ->setEditable(false);
    llditem     ->setEditable(false);
    
    feditem     ->setForeground(QBrush(Qt::blue));
    crateitem   ->setForeground(QBrush(Qt::blue));
    fecitem     ->setForeground(QBrush(Qt::blue));
    ringitem    ->setForeground(QBrush(Qt::blue));
    ccuitem     ->setForeground(QBrush(Qt::blue));
    ccuchanitem ->setForeground(QBrush(Qt::blue));
    llditem     ->setForeground(QBrush(Qt::blue));
    
    itemrow.append(feditem    );
    itemrow.append(crateitem  );
    itemrow.append(fecitem    );
    itemrow.append(ringitem   );
    itemrow.append(ccuitem    );
    itemrow.append(ccuchanitem);
    itemrow.append(llditem    );
    
    SiStripFedKey fedkey(keys.first);
    SiStripFecKey feckey(keys.second);
    
    fecitem->setData(keys.second);
    
    if      (selLevel == "FED") {
        feditem->setCheckable(true);
        feditem->setCheckState(Qt::Checked);
        feditem->setText(QString::number(fedkey.fedId()));
        skipModel->appendRow(itemrow);
    }
    
    else if (selLevel == "FULL") {
        feditem->setCheckable(true);
        feditem->setCheckState(Qt::Checked);
        feditem     ->setText(QString::number(fedkey.fedId()));
        crateitem   ->setText(QString::number(feckey.fecCrate()));
        fecitem     ->setText(QString::number(feckey.fecSlot()));
        ringitem    ->setText(QString::number(feckey.fecRing()));
        ccuitem     ->setText(QString::number(feckey.ccuAddr()));
        ccuchanitem ->setText(QString::number(feckey.ccuChan()));
        llditem     ->setText(QString::number(feckey.lldChan()));
        skipModel->appendRow(itemrow);
    }  
    
    else if (selLevel == "CCUCHAN") {
        crateitem->setCheckable(true);
        crateitem->setCheckState(Qt::Checked);
        crateitem   ->setText(QString::number(feckey.fecCrate()));
        fecitem     ->setText(QString::number(feckey.fecSlot()));
        ringitem    ->setText(QString::number(feckey.fecRing()));
        ccuitem     ->setText(QString::number(feckey.ccuAddr()));
        ccuchanitem ->setText(QString::number(feckey.ccuChan()));
        skipModel->appendRow(itemrow);
    } 
    
    else if (selLevel == "CCU") {
        crateitem->setCheckable(true);
        crateitem->setCheckState(Qt::Checked);
        crateitem   ->setText(QString::number(feckey.fecCrate()));
        fecitem     ->setText(QString::number(feckey.fecSlot()));
        ringitem    ->setText(QString::number(feckey.fecRing()));
        ccuitem     ->setText(QString::number(feckey.ccuAddr()));
        skipModel->appendRow(itemrow);
    }
    
    else if (selLevel == "RING") {
        crateitem->setCheckable(true);
        crateitem->setCheckState(Qt::Checked);
        crateitem   ->setText(QString::number(feckey.fecCrate()));
        fecitem     ->setText(QString::number(feckey.fecSlot()));
        ringitem    ->setText(QString::number(feckey.fecRing()));
        skipModel->appendRow(itemrow);
    }
    
    else if (selLevel == "FEC") {
        crateitem->setCheckable(true);
        crateitem->setCheckState(Qt::Checked);
        crateitem   ->setText(QString::number(feckey.fecCrate()));
        fecitem     ->setText(QString::number(feckey.fecSlot()));
        skipModel->appendRow(itemrow);
    }

    /*
    feditem     ->setEnabled(false);
    crateitem   ->setEnabled(false);
    fecitem     ->setEnabled(false);
    ringitem    ->setEnabled(false);
    ccuitem     ->setEnabled(false);
    ccuchanitem ->setEnabled(false);
    llditem     ->setEnabled(false);
    */
}

void DBUpload::on_btnUpload_clicked() {

    if (currentRun.toInt() == sistrip::MULTIPART) {

        if (QMessageBox::question(NULL, QObject::tr("Confirmation"), QObject::tr("You are going to perform Timing O2O. Are you sure you want to continue?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;


        QString nextRun;
        QString iovQueryStr("select max(runnumbertbl.runnumber+1) runnumber from CMS_RUNINFO.runnumbertbl");
        QSqlQuery iovQuery(iovQueryStr);

        while (iovQuery.next()) nextRun = iovQuery.value(0).toString();

        skipss.str("");
        infoss.str("");
        infoss << "<html>" << std::endl;
        infoss << "<b>Timing O2O : </b>" << "<br/>";
        infoss << "IOV : " << qPrintable(nextRun) << "<br/>";

        QString partFilename = "/nfshome0/trackerpro/o2o/scripts/TimingO2O_Partitions.py";
        QString skipFilename = "/nfshome0/trackerpro/o2o/scripts/TimingO2O_SkippedChannels.py";

        std::ofstream partFile;
        std::ofstream skipFile;

        partFile.open(partFilename.toStdString().c_str());
        skipFile.open(skipFilename.toStdString().c_str());

        QMap<unsigned,unsigned> uploadMap;
        QMap<unsigned, unsigned>::const_iterator ins_iter = addLevelMap.constBegin();
        while (ins_iter != addLevelMap.constEnd()) {
            uploadMap[ins_iter.key()] = ins_iter.value();
            ++ins_iter;
        }
        ins_iter = selLevelMap.constBegin();
        while (ins_iter != selLevelMap.constEnd()) {
            uploadMap[ins_iter.key()] = ins_iter.value();
            ++ins_iter;
        }

        partFile << partss.str().c_str();
        if (chkSkip->isChecked()) {
            QMap<unsigned, unsigned>::const_iterator map_iter = uploadMap.constBegin();
            while (map_iter != uploadMap.constEnd()) {
                if (unselLevelMap.constFind(map_iter.key()) != unselLevelMap.constEnd()) {
                    ++map_iter;
                    continue;
                }
                if (selLevel == "FED") {
                    SiStripFedKey fedkey(map_iter.key());
                    skipss << "\tcms.PSet(" << std::endl;
                    skipss << "\t\t fedId = cms.untracked.uint32("  << fedkey.fedId()  << ")," << std::endl;
                    skipss << "\t\t feUnit = cms.untracked.uint32(" << fedkey.feUnit() << ")," << std::endl;
                    skipss << "\t\t feChan = cms.untracked.uint32(" << fedkey.feChan() << ")," << std::endl;
                    skipss << "\t\t fedApv = cms.untracked.uint32(" << fedkey.fedApv() << ")"  << std::endl;
                    skipss << "\t)," << std::endl;
            
                }
                else {
                    SiStripFecKey feckey(map_iter.key());
                    skipss << "\tcms.PSet(" << std::endl;
                    skipss << "\t\t fecCrate = cms.untracked.uint32(" << feckey.fecCrate()  << ")," << std::endl;
                    skipss << "\t\t fecSlot  = cms.untracked.uint32(" << feckey.fecSlot()   << ")," << std::endl;
                    skipss << "\t\t fecRing  = cms.untracked.uint32(" << feckey.fecRing()   << ")," << std::endl;
                    skipss << "\t\t ccuAddr  = cms.untracked.uint32(" << feckey.ccuAddr()   << ")," << std::endl;
                    skipss << "\t\t ccuChan  = cms.untracked.uint32(" << feckey.ccuChan()   << ")," << std::endl;
                    skipss << "\t\t lldChan  = cms.untracked.uint32(" << feckey.i2cAddr()   << ")," << std::endl;
                    skipss << "\t\t i2cAddr  = cms.untracked.uint32(" << 0                  << ")"  << std::endl;
                    skipss << "\t)," << std::endl;
            
                }
                ++map_iter;
            }
            skipFile << skipss.str().c_str();
        }

        partFile.close();
        skipFile.close();

        QString sveto = (chkVeto->isChecked() ? "0" : "1");
        QStringList commandArgs;
        commandArgs << "/nfshome0/trackerpro/o2o/scripts/runGainO2O.sh" << sveto << nextRun << partFilename << skipFilename;
        //commandArgs << "/nfshome0/trackerpro/o2o/scripts/testGainO2O.sh" << sveto << nextRun << partFilename << skipFilename;
        //commandArgs << "/nfshome0/trackerpro/o2o/scripts/simpletest.sh" << sveto << nextRun << partFilename << skipFilename;

        bool o2oresult = false;
        QProcess* proc = new QProcess(this);
        TkTerminalDialog* timingO2OTerm = new TkTerminalDialog(this);
        timingO2OTerm->setProcessPtr(proc);

        connect( proc, SIGNAL(readyReadStandardOutput())          , timingO2OTerm, SLOT(readFromStdout())  );
        connect( proc, SIGNAL(finished(int, QProcess::ExitStatus)), timingO2OTerm, SLOT(processFinished(int, QProcess::ExitStatus)) );
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), timingO2OTerm, SLOT(executeWaitForReadyRead()));
        timer->start(100);

        proc->start(commandArgs.join(" "));
        if (!proc->waitForStarted()) {
            infoss << "Could not start analysis" << qPrintable(nextRun) << "<br/>";
            delete timingO2OTerm;
            o2oresult = false;
        }
        else {
            if (timingO2OTerm->exec()==QDialog::Accepted) o2oresult = true;
            else o2oresult = false;
        }

        if (o2oresult) infoss << "<b>O2O process completed successfully</b>" << "<br/>";
        else           infoss << "<b>O2O process failed</b>"                 << "<br/>";

        infoss << "</html>" << std::endl;
        QTextCursor cursor(txtCurRunInfo->textCursor());
        cursor.insertHtml(infoss.str().c_str());
    }

    else {
        QFile file("/opt/cmssw/scripts/analysis_template_test.py");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
        
        QByteArray total;
        QByteArray line;
        while (!file.atEnd()) {
            line = file.readAll();
            total.append(line);
        }
   
        QString sveto = (chkVeto->isChecked() ? "True" : "False");

        QMap<QString, QString> runTypeMap;
        runTypeMap["PEDESTAL"]  = "PedestalsParameters";
        runTypeMap["PEDESTALS"] = "PedestalsParameters";
        runTypeMap["TIMING"]    = "ApvTimingParameters";
        runTypeMap["GAINSCAN"]  = "OptoScanParameters";
        runTypeMap["VPSPSCAN"]  = "VpspScanParameters";

        QMap<unsigned,unsigned> uploadMap;
        QMap<unsigned, unsigned>::const_iterator ins_iter = addLevelMap.constBegin();
        while (ins_iter != addLevelMap.constEnd()) {
            uploadMap[ins_iter.key()] = ins_iter.value();
            ++ins_iter;
        }
        ins_iter = selLevelMap.constBegin();
        while (ins_iter != selLevelMap.constEnd()) {
            uploadMap[ins_iter.key()] = ins_iter.value();
            ++ins_iter;
        }

        if (chkSkip->isChecked() && uploadMap.size() > 0) {
            if (runTypeMap.contains(analysisType)) {
                QString runtypestr = "process.db_client.";
                runtypestr += runTypeMap[analysisType];
                total.append(runtypestr+".doSelectiveUpload = cms.bool(True)\n");
                total.append(runtypestr+".vetoModules = cms.bool(");
                total.append(sveto);
                total.append(")\n");
                QMap<unsigned, unsigned>::const_iterator sm_iter = uploadMap.constBegin();

                if (selLevel == "FED") {
                    total.append(runtypestr+".fedMaskVector = cms.vuint32(");
                    bool firstWritten = false;
                    while (sm_iter != uploadMap.constEnd()) {
                        if (unselLevelMap.constFind(sm_iter.key()) != unselLevelMap.constEnd()) {
                            ++sm_iter;
                            continue;
                        }
                        SiStripFedKey fedkey(sm_iter.key());
                        if (firstWritten) total.append(",");
                        total.append(QString::number(fedkey.fedId()));
                        firstWritten = true;
                        ++sm_iter;
                    }
                    total.append(")\n");
                }
                else if (selLevel == "FULL" || selLevel == "FEC" || selLevel == "RING" || selLevel == "CCU" || selLevel == "CCUCHAN") {
                    total.append(runtypestr+".fecMaskVector = cms.vuint32(");
                    sm_iter = uploadMap.constBegin();
                    bool firstWritten = false;
                    while (sm_iter != uploadMap.constEnd()) {
                        if (unselLevelMap.constFind(sm_iter.key()) != unselLevelMap.constEnd()) {
                            ++sm_iter;
                            continue;
                        }
                        SiStripFecKey feckey(sm_iter.key());
                        if (firstWritten) total.append(",");
                        total.append(QString::number(feckey.fecSlot()));
                        firstWritten = true;
                        ++sm_iter;
                    }
                    total.append(")\n");
                    total.append(runtypestr+".ringVector = cms.vuint32(");
                    sm_iter = uploadMap.constBegin();
                    firstWritten = false;
                    while (sm_iter != uploadMap.constEnd()) {
                        if (unselLevelMap.constFind(sm_iter.key()) != unselLevelMap.constEnd()) {
                            ++sm_iter;
                            continue;
                        }
                        SiStripFecKey feckey(sm_iter.key());
                        if (firstWritten) total.append(",");
                        total.append(QString::number(feckey.fecRing()));
                        firstWritten = true;
                        ++sm_iter;
                    }
                    total.append(")\n");
                    total.append(runtypestr+".ccuVector = cms.vuint32(");
                    sm_iter = uploadMap.constBegin();
                    firstWritten = false;
                    while (sm_iter != uploadMap.constEnd()) {
                        if (unselLevelMap.constFind(sm_iter.key()) != unselLevelMap.constEnd()) {
                            ++sm_iter;
                            continue;
                        }
                        SiStripFecKey feckey(sm_iter.key());
                        if (firstWritten) total.append(",");
                        total.append(QString::number(feckey.ccuAddr()));
                        firstWritten = true;
                        ++sm_iter;
                    }
                    total.append(")\n");
                    total.append(runtypestr+".i2cChanVector = cms.vuint32(");
                    sm_iter = uploadMap.constBegin();
                    firstWritten = false;
                    while (sm_iter != uploadMap.constEnd()) {
                        if (unselLevelMap.constFind(sm_iter.key()) != unselLevelMap.constEnd()) {
                            ++sm_iter;
                            continue;
                        }
                        SiStripFecKey feckey(sm_iter.key());
                        if (firstWritten) total.append(",");
                        total.append(QString::number(feckey.ccuChan()));
                        firstWritten = true;
                        ++sm_iter;
                    }
                    total.append(")\n");
                    total.append(runtypestr+".lldChanVector = cms.vuint32(");
                    sm_iter = uploadMap.constBegin();
                    firstWritten = false;
                    while (sm_iter != uploadMap.constEnd()) {
                        if (unselLevelMap.constFind(sm_iter.key()) != unselLevelMap.constEnd()) {
                            ++sm_iter;
                            continue;
                        }
                        SiStripFecKey feckey(sm_iter.key());
                        if (firstWritten) total.append(",");
                        total.append(QString::number(feckey.lldChan()));
                        firstWritten = true;
                        ++sm_iter;
                    }
                    total.append(")\n");
                }
            }
        }
        
        QFile outfile("/opt/cmssw/scripts/selectiveupload_template.py");
        outfile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream outstream(&outfile);
        outstream << total;
        outfile.close();
        
        if(Debug::Inst()->getEnabled()) qDebug() << total;
        //qDebug() << total;
        
        QStringList commandArgs;
        QString uploadString;
        QString uploadAnalString;
        QString useClientString;
        QString saveClientString;
        QString disableModulesString;
        
        uploadString = "true";
        uploadAnalString = "true";
        useClientString="true";
        saveClientString="true";
        disableModulesString="false";
        
        if (uploadString == "true") {
            if (QMessageBox::question(NULL, QObject::tr("Confirmation"), QObject::tr("You are going to upload run analysis results to the configuration database. You should have already run the same analysis and verified the quality of the run. Do you want to continue?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;
        }
        
        commandArgs << currentRun << uploadString << uploadAnalString << currentPartition << useClientString << disableModulesString << saveClientString;
       
        QDir fffdir("/raid/fff");
        QStringList runFilter;
        runFilter << "*run"+currentRun+"*";
        QStringList runs = fffdir.entryList(runFilter, QDir::Dirs);

        TkTerminal* terminal = new TkTerminal();
        if (runs.size() > 0) terminal->startProcess("/opt/cmssw/scripts/run_analysis_selup_new.sh", commandArgs);
        else                 terminal->startProcess("/opt/cmssw/scripts/run_analysis_selup.sh", commandArgs);
        if (terminal->didStartFail()) delete terminal;
        else emit showTabSignal(terminal, "Run Analysis");

    }
}

bool DBUpload::displayRunInfo() {

    if (currentRun == "") {
        btnUpload->setEnabled(false);
        return false;
    }

    fillSkipList();

    if (currentRun.toInt() == sistrip::MULTIPART) {

        //chkVeto->setEnabled(false);

        QStringList parts = currentPartition.split("*");
        QVector<QRunId> runIds;       
 
        if (parts.size() != 5) {
            if(Debug::Inst()->getEnabled()) qDebug() << "Unable to deconstruct 4 partition names for multi-partition view\n";
            btnUpload->setEnabled(false);
            return false;
        }

        for (int i = 1; i < parts.size(); i++) {
            QString part = parts.at(i);
            QStringList subparts = part.split("#");
            if (subparts.size() != 2) {
                if(Debug::Inst()->getEnabled()) qDebug() << "Unable to deconstruct 4 partition names and run numbers for multi-partition view\n";
                btnUpload->setEnabled(false);
                return false;
            }
            runIds.push_back(QRunId(subparts[0], subparts[1]));
        }

        infoss << "<html>" << std::endl;
        infoss << "<b>Multi-partition view : </b>" << "<br/><br/>";

        if (parts.at(0) != "TIMING") {
            btnUpload->setEnabled(false);
        }

        for (int i = 0; i < runIds.size(); i++) {
            QString partition, modeDescription, creationDate, startTime, endTime;
            QString fecMajor, fecMinor, fedMajor, fedMinor, connMajor, connMinor, dcuinfoMajor, dcuinfoMinor, dcumapMajor, dcumapMinor, maskMajor, maskMinor;
            QString analMajor, analMinor;
            
            QString tablename = "viewallrun";
            
            std::stringstream queryss;
            queryss << "select distinct ";
            queryss << "partitionname, ";
            queryss << "modedescription, ";
            queryss << "to_char( starttime,'yyyy-mm-dd' ) as creationdate, ";
            queryss << "to_char( starttime, 'hh24:mi:ss' ) as creationtime, ";
            queryss << "to_char( endtime, 'hh24:mi:ss' ) as finishtime, ";
            queryss << "fecversionmajorid, ";
            queryss << "fecversionminorid, ";
            queryss << "fedversionmajorid, ";
            queryss << "fedversionminorid, ";
            queryss << "connectionversionmajorid, ";
            queryss << "connectionversionminorid, ";
            queryss << "dcuinfoversionmajorid, ";
            queryss << "dcuinfoversionminorid, ";
            queryss << "dcupsumapversionmajorid, ";
            queryss << "dcupsumapversionminorid, ";
            queryss << "maskversionmajorid, ";
            queryss << "maskversionminorid ";
            queryss << "from ";
            queryss <<  tablename.toStdString();
            queryss << " where runnumber=" << qPrintable(runIds[i].second);
        
            QString myQuery(queryss.str().c_str());
            QSqlQuery query(myQuery);
            
            while (query.next()) {
                partition       = query.value(0).toString();
                modeDescription = query.value(1).toString();
                creationDate    = query.value(2).toString();
                startTime       = query.value(3).toString();
                endTime         = query.value(4).toString();
                fecMajor        = query.value(5).toString();
                fecMinor        = query.value(6).toString();
                fedMajor        = query.value(7).toString();
                fedMinor        = query.value(8).toString();
                connMajor       = query.value(9).toString();
                connMinor       = query.value(10).toString();
                dcuinfoMajor    = query.value(11).toString();
                dcuinfoMinor    = query.value(12).toString();
                dcumapMajor     = query.value(13).toString();
                dcumapMinor     = query.value(14).toString();
                maskMajor       = query.value(15).toString();
                maskMinor       = query.value(16).toString();
            }

            tablename = "analysis";
            queryss.str("");
            queryss << "select distinct ";
            queryss << "versionmajorid, ";
            queryss << "versionminorid ";
            queryss << "from ";
            queryss <<  tablename.toStdString();
            queryss << " where analysisid = ( select max(analysisid) from analysis where runnumber = " << qPrintable(runIds[i].second) << ")";

            myQuery = queryss.str().c_str();
            QSqlQuery query2(myQuery);

            while (query2.next()) {
                analMajor       = query2.value(0).toString();
                analMinor       = query2.value(1).toString();
            }

            QString pname = "";
            QString pnameinfo = "";

            if      (partition.startsWith("TI")) pnameinfo = "TIB/TID";
            else if (partition.startsWith("TO")) pnameinfo = "TOB";
            else if (partition.startsWith("TP")) pnameinfo = "TEC+";
            else if (partition.startsWith("TM")) pnameinfo = "TEC-";

            if      (partition.startsWith("TI")) pname = "PartTIBD";
            else if (partition.startsWith("TO")) pname = "PartTOB";
            else if (partition.startsWith("TP")) pname = "PartTECP";
            else if (partition.startsWith("TM")) pname = "PartTECM";

            infoss << "<b>DB parameters for " << qPrintable(pnameinfo) << "</b><br/>";
            infoss << "Partition name : "  << qPrintable(partition)        << "<br/>";
            infoss << "Run number : "      << qPrintable(runIds[i].second) << "<br/>";
            infoss << "Cabling : "         << qPrintable(connMajor)        << "."   << qPrintable(connMinor)     << "<br/>";
            infoss << "FEC : "             << qPrintable(fecMajor)         << "."   << qPrintable(fecMinor)      << "<br/>";
            infoss << "FED : "             << qPrintable(fedMajor)         << "."   << qPrintable(fedMinor)      << "<br/>";
            infoss << "DCU : "             << qPrintable(dcuinfoMajor)     << "."   << qPrintable(dcuinfoMinor)  << "<br/>";
            infoss << "DCU PSU Map : "     << qPrintable(dcumapMajor)      << "."   << qPrintable(dcumapMinor)   << "<br/>";
            infoss << "Mask : "            << qPrintable(maskMajor)        << "."   << qPrintable(maskMinor)     << "<br/>";
            infoss << "Analysis : "        << qPrintable(analMajor)        << "."   << qPrintable(analMinor)     << "<br/>";
            infoss << "<br/>";

            partss << "\t" << qPrintable(pname) << " = cms.untracked.PSet("      << std::endl;
            partss << "\t\tForceCurrentState = cms.untracked.bool(False)," << std::endl;
            partss << "\t\tForceVersions = cms.untracked.bool(True),"      << std::endl;
            partss << "\t\tPartitionName = cms.untracked.string(\'"        << qPrintable(partition)        << "\')," << std::endl;
            partss << "\t\tRunNumber = cms.untracked.uint32("              << qPrintable(runIds[i].second) << "),"   << std::endl;
            partss << "\t\tCablingVersion = cms.untracked.vuint32("        << qPrintable(connMajor)        << ", "   << qPrintable(connMinor)     << ")," << std::endl;
            partss << "\t\tFecVersion = cms.untracked.vuint32("            << qPrintable(fecMajor)         << ", "   << qPrintable(fecMinor)      << ")," << std::endl;
            partss << "\t\tFedVersion = cms.untracked.vuint32("            << qPrintable(fedMajor)         << ", "   << qPrintable(fedMinor)      << ")," << std::endl;
            partss << "\t\tDcuDetIdsVersion = cms.untracked.vuint32("      << qPrintable(dcuinfoMajor)     << ", "   << qPrintable(dcuinfoMinor)  << ")," << std::endl;
            partss << "\t\tDcuPsuMapVersion = cms.untracked.vuint32("      << qPrintable(dcumapMajor)      << ", "   << qPrintable(dcumapMinor)   << ")," << std::endl;
            partss << "\t\tMaskVersion = cms.untracked.vuint32("           << qPrintable(maskMajor)        << ", "   << qPrintable(maskMinor)     << ")," << std::endl;
            partss << "\t\tApvTimingVersion = cms.untracked.vuint32("      << qPrintable(analMajor)        << ", "   << qPrintable(analMinor)     << ")," << std::endl;
            partss << "\t)," << std::endl;

        }

        infoss << "</html>" << std::endl;
        QTextCursor cursor(txtCurRunInfo->textCursor());
        cursor.insertHtml(infoss.str().c_str());

        return true;

    }

    else {

        //btnUpload->setEnabled(false);
 
        QString partition, modeDescription, creationDate, startTime, endTime, o2o;
        QString fecMajor, fecMinor, fedMajor, fedMinor, connMajor, connMinor, dcuinfoMajor, dcuinfoMinor, dcumapMajor, dcumapMinor, maskMajor, maskMinor, analysisid;
        QString cpsetpoint;
        
        QString tablename = "viewallrun";
        
        std::stringstream queryss;
        queryss << "select distinct ";
        queryss << "partitionname, ";
        queryss << "modedescription, ";
        queryss << "to_char( starttime,'yyyy-mm-dd' ) as creationdate, ";
        queryss << "to_char( starttime, 'hh24:mi:ss' ) as creationtime, ";
        queryss << "to_char( endtime, 'hh24:mi:ss' ) as finishtime, ";
        queryss << "fecversionmajorid, ";
        queryss << "fecversionminorid, ";
        queryss << "fedversionmajorid, ";
        queryss << "fedversionminorid, ";
        queryss << "connectionversionmajorid, ";
        queryss << "connectionversionminorid, ";
        queryss << "dcuinfoversionmajorid, ";
        queryss << "dcuinfoversionminorid, ";
        queryss << "dcupsumapversionmajorid, ";
        queryss << "dcupsumapversionminorid, ";
        queryss << "maskversionmajorid, ";
        queryss << "maskversionminorid, ";
        queryss << "analysisversionid ";
        queryss << "from ";
        queryss <<  tablename.toStdString();
        queryss << " where runnumber=" << qPrintable(currentRun);
        
        QString myQuery(queryss.str().c_str());
        QSqlQuery query(myQuery);
        
        while (query.next()) {
            partition       = query.value(0).toString();
            modeDescription = query.value(1).toString();
            creationDate    = query.value(2).toString();
            startTime       = query.value(3).toString();
            endTime         = query.value(4).toString();
            fecMajor        = query.value(5).toString();
            fecMinor        = query.value(6).toString();
            fedMajor        = query.value(7).toString();
            fedMinor        = query.value(8).toString();
            connMajor       = query.value(9).toString();
            connMinor       = query.value(10).toString();
            dcuinfoMajor    = query.value(11).toString();
            dcuinfoMinor    = query.value(12).toString();
            dcumapMajor     = query.value(13).toString();
            dcumapMinor     = query.value(14).toString();
            maskMajor       = query.value(15).toString();
            maskMinor       = query.value(16).toString();
            analysisid      = query.value(17).toString();
        }
        
        analysisType = modeDescription;

        std::stringstream infoss;
        infoss << "<html>" << std::endl;
        infoss << "<p>" << std::endl;
        infoss << "<b>About the run:</b>" << "<br/>";
        infoss << "Run Number : "         << qPrintable(currentRun)      << " (" << qPrintable(modeDescription) << ") <br/>";
        infoss << "Partition          : " << qPrintable(partition)       << "<br/>";
        infoss << "Created On    : "      << qPrintable(creationDate)    << " during " << qPrintable(startTime) << " to " << qPrintable(endTime) << "<br/>";
        infoss << std::endl;
        infoss << "</p>" << std::endl;
        
        infoss << "<b>DB Versions:" << "</b>" << "<br/>";
        
        QTextCursor cursor(txtCurRunInfo->textCursor());
        cursor.insertHtml(infoss.str().c_str());
        
        cursor.insertTable(6,2);
        cursor.insertText("FEC");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(fecMajor+"."+fecMinor);
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText("FED");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(fedMajor+"."+fedMinor);
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText("CONN");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(connMajor+"."+connMinor);
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText("DCU  INFO");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(dcuinfoMajor+"."+dcuinfoMinor);
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText("DCU-PSU MAP");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(dcumapMajor+"."+dcumapMinor);
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText("MASK");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(maskMajor+"."+maskMinor);
        cursor.movePosition(QTextCursor::NextCell);
        
        std::stringstream info2ss;
        info2ss << "</html>" << std::endl;
        cursor.movePosition(QTextCursor::End);
        cursor.insertHtml(info2ss.str().c_str());

        return true;
    }
}

