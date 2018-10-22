/********************************************************************************
** Form generated from reading UI file 'frmpartitions.ui'
**
** Created: Mon Oct 22 16:28:21 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMPARTITIONS_H
#define UI_FRMPARTITIONS_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <occi.h>

QT_BEGIN_NAMESPACE

class Ui_Partitions
{
public:
    QVBoxLayout *vboxLayout;
    QListView *listPartitions;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacer10;
    QPushButton *btnCancel;
    QSpacerItem *spacer10_2;
    QPushButton *btnOk;

    void setupUi(QDialog *Partitions)
    {
        if (Partitions->objectName().isEmpty())
            Partitions->setObjectName(QString::fromUtf8("Partitions"));
        Partitions->resize(304, 458);
        vboxLayout = new QVBoxLayout(Partitions);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        listPartitions = new QListView(Partitions);
        listPartitions->setObjectName(QString::fromUtf8("listPartitions"));

        vboxLayout->addWidget(listPartitions);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacer10 = new QSpacerItem(260, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer10);

        btnCancel = new QPushButton(Partitions);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setMinimumSize(QSize(80, 0));

        hboxLayout->addWidget(btnCancel);

        spacer10_2 = new QSpacerItem(40, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer10_2);

        btnOk = new QPushButton(Partitions);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setMinimumSize(QSize(80, 0));
        btnOk->setDefault(true);

        hboxLayout->addWidget(btnOk);


        vboxLayout->addLayout(hboxLayout);


        retranslateUi(Partitions);

        QMetaObject::connectSlotsByName(Partitions);
    } // setupUi

    void retranslateUi(QDialog *Partitions)
    {
        Partitions->setWindowTitle(QApplication::translate("Partitions", "Choose a partition name", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("Partitions", "Cancel", 0, QApplication::UnicodeUTF8));
        btnCancel->setShortcut(QApplication::translate("Partitions", "Esc", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("Partitions", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Partitions: public Ui_Partitions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMPARTITIONS_H
