#ifndef TagUpload_H
#define TagUpload_H

// Qt includes
#include <QValidator> 
#include <QRegExpValidator> 
#include <QRegExp> 
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QStandardItemModel>
#include <QtSql/QSqlQuery>

// Debug output
#include "Debug.h"
#include "DbConnection.h"

// UI file
#include "ui_frmsavetags.h"

class TagUpload : public QDialog, private Ui::TagUpload {

    Q_OBJECT
 
    public:
        TagUpload(QWidget *parent = 0) {
            Q_UNUSED(parent);

            setupUi(this); 

            tagsModel = new QStandardItemModel(0, 2,this);
            tagsModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Detid"));
            tagsModel->setHeaderData(1, Qt::Horizontal, QObject::tr("I2CAddress"));

            tagsView->setModel(tagsModel);
            tagsView->setSelectionMode(QAbstractItemView::SingleSelection);
            tagsView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
            
            connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));
            connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));
        }

        ~TagUpload() {
        }

    public Q_SLOTS:
        void accept() {
        }

        void reject() {
            done(0);
        }

    private:
        QStandardItemModel* tagsModel;
};
#endif
