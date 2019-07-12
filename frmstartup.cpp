// Qt includes
#include <QtGui> 
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVariant>
#include <QModelIndex>
#include <QMessageBox>
#include <QProcess>
#include <QDir>

// project includes
#include "frmstartup.h"
#include "frmtreeviewer.h"
#include "frmterminal.h"
#include "frmmultipart.h"
#include "frmprepareglobal.h"
#include "TreeBuilder.h"
#include "Debug.h"
#include "DbConnection.h"

Startup::Startup(QWidget * parent): 
    QConnectedTabWidget(parent)
{
    setupUi(this); 

    // set up runView ItemModel, headers etc
    runModel = new QStandardItemModel(0, 2,this);
    runView->setModel(runModel);
    runView->setSelectionMode(QAbstractItemView::SingleSelection);
    runView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    
    // set up partitionView ItemModel, headers etc
    partitionModel = new QStandardItemModel(0, 2,this);
    partitionView->setModel(partitionModel);
    partitionView->setSelectionMode(QAbstractItemView::SingleSelection);
    partitionView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    
    // connect signals from change of selection respective slots
    connect(partitionView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(partitionChanged(QModelIndex,QModelIndex)));
    connect(runView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(runChanged(QModelIndex,QModelIndex)));
    
    // method name says it all
    populatePartitions();

    // Select the top most partition in the partition view, which then triggers the run view for that partition to be filled
    partitionView->selectRow(0);

    QString user = DbConnection::Inst()->dbConnection().userName();
    if (QString::compare(user, tr("cms_tracker_tif3"), Qt::CaseInsensitive) != 0) {
        QMessageBox::critical(0, tr("Startup"), tr("You are using a database account which does not have write permissions!\n\nRun flagging will be disabled") );      
        btnMarkBad->setEnabled(false);
    }
}

Startup::~Startup() {
    deleteTmpFiles();
    delete partitionModel;
    delete runModel;
}

void Startup::deleteTmpFiles() {
    for (int i = 0; i < tmpfiles.size(); i++) {
        QProcess rmproc;
        rmproc.start("rm", QStringList() << tmpfiles[i]);
        bool wait = true;
        while(wait) {
            wait = !rmproc.waitForFinished();
        } 
    }
}

void Startup::addItem(QStandardItemModel* model, const QString &first, const QString &second, bool isRunItem, bool analyzed, bool itemBad) {
    QList<QStandardItem*> list;

    QStandardItem* firstItem = new QStandardItem(first);
    firstItem->setEditable(false);
    if (itemBad) {
        firstItem->setForeground(Qt::red);
        firstItem->setBackground(QBrush(Qt::gray));
        firstItem->setToolTip(tr("Run marked as bad in database"));
    }
    if ( analyzed && isRunItem) firstItem->setIcon(QIcon("images/check-icon.png"));
    if (!analyzed && isRunItem) firstItem->setIcon(QIcon("images/cross-icon.png"));
    list.append(firstItem);

    QStandardItem* secondItem = new QStandardItem(second);
    secondItem->setEditable(false);
    if (itemBad && isRunItem) {
        secondItem->setForeground(Qt::red);
        secondItem->setBackground(QBrush(Qt::gray));
        secondItem->setToolTip(tr("Run marked as bad in database"));
    }
    list.append(secondItem);

    model->appendRow(list);
}

void Startup::populatePartitions() {
    QString squery = "select partitionname, to_char(  max(starttime),'yyyy-mm-dd' )  as CHANGEDATE from viewallrun where local=1 group by partitionname order by max(starttime) desc";
    QSqlQuery query(squery);
    partitionModel->clear();

    while (query.next()) { 
        QString partitionName = query.value(0).toString();
        QString changeDate    = query.value(1).toString() ;
        if (!partitionName.isEmpty()) addItem(partitionModel, partitionName, changeDate);
    }

    partitionModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Partition"));
    partitionModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
}

void Startup::populateRuns(const QString &partitionName) {
    QString squery = QString("select distinct runnumber, modedescription, case when analysisid is not null then 1 else 0 end as analyzed, case when comments = 'BAD' then 1 else 0 end as badflag from viewallrun left outer join analysis using(runnumber) where partitionname='%1' and local = 1 order by RUNNUMBER desc").arg(partitionName);
    QSqlQuery query(squery);
    runModel->clear();
    while (query.next()) {
        QString runNumber       = query.value(0).toString();
        QString modeDescription = query.value(1).toString() ;
        bool    analyzed        = query.value(2).toBool() ;
        bool    badFlag         = query.value(3).toBool() ;
        if (!runNumber.isEmpty()) addItem(runModel, runNumber, modeDescription, true, analyzed, badFlag);
    } 

    runModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Run Number"));
    runModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Mode"));

    btnViewResults->setEnabled(false);
    btnAnalyze->setEnabled(false);
}

void Startup::partitionChanged(QModelIndex current, QModelIndex) {
    currentPartitionName = partitionModel->item(current.row(),0)->text();
    populateRuns(currentPartitionName);
}

void Startup::runChanged(QModelIndex current, QModelIndex) {
    QString runNumber = runModel->item(current.row(),0)->text();

    QString squery = QString("select case when analysisid is not null then 1 else 0 end as analyzed from analysis where runnumber= %1 ").arg(runNumber);
    QSqlQuery query(squery);
    bool isAnalyzed = false;
    while (query.next()) isAnalyzed = query.value(0).toBool();

    btnViewResults->setEnabled(isAnalyzed);
    btnAnalyze->setEnabled(true);
}

void Startup::on_btnUpdatePartitions_clicked() {
    populatePartitions();
    partitionView->clearSelection();
    runView->clearSelection();
    partitionView->selectRow(0);
}

void Startup::on_btnUpdateRuns_clicked() {
    populateRuns(currentPartitionName);
    runView->clearSelection();
}

void Startup::on_btnState_clicked() {
    if (cmbState->currentText() == "Select state...") return;

    if (Debug::Inst()->getEnabled()) qDebug() << "Creating tree from current state for partition " << qPrintable(currentPartitionName) << "\n";
    tmpfiles.push_back(QString("/exports/slc7/tkCommissionerData/tmp/curstatetmp_")+QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss_zzz")+QString(".root")); 
    TreeViewer *treeview = new TreeViewer(tmpfiles.back());

    bool addRunResult = false;
    if (cmbState->currentText() == "Current State") {
      TreeBuilder::Inst()->getState(currentPartitionName, sistrip::CURRENTSTATE);
      addRunResult = treeview->addRun(currentPartitionName, QString::number(sistrip::CURRENTSTATE), true);
    } 
    else if (cmbState->currentText() == "Last O2O'ed State") {
        TreeBuilder::Inst()->getState(currentPartitionName,sistrip::LASTO2O);
        addRunResult = treeview->addRun(currentPartitionName, QString::number(sistrip::LASTO2O), true);
    }
    
    if (addRunResult) emit showTabSignal(treeview, "Tree View");
}

void Startup::on_btnViewResults_clicked() {
    QModelIndexList runList = runView->selectionModel()->selectedRows();
    if (runList.size() != 1) {
        if (Debug::Inst()->getEnabled()) qDebug() << "More than one run selected. This is not allowed. Quitting ... \n";
        return;
    }
    QStandardItem *run = runModel->itemFromIndex(runList.at(0));
    QString runNumber = run->text();

    tmpfiles.push_back(QString("/exports/slc7/tkCommissionerData/tmp/analysistmp_")+QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss_zzz")+QString(".root")); 
    TreeViewer *treeview = new TreeViewer(tmpfiles.back(), chkUseCache->isChecked());
    if (treeview->addRun(currentPartitionName, runNumber, true)) emit showTabSignal(treeview, "Tree View");
}

void Startup::on_btnAnalyze_clicked() {
    QModelIndexList runList = runView->selectionModel()->selectedRows();
    if (runList.size() != 1) {
        if (Debug::Inst()->getEnabled()) qDebug() << "More than one run selected. This is not allowed. Quitting ... \n";
        return;
    }
    QStandardItem *run = runModel->itemFromIndex(runList.at(0));
    QString runNumber = run->text();
    if (runNumber == "" || currentPartitionName == "") {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to obtain run information. Quitting ... \n";
        return;
    }

    bool upload = chkUploadConfiguration->isChecked();
    bool uploadAnal = chkUploadAnalysis->isChecked();
    bool useClient = chkUseClient->isChecked();
    bool saveClient = chkSaveClient->isChecked();
    
    QStringList commandArgs;
    QString uploadString;
    QString uploadAnalString;
    QString useClientString;
    QString saveClientString;
    QString disableModulesString;
    
    if (upload)     uploadString = "true";
    else            uploadString = "false";
    
    if (uploadAnal) uploadAnalString = "true";
    else            uploadAnalString = "false";
    
    if (useClient)  useClientString="true";
    else            useClientString="false";
    
    if (saveClient) saveClientString="true";
    else            saveClientString="false";   
    
    disableModulesString="false";   
      
    if (upload) {
        if (QMessageBox::question(NULL, QObject::tr("Confirmation"), QObject::tr("You are going to upload run analysis results to the configuration database. You should have already run the same analysis and verified the quality of the run. Do you want to continue?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;
    }
      
    if (upload && (!uploadAnal)) {
        if (QMessageBox::question(NULL, QObject::tr("Warning"), QObject::tr("You asked to upload the results of the analysis to the configuration database. But you disabled the upload to the analysis database. This is bad. Do you want to continue?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;
    }
    
    commandArgs << runNumber << uploadString << uploadAnalString << currentPartitionName << useClientString << disableModulesString << saveClientString;
    TkTerminal* terminal = new TkTerminal();

    QDir fffdir("/raid/fff");
    QStringList runFilter;
    runFilter << "*run"+runNumber+"*";
    QStringList runs = fffdir.entryList(runFilter, QDir::Dirs);

    std::cout<<"Run analysis scripts with: "<<qPrintable(runNumber)<<" "<<qPrintable(uploadString)<<" "<<qPrintable(uploadAnalString)<<" "<<qPrintable(currentPartitionName)<<" "<<qPrintable(useClientString)<<" "<<qPrintable(disableModulesString)<<" "<<qPrintable(saveClientString)<<std::endl;

    if (runs.size() > 0) terminal->startProcess("/exports/slc7/scripts/run_analysis_CC7.sh", commandArgs);
    else                 terminal->startProcess("/exports/slc7/scripts/run_analysis_CC7.sh", commandArgs);
    if (terminal->didStartFail()) delete terminal;
    else emit showTabSignal(terminal, "Run Analysis");
}

void Startup::on_btnMarkBad_clicked() {
    QString user = DbConnection::Inst()->dbConnection().userName();
    if (QString::compare( user, tr("cms_trk_tkcc"),  Qt::CaseInsensitive) != 0) QMessageBox::critical(0, tr("Startup"), tr("You are using a wrong database account which does not have write permissions") );
    
    QModelIndexList runList = runView->selectionModel()->selectedRows();
    if (runList.size() != 1) {
        if (Debug::Inst()->getEnabled()) qDebug() << "More than one run selected. This is not allowed. Quitting ... \n";
        return;
    }
    QStandardItem *run = runModel->itemFromIndex(runList.at(0));
    QString runNumber = run->text();

    if (QMessageBox::question(this, "Mark Bad", tr("This will mark run ")+runNumber+tr(" of partition ")+currentPartitionName+tr(" as bad\nDo you want to proceed?"), QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Cancel ) return;
    
    QSqlQuery query;
    query.prepare("UPDATE RUN set COMMENTS = ? where RUNNUMBER = ? and PARTITIONID = ( SELECT PARTITIONID from PARTITION where PARTITIONNAME = ? )");
    query.addBindValue("BAD");
    query.addBindValue(runNumber.toInt() );
    query.addBindValue(currentPartitionName );
    
    bool result = query.exec();
    if (result) QMessageBox::information(0, tr("Startup"), tr("Marked run ")+runNumber+tr(" of partition ")+currentPartitionName+tr(" as bad") );
    else {
        QMessageBox::critical(0, tr("Startup"), tr("Something went wrong in the run flagging") );
        qDebug() << query.lastError();
    }
    on_btnUpdateRuns_clicked();

}

void Startup::on_btnPrepareGlobal_clicked() {
    PrepareGlobal* o2o = new PrepareGlobal();
    o2o->show();
    //emit showTabSignal(o2o, "O2O");
}

void Startup::on_btnTimingO2O_clicked() {
    MultiPart* to2o = new MultiPart(&tmpfiles);
    emit showTabSignal(to2o, "Multi Partitions");
}

void Startup::on_btnQuit_clicked() {
    emit closeParentSignal();
}



