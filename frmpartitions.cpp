#include "frmpartitions.h"
#include <QtSql/QSqlQuery>

#define GETPARTITIONS "select distinct partition.partitionname, partition.partitionid from partition, StateHistory, CurrentState where StateHistory.partitionid=Partition.partitionId and StateHistory.stateHistoryId=CurrentState.stateHistoryId order by partition.partitionid DESC"

Partitions::Partitions(QWidget* parent):
    QDialog(parent),
    selectedPartitionName("")
{
    setupUi(this);

    model = new QStringListModel(this);
    listPartitions->setModel(model);

    connect(listPartitions, SIGNAL(clicked(const QModelIndex)), this, SLOT(partitionClicked(QModelIndex))); 
}

Partitions::~Partitions() {
}

void Partitions::populatePartitions() {

    QString myQuery = QString(GETPARTITIONS);
    QSqlQuery query(myQuery);
     
    QStringList partList;
 
    while (query.next()) { 
        QString partitionName = query.value(0).toString();
        partList << partitionName;
    }

    model->setStringList(partList);

}
    
void Partitions::on_btnOk_clicked() {
    this->accept();
}


void Partitions::on_btnCancel_clicked() {
    this->reject();
}

const QString& Partitions::selectedPartition() {
    return selectedPartitionName;
}

void Partitions::partitionClicked(QModelIndex current) {
    selectedPartitionName = current.data().toString();
}

