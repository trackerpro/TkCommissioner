#include "frmdetails.h"
#include "frmtrends.h"
#include "frmsource.h"
#include "frmdbtag.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDate>
#include <QTime>
#include <QStandardItem>
#include <QModelIndex>
#include <QList>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDateTime>
#include <QMap>
#include <QPair>

#include <TBranch.h>
#include <TGraph.h>

#include "Debug.h"
#include "cmssw/SiStripFedKey.h"
#include "cmssw/SiStripFecKey.h"

SelectionDetails::SelectionDetails(QWidget* p, const TreeViewerRunInfo& tinfo): 
    QConnectedTabWidget(p)
{
    setupUi(this);

    selModel = new QStandardItemModel(0, 17, this);
    listSelection->setModel(selModel);
    selModel = selModel;

    run    = tinfo.getCurrentRunNumber();
    refrun = tinfo.getReferenceRunNumber();
}

SelectionDetails::~SelectionDetails() {
}

void SelectionDetails::populate(TTree* tree, const QVector<int>& sel, const QString& varname) {
    var = varname;
    QString myQuery;        
    QTextStream queryss(&myQuery);
    queryss << "SELECT DISTINCT ticketId, deviceId, runNumber, tagDescription, tkComment, tkAuthor, timeStampInsert, tkanalysislog.tagNumber"
            << " FROM TkAnalysisLog, TkAnalysisTag"
            << " WHERE TkAnalysisLog.tagNumber = TkAnalysisTag.tagNumber"
            << " AND TkAnalysisLog.timeStampCloseTicket IS NULL" 
            << " order by ticketid, runnumber";
    QSqlQuery query(myQuery);

    QString myTagQuery;        
    QTextStream tagqueryss(&myTagQuery);
    tagqueryss << "select distinct TAGNUMBER,TAGDESCRIPTION from TkAnalysisTag where tagnumber <> 0 order by tagnumber";
    QSqlQuery tagquery(myTagQuery);

    while(tagquery.next()) cmbTagList->addItem(tagquery.value(1).toString(), tagquery.value(0).toString()); 

    QStringList headerLabels;
    headerLabels << "DeviceId";
    headerLabels << varname.toStdString().c_str();
    headerLabels << "Power";
    headerLabels << "Detid";
    headerLabels << "FecCrate";
    headerLabels << "Fec";
    headerLabels << "Ring";
    headerLabels << "Ccu";
    headerLabels << "CcuArrangement";
    headerLabels << "I2CChannel";
    headerLabels << "I2CAddress";
    headerLabels << "lasChan";
    headerLabels << "FedId";
    headerLabels << "FeUnit";
    headerLabels << "FeChan";
    headerLabels << "FeApv";
    headerLabels << "Selected";
    selModel->setHorizontalHeaderLabels(headerLabels);

    TBranch* bdevId          = tree->GetBranch("DeviceId");
    TBranch* bvar            = tree->GetBranch(varname.toStdString().c_str());
    TBranch* bpower          = tree->GetBranch("Power");
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
    double var            = 0.0;
    double power          = 0.0;
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
    bvar           ->SetAddress(&var);
    bpower         ->SetAddress(&power);
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
        QList<QStandardItem*> list;
        bdevId         ->GetEvent(i);
        bvar           ->GetEvent(i);
        bpower         ->GetEvent(i);
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

        QStandardItem* idevId          = new QStandardItem(QString::number(devId, 'g', 20));
        QStandardItem* ivar            = new QStandardItem(QString::number(var));
        QStandardItem* ipower          = new QStandardItem(QString::number(power));
        QStandardItem* idetId          = new QStandardItem(QString::number(detId, 'g', 20));
        QStandardItem* iFecCrate       = new QStandardItem(QString::number(FecCrate));
        QStandardItem* iFec            = new QStandardItem(QString::number(Fec));
        QStandardItem* iRing           = new QStandardItem(QString::number(Ring));
        QStandardItem* iCcu            = new QStandardItem(QString::number(Ccu));
        QStandardItem* iCcuArrangement = new QStandardItem(QString::number(CcuArrangement));
        QStandardItem* iI2CChannel     = new QStandardItem(QString::number(I2CChannel));
        QStandardItem* iI2CAddress     = new QStandardItem(QString::number(I2CAddress));
        QStandardItem* ilasChan        = new QStandardItem(QString::number(lasChan));
        QStandardItem* iFedId          = new QStandardItem(QString::number(FedId));
        QStandardItem* iFeUnit         = new QStandardItem(QString::number(FeUnit));
        QStandardItem* iFeChan         = new QStandardItem(QString::number(FeChan));
        QStandardItem* iFeApv          = new QStandardItem(QString::number(FeApv));
        QStandardItem* iSel            = new QStandardItem(QString::number(sel[i]));

        ivar           ->setTextAlignment(Qt::AlignHCenter);
        ipower         ->setTextAlignment(Qt::AlignHCenter);
        idetId         ->setTextAlignment(Qt::AlignHCenter);
        iFecCrate      ->setTextAlignment(Qt::AlignHCenter);
        iFec           ->setTextAlignment(Qt::AlignHCenter);
        iRing          ->setTextAlignment(Qt::AlignHCenter);
        iCcu           ->setTextAlignment(Qt::AlignHCenter);
        iCcuArrangement->setTextAlignment(Qt::AlignHCenter);
        iI2CChannel    ->setTextAlignment(Qt::AlignHCenter);
        iI2CAddress    ->setTextAlignment(Qt::AlignHCenter);
        ilasChan       ->setTextAlignment(Qt::AlignHCenter);
        iFedId         ->setTextAlignment(Qt::AlignHCenter);
        iFeUnit        ->setTextAlignment(Qt::AlignHCenter);
        iFeChan        ->setTextAlignment(Qt::AlignHCenter);
        iFeApv         ->setTextAlignment(Qt::AlignHCenter);
        iSel           ->setTextAlignment(Qt::AlignHCenter);

        idevId->setCheckable(true);

        query.first();
        while(query.next()) {
            if (query.value(1).toDouble() == devId) {
                QString strtemplate("Ticket Nr: %1(%3)\n from Run Nr: %2\n Author: %5\n Date: %6 Time: %7\n %4");
                QString str = strtemplate.arg(query.value(0).toInt())
                                         .arg(query.value(2).toInt())
                                         .arg(query.value(3).toString())
                                         .arg(query.value(4).toString())
                                         .arg(query.value(5).toString())
                                         .arg(query.value(6).toDate().toString())
                                         .arg(query.value(6).toTime().toString());
                idevId->appendRow(new QStandardItem(str));
            }
        }

        if (sel[i] == 0 && idevId->rowCount() == 0) continue;

        list.append(idevId         );
        list.append(ivar           );
        list.append(ipower         );
        list.append(idetId         );
        list.append(iFecCrate      );
        list.append(iFec           );
        list.append(iRing          );
        list.append(iCcu           );
        list.append(iCcuArrangement);
        list.append(iI2CChannel    );
        list.append(iI2CAddress    );
        list.append(ilasChan       );
        list.append(iFedId         );
        list.append(iFeUnit        );
        list.append(iFeChan        );
        list.append(iFeApv         );
        list.append(iSel           );
        selModel->appendRow(list);
    }

    listSelection->hideColumn(16);
    for (int i = 0; i < selModel->rowCount(); i++) {
        if ((selModel->item(i, 16)->text()).toInt() == 0) listSelection->setRowHidden(i, QModelIndex(), true); 
    }

    listSelection->expandAll();
    for (int i = 0; i < 16; i++) listSelection->resizeColumnToContents(i);
    listSelection->collapseAll();

    bdevId          ->ResetAddress();
    bvar            ->ResetAddress();
    bpower          ->ResetAddress();
    bdetId          ->ResetAddress();
    bFecCrate       ->ResetAddress();
    bFec            ->ResetAddress();
    bRing           ->ResetAddress();
    bCcu            ->ResetAddress();
    bCcuArrangement ->ResetAddress();
    bI2CChannel     ->ResetAddress();
    bI2CAddress     ->ResetAddress();
    blasChan        ->ResetAddress();
    bFedId          ->ResetAddress();
    bFeUnit         ->ResetAddress();
    bFeChan         ->ResetAddress();
    bFeApv          ->ResetAddress();

}

void SelectionDetails::on_btnSelectAll_clicked() {
    for (int i = 0; i < selModel->rowCount(); i++) {
        if (!listSelection->isRowHidden(i, QModelIndex())) selModel->item(i, 0)->setCheckState(Qt::Checked);
    }
}

void SelectionDetails::on_btnUnselectAll_clicked() {
    for (int i = 0; i < selModel->rowCount(); i++) {
        if (!listSelection->isRowHidden(i, QModelIndex())) selModel->item(i, 0)->setCheckState(Qt::Unchecked);
    }
}

void SelectionDetails::on_btnSelectTagged_clicked() {
    for (int i = 0; i < selModel->rowCount(); i++) {
        if (!listSelection->isRowHidden(i, QModelIndex()) && selModel->item(i, 0)->rowCount() > 0) selModel->item(i, 0)->setCheckState(Qt::Checked);
    }
}

void SelectionDetails::on_btnUnselectTagged_clicked() {
    for (int i = 0; i < selModel->rowCount(); i++) {
        if (!listSelection->isRowHidden(i, QModelIndex()) && selModel->item(i, 0)->rowCount() > 0) selModel->item(i, 0)->setCheckState(Qt::Unchecked);
    }
}

void SelectionDetails::on_btnShowTaggedSelected_clicked() {
    for (int i = 0; i < selModel->rowCount(); i++) {
        if (selModel->item(i, 0)->rowCount() == 0) listSelection->setRowHidden(i, QModelIndex(), true);
        if ((selModel->item(i, 16)->text()).toInt() == 0) listSelection->setRowHidden(i, QModelIndex(), true );
    }
}

void SelectionDetails::on_btnShowAllSelected_clicked() {
    for (int i = 0; i < selModel->rowCount(); i++) {
        if ((selModel->item(i, 16)->text()).toInt() != 0) listSelection->setRowHidden(i, QModelIndex(), false);
        if ((selModel->item(i, 16)->text()).toInt() == 0) listSelection->setRowHidden(i, QModelIndex(), true );
    }        
}

void SelectionDetails::on_btnShowTaggedAll_clicked() {
    for (int i = 0; i < selModel->rowCount(); i++) {
        if (selModel->item(i, 0)->rowCount() == 0) listSelection->setRowHidden(i, QModelIndex(), true);
        if ((selModel->item(i, 16)->text()).toInt() == 0) listSelection->setRowHidden(i, QModelIndex(), false);
    }        
}

void SelectionDetails::on_btnAddTag_clicked() {
    /*
    TagCreator* tagger = new TagCreator();
    tagger->show();
    */
}

void SelectionDetails::on_btnShowSource_clicked() {
    QVector<QPair<QString, QString> > devices;
    QVector<QPair<unsigned, unsigned> > keys;
    for (int i = 0; i < selModel->rowCount(); i++) {
        if (selModel->item(i, 0)->checkState() == Qt::Checked) {
            devices.push_back(QPair<QString, QString>(selModel->item(i, 3)->text(), selModel->item(i, 10)->text()));
            SiStripFecKey feckey(
                selModel->item(i, 4 )->text().toInt(),
                selModel->item(i, 5 )->text().toInt(),
                selModel->item(i, 6 )->text().toInt(),
                selModel->item(i, 7 )->text().toInt(),
                selModel->item(i, 9 )->text().toInt(),
                selModel->item(i, 11)->text().toInt()+1,
                selModel->item(i, 10)->text().toInt()
            );
            SiStripFedKey fedkey(
                selModel->item(i, 12)->text().toInt(),
                selModel->item(i, 13)->text().toInt(),
                selModel->item(i, 14)->text().toInt(),
                selModel->item(i, 15)->text().toInt()
            );
            keys.push_back(QPair<unsigned, unsigned>(feckey.key(), fedkey.key()));
        }
    }

    SourceDisplay* source = new SourceDisplay(NULL, run, refrun, devices, keys);
    emit showTabSignal(source, "Source");
}

void SelectionDetails::on_btnShowTrend_clicked() {
    Trends* trends = new Trends;

    QSqlQuery runinfoquery(QString("select runnumber, modedescription from viewallrun left outer join analysis using(runnumber) where runnumber=")+run);
    QString runtype;
    QString runtypetable;
    QString plotvar;
    while(runinfoquery.next()) runtype = runinfoquery.value(1).toString();
    if      (runtype == "TIMING")                                              runtypetable = "ANALYSISTIMING";
    else if (runtype == "OPTOSCAN" || runtype == "GAINSCAN")                   runtypetable = "ANALYSISOPTOSCAN";
    else if (runtype == "VPSPSCAN")                                            runtypetable = "ANALYSISVPSPSCAN";
    else if (runtype == "VERY_FAST_CONNECTION" || runtype == "FASTFEDCABLING") runtypetable = "ANALYSISFASTFEDCABLING";
    else if (runtype == "PEDESTALS" || runtype == "PEDESTAL")                  runtypetable = "ANALYSISPEDESTALS";
    else return;
    plotvar = runtypetable + "." + var;

    QMap<QPair<QString, QString>, TGraph*> graphMap;

    for (int i = 0; i < selModel->rowCount(); i++) {
        if (selModel->item(i, 0)->checkState() == Qt::Checked) {
            QString myQuery;
            QTextStream queryss(&myQuery);

            if (runtype == "PEDESTALS" || runtype == "PEDESTAL") {
            
              queryss << "with input as ( select ? fecslot, ? ringslot, ? ccuaddress, ? i2cchannel, ? i2caddress from dual) "
                  << "select viewdevice.fecslot, viewdevice.ringslot, viewdevice.ccuaddress,viewdevice.i2cchannel, "
                  << qPrintable(plotvar)      << ", viewallrun.runnumber, starttime "
                  << "from "                  << qPrintable(runtypetable)                 << " join analysis on " 
                  << qPrintable(runtypetable) << ".analysisid=analysis.analysisid "
                  << "join viewdevice on "    << qPrintable(runtypetable)                 << ".deviceid=viewdevice.deviceid join apvfec on apvfec.deviceid=viewdevice.deviceid join viewallrun "
                  << " on analysis.runnumber=viewallrun.runnumber and " 
                  << " apvfec.versionmajorid=viewallrun.FECVERSIONMAJORID and " 
                  << "apvfec.versionminorid=viewallrun.FECVERSIONMINORID " 
                  << " where apvmode = ( " 
                  << " select distinct apvmode from apvfec join viewdevice using(deviceid) " 
                  << "join viewallrun on " 
                  << " apvfec.versionmajorid=viewallrun.FECVERSIONMAJORID and " 
                  << "apvfec.versionminorid=viewallrun.FECVERSIONMINORID and fecslot = ( select fecslot from input) and ringslot = ( select ringslot from input) and ccuaddress = ( select ccuaddress from input) and i2cchannel = ( select i2cchannel from input) and i2caddress = ( select i2caddress from input) and viewallrun.runnumber = " << run.toInt() << ")"
                  << "and fecslot= ( select fecslot from input) and "
                  << "ringslot =  (select ringslot from input ) and " 
                  << "ccuaddress= (select ccuaddress from input ) and "
                  << "i2cchannel= (select i2cchannel from input ) and "
                  << "i2caddress= (select i2caddress from input ) order by runnumber";
            
            
            } else {
              
              queryss << "select viewdevice.fecslot, viewdevice.ringslot, viewdevice.ccuaddress,viewdevice.i2cchannel, "
                  << qPrintable(plotvar)      << ", runnumber, starttime "
                  << "from "                  << qPrintable(runtypetable)                 << " join analysis on " 
                  << qPrintable(runtypetable) << ".analysisid=analysis.analysisid "
                  << "join viewdevice on "    << qPrintable(runtypetable)                 << ".deviceid=viewdevice.deviceid join run using(runnumber) "
                  << "where fecslot="         << "? and "
                  << "ringslot="              << "? and "
                  << "ccuaddress="            << "? and "
                  << "i2cchannel="            << "? and "
                  << "i2caddress="            << "? order by runnumber";
              
            }

            QVector<QPair<double, double> > graphEntries;
            QSqlQuery query;
            query.prepare(myQuery);
            query.addBindValue((selModel->item(i, 5)->text()).toInt());
            query.addBindValue((selModel->item(i, 6)->text()).toInt());
            query.addBindValue((selModel->item(i, 7)->text()).toInt());
            query.addBindValue((selModel->item(i, 9)->text()).toInt());
            query.addBindValue((selModel->item(i,10)->text()).toInt());
            query.exec();
            if( query.lastError().isValid() ) {
                if (Debug::Inst()->getEnabled()) qDebug() << query.lastError().text();
            } 

            while (query.next()) graphEntries.push_back(QPair<double, double>(query.value(4).toDouble(), double(query.value(6).toDateTime().toMSecsSinceEpoch()/1000)-9466.848e5));
            int n = graphEntries.size();
            double* xvals = new double[n];
            double* yvals = new double[n];
            for (int j = 0; j < n; j++) {
                xvals[j] = graphEntries[j].second;
                yvals[j] = graphEntries[j].first;
            }

            // need a check for zero entries here
            TGraph* gr = new TGraph(n, xvals, yvals);
            graphMap[QPair<QString, QString>(selModel->item(i, 3)->text(), selModel->item(i, 10)->text())] = gr;
        }
    }

    trends->getSelectionInfo(graphMap);
    emit showTabSignal(trends, "Trends");
}
