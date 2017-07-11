#ifndef FRMPARTITIONS_H
#define FRMPARTITIONS_H
 
#include "ui_frmpartitions.h"
#include <QStringListModel>

class Partitions : public QDialog, private Ui::Partitions {

    Q_OBJECT
 
    public:

        Partitions(QWidget *parent = 0);
        ~Partitions();

        const QString& selectedPartition();
        void populatePartitions();

    private:

        QString selectedPartitionName;
        QStringListModel* model;

    public Q_SLOTS:

        void on_btnOk_clicked();

        void on_btnCancel_clicked();

        void partitionClicked(QModelIndex);
};

#endif
