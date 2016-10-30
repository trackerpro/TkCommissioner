#ifndef REFERENCECHOOSER_H
#define REFERENCECHOOSER_H

// Qt includes 
#include <QAbstractButton>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>
 
// UI file
#include "ui_frmreferencechooser.h"

class ReferenceChooser : public QDialog, private Ui::ReferenceChooser {

    Q_OBJECT
 
    public:
        ReferenceChooser(QWidget *parent = 0) {
            Q_UNUSED(parent);

            setupUi(this);
            
            sameRunType = false;
            
            refRunModel = new QStandardItemModel(0, 2,this);
            refRunView->setModel(refRunModel);
            refRunView->setSelectionMode(QAbstractItemView::SingleSelection);
            refRunView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
            
            connect(refRunView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(runChanged(QModelIndex,QModelIndex)));

        }

        ~ReferenceChooser() {
        }        

    signals:
        void refSignal(QString, QString, bool);

    public Q_SLOTS:
        void runChanged(QModelIndex current, QModelIndex) {
            referenceRunNumber = refRunModel->item(current.row(),0)->text();
        }

        void on_buttonBox_clicked(QAbstractButton* button) {
            if (buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole) return;
            
            QString newRunType;
            QString refRunType;
            
            QString myQuery = QString("select distinct runnumber, modedescription from viewallrun left outer join analysis using(runnumber) where partitionname='%1' and local = 1").arg(referencePartition);
            QSqlQuery query(myQuery);
            while (query.next()) {
                QString runNumber       = query.value(0).toString();
                QString modeDescription = query.value(1).toString();
            
                if (runNumber == newRunNumber) newRunType = modeDescription;
                if (runNumber == referenceRunNumber) refRunType = modeDescription;
            } 
            
            if (!newRunType.isEmpty() && !refRunType.isEmpty() && newRunType == refRunType) sameRunType = true;
            
            emit refSignal(referencePartition, referenceRunNumber, sameRunType);
        }

    public: 
        void addReferenceRuns(QString partitionName, QString currentRunNumber) {
            newRunNumber       = currentRunNumber;
            referenceRunNumber = currentRunNumber;
            referencePartition = partitionName;
            
            QString myQuery = QString("select distinct runnumber, modedescription, case when analysisid is not null then 1 else 0 end as analyzed from viewallrun left outer join analysis using(runnumber) where partitionname='%1' and local = 1 order by RUNNUMBER desc").arg(partitionName);
            QSqlQuery query(myQuery);
            while (query.next()) {
                QString runNumber       = query.value(0).toString();
                QString modeDescription = query.value(1).toString();
                bool    analyzed        = query.value(2).toBool();
            
                if (runNumber != currentRunNumber && analyzed) {
                    QList<QStandardItem*> *list = new QList<QStandardItem*>;
                    QStandardItem* runItem = new QStandardItem(runNumber);
                    runItem->setEditable(false);
                    QStandardItem* modItem = new QStandardItem(modeDescription);
                    modItem->setEditable(false);
                    list->append(runItem);
                    list->append(modItem);
                    refRunModel->appendRow(*list);
                }            
            } 
            refRunModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Run Number"));
            refRunModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Mode"));
        }

    private:
        QString newRunNumber;
        QString referenceRunNumber;
        QString referencePartition;
        bool sameRunType; 
        QStandardItemModel* refRunModel;
};
#endif
