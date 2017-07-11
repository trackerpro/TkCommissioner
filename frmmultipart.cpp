// Qt includes
#include <QtGui> 
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVariant>
#include <QModelIndex>
#include <QMessageBox>
#include <QProcess>

// project includes
#include "frmmultipart.h"
#include "frmtreeviewer.h"
#include "TreeBuilder.h"
#include "Debug.h"
#include "DbConnection.h"

MultiPart::MultiPart(QVector<QString>* tf, QWidget * parent): 
    QConnectedTabWidget(parent)
{
    setupUi(this); 
    tfiles = tf;
    prepareRunTypes();        
    preparePartitions();        
    prepareRuns();        
}

MultiPart::~MultiPart() {
}

void MultiPart::preparePartitionList(const QString& partition, QComboBox * comboBox) {
    QString squery = "select partitionname from viewallrun where local=1 group by partitionname order by max(starttime) desc";
    QSqlQuery query(squery);

    int counter = 0;
    while (query.next()) { 
        QString partitionName = query.value(0).toString();
        if (partitionName.startsWith(partition)) {
            comboBox->insertItem(counter, partitionName);
            counter++;
        }
    }

    comboBox->setCurrentIndex(0);
}

void MultiPart::prepareRunTypes() {

    cmbRunType->insertItem(0, "TIMING"  );
    cmbRunType->insertItem(1, "PEDESTAL");
    cmbRunType->insertItem(2, "GAINSCAN");
    cmbRunType->insertItem(3, "VPSPSCAN");

}

void MultiPart::preparePartitions() {
    preparePartitionList("TI", cmbTibPartition);
    preparePartitionList("TO", cmbTobPartition);
    preparePartitionList("TP", cmbTecpPartition);
    preparePartitionList("TM", cmbTecmPartition);
}

void MultiPart::prepareRunList(const QString& partitionName, const QString& runType, QComboBox * comboBox) {
    comboBox->clear();

    QString squery = QString("select distinct runnumber, modedescription, case when analysisid is not null then 1 else 0 end as analyzed, case when comments = 'BAD' then 1 else 0 end as badflag from viewallrun left outer join analysis using(runnumber) where partitionname='%1' and local = 1 order by RUNNUMBER desc").arg(partitionName);
    QSqlQuery query(squery);

    int counter = 0;
    while (query.next()) {
        QString runNumber       = query.value(0).toString();
        QString modeDescription = query.value(1).toString();
        bool    analyzed        = query.value(2).toBool();
        bool    badFlag         = query.value(3).toBool();

        if (modeDescription != runType) continue;
        if (!analyzed) continue;
        if (badFlag) continue;
        comboBox->insertItem(counter, runNumber);
        counter++;
    }
 
    comboBox->setCurrentIndex(0);
}

void MultiPart::prepareRuns() {
    prepareRunList(cmbTibPartition->currentText() , QString::QString(cmbRunType->currentText()), cmbRunTib);
    prepareRunList(cmbTobPartition->currentText() , QString::QString(cmbRunType->currentText()), cmbRunTob);
    prepareRunList(cmbTecpPartition->currentText(), QString::QString(cmbRunType->currentText()), cmbRunTecp);	
    prepareRunList(cmbTecmPartition->currentText(), QString::QString(cmbRunType->currentText()), cmbRunTecm);
}

void MultiPart::prepareDbTable(const QString& part, const QString& run) {

    QString fecMajor, fecMinor, fedMajor, fedMinor, connMajor, connMinor, dcuinfoMajor, dcuinfoMinor, dcumapMajor, dcumapMinor, maskMajor, maskMinor;
    QString analMajor, analMinor;

    std::stringstream queryss;
    queryss << "select distinct ";
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
    queryss << "from viewallrun";
    queryss << " where runnumber=" << qPrintable(run);
        
    QString myQuery = queryss.str().c_str();
    QSqlQuery query(myQuery);
    
    while (query.next()) {
        fecMajor        = query.value(0).toString();
        fecMinor        = query.value(1).toString();
        fedMajor        = query.value(2).toString();
        fedMinor        = query.value(3).toString();
        connMajor       = query.value(4).toString();
        connMinor       = query.value(5).toString();
        dcuinfoMajor    = query.value(6).toString();
        dcuinfoMinor    = query.value(7).toString();
        dcumapMajor     = query.value(8).toString();
        dcumapMinor     = query.value(9).toString();
        maskMajor       = query.value(10).toString();
        maskMinor       = query.value(11).toString();
    }

    queryss.str("");
    queryss << "select distinct ";
    queryss << "versionmajorid, ";
    queryss << "versionminorid ";
    queryss << "from analysis";
    queryss << " where analysisid = ( select max(analysisid) from analysis where runnumber = " << qPrintable(run) << ")";
    
    myQuery = queryss.str().c_str();
    QSqlQuery query2(myQuery);
    
    while (query2.next()) {
        analMajor       = query2.value(0).toString();
        analMinor       = query2.value(1).toString();
    }

    if (part == "TI") {
        lblTibFec   ->setText(fecMajor     + "." + fecMinor);
        lblTibFed   ->setText(fedMajor     + "." + fedMinor);
        lblTibConn  ->setText(connMajor    + "." + connMinor);
        lblTibMask  ->setText(maskMajor    + "." + maskMinor);
        lblTibDcu   ->setText(dcuinfoMajor + "." + dcuinfoMinor);
        lblTibDcupsu->setText(dcumapMajor  + "." + dcumapMinor);
        lblTibAna   ->setText(analMajor    + "." + analMinor);
    }
    else if (part == "TO") {
        lblTobFec    ->setText(fecMajor     + "." + fecMinor);
        lblTobFed    ->setText(fedMajor     + "." + fedMinor);
        lblTobConn   ->setText(connMajor    + "." + connMinor);
        lblTobMask   ->setText(maskMajor    + "." + maskMinor);
        lblTobDcu    ->setText(dcuinfoMajor + "." + dcuinfoMinor);
        lblTobDcupsu ->setText(dcumapMajor  + "." + dcumapMinor);
        lblTobAna    ->setText(analMajor    + "." + analMinor);
    }
    else if (part == "TP") {
        lblTecpFec    ->setText(fecMajor     + "." + fecMinor);
        lblTecpFed    ->setText(fedMajor     + "." + fedMinor);
        lblTecpConn   ->setText(connMajor    + "." + connMinor);
        lblTecpMask   ->setText(maskMajor    + "." + maskMinor);
        lblTecpDcu    ->setText(dcuinfoMajor + "." + dcuinfoMinor);
        lblTecpDcupsu ->setText(dcumapMajor  + "." + dcumapMinor);
        lblTecpAna    ->setText(analMajor    + "." + analMinor);
    }
    else if (part == "TM") {
        lblTecmFec    ->setText(fecMajor     + "." + fecMinor);
        lblTecmFed    ->setText(fedMajor     + "." + fedMinor);
        lblTecmConn   ->setText(connMajor    + "." + connMinor);
        lblTecmMask   ->setText(maskMajor    + "." + maskMinor);
        lblTecmDcu    ->setText(dcuinfoMajor + "." + dcuinfoMinor);
        lblTecmDcupsu ->setText(dcumapMajor  + "." + dcumapMinor);
        lblTecmAna    ->setText(analMajor    + "." + analMinor);
    }

}

void MultiPart::on_cmbRunType_currentIndexChanged(const QString&) { 
    prepareRuns(); 
}

void MultiPart::on_cmbRunTib_currentIndexChanged(const QString&) { 
    prepareDbTable("TI", cmbRunTib->currentText()); 
}

void MultiPart::on_cmbRunTob_currentIndexChanged(const QString&) { 
    prepareDbTable("TO", cmbRunTob->currentText()); 
}

void MultiPart::on_cmbRunTecp_currentIndexChanged(const QString&) { 
    prepareDbTable("TP", cmbRunTecp->currentText()); 
}

void MultiPart::on_cmbRunTecm_currentIndexChanged(const QString&) { 
    prepareDbTable("TM", cmbRunTecm->currentText()); 
}

void MultiPart::on_btnUpdate_clicked() {
    preparePartitions();
    prepareRuns();

    prepareDbTable("TI", cmbRunTib->currentText()); 
    prepareDbTable("TO", cmbRunTob->currentText()); 
    prepareDbTable("TP", cmbRunTecp->currentText()); 
    prepareDbTable("TM", cmbRunTecm->currentText()); 
}

void MultiPart::on_btnShow_clicked() {
    QString currentPartitionName = cmbRunType->currentText() + "*";
    currentPartitionName += cmbTibPartition->currentText()   + "#" + cmbRunTib->currentText()  + "*";
    currentPartitionName += cmbTobPartition->currentText()   + "#" + cmbRunTob->currentText()  + "*";
    currentPartitionName += cmbTecpPartition->currentText()  + "#" + cmbRunTecp->currentText() + "*";
    currentPartitionName += cmbTecmPartition->currentText()  + "#" + cmbRunTecm->currentText();

    tfiles->push_back(QString("/opt/cmssw/shifter/avartak/data/tmp/timingo2otmp_")+QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss_zzz")+QString(".root")); 
    TreeViewer *treeview = new TreeViewer(tfiles->back());

    bool addRunResult = treeview->addRun(currentPartitionName, QString::number(sistrip::MULTIPART), true);
    
    if (addRunResult) emit showTabSignal(treeview, "Tree View");
}
