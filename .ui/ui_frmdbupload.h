/********************************************************************************
** Form generated from reading UI file 'frmdbupload.ui'
**
** Created: Mon Oct 22 16:28:21 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMDBUPLOAD_H
#define UI_FRMDBUPLOAD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTableView>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>
#include "QConnectedTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DBUpload
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupSelLevel;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radAll;
    QRadioButton *radFed;
    QRadioButton *radFec;
    QRadioButton *radRing;
    QRadioButton *radCcu;
    QRadioButton *radCcuChan;
    QPushButton *btnAddSkip;
    QHBoxLayout *horizontalLayout;
    QTextEdit *txtCurRunInfo;
    QTableView *skipList;
    QGroupBox *groupUpload;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *chkSkip;
    QCheckBox *chkVeto;
    QPushButton *btnUpload;

    void setupUi(QConnectedTabWidget *DBUpload)
    {
        if (DBUpload->objectName().isEmpty())
            DBUpload->setObjectName(QString::fromUtf8("DBUpload"));
        DBUpload->resize(1041, 709);
        gridLayout = new QGridLayout(DBUpload);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupSelLevel = new QGroupBox(DBUpload);
        groupSelLevel->setObjectName(QString::fromUtf8("groupSelLevel"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupSelLevel->sizePolicy().hasHeightForWidth());
        groupSelLevel->setSizePolicy(sizePolicy);
        groupSelLevel->setMinimumSize(QSize(700, 60));
        horizontalLayoutWidget = new QWidget(groupSelLevel);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 651, 51));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        radAll = new QRadioButton(horizontalLayoutWidget);
        radAll->setObjectName(QString::fromUtf8("radAll"));
        radAll->setChecked(true);

        horizontalLayout_3->addWidget(radAll);

        radFed = new QRadioButton(horizontalLayoutWidget);
        radFed->setObjectName(QString::fromUtf8("radFed"));

        horizontalLayout_3->addWidget(radFed);

        radFec = new QRadioButton(horizontalLayoutWidget);
        radFec->setObjectName(QString::fromUtf8("radFec"));

        horizontalLayout_3->addWidget(radFec);

        radRing = new QRadioButton(horizontalLayoutWidget);
        radRing->setObjectName(QString::fromUtf8("radRing"));

        horizontalLayout_3->addWidget(radRing);

        radCcu = new QRadioButton(horizontalLayoutWidget);
        radCcu->setObjectName(QString::fromUtf8("radCcu"));

        horizontalLayout_3->addWidget(radCcu);

        radCcuChan = new QRadioButton(horizontalLayoutWidget);
        radCcuChan->setObjectName(QString::fromUtf8("radCcuChan"));

        horizontalLayout_3->addWidget(radCcuChan);

        btnAddSkip = new QPushButton(horizontalLayoutWidget);
        btnAddSkip->setObjectName(QString::fromUtf8("btnAddSkip"));

        horizontalLayout_3->addWidget(btnAddSkip);


        gridLayout->addWidget(groupSelLevel, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        txtCurRunInfo = new QTextEdit(DBUpload);
        txtCurRunInfo->setObjectName(QString::fromUtf8("txtCurRunInfo"));
        txtCurRunInfo->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txtCurRunInfo->sizePolicy().hasHeightForWidth());
        txtCurRunInfo->setSizePolicy(sizePolicy1);
        txtCurRunInfo->setMinimumSize(QSize(0, 250));
        txtCurRunInfo->setReadOnly(true);

        horizontalLayout->addWidget(txtCurRunInfo);

        skipList = new QTableView(DBUpload);
        skipList->setObjectName(QString::fromUtf8("skipList"));
        sizePolicy1.setHeightForWidth(skipList->sizePolicy().hasHeightForWidth());
        skipList->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(skipList);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 2);

        groupUpload = new QGroupBox(DBUpload);
        groupUpload->setObjectName(QString::fromUtf8("groupUpload"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupUpload->sizePolicy().hasHeightForWidth());
        groupUpload->setSizePolicy(sizePolicy2);
        horizontalLayoutWidget_2 = new QWidget(groupUpload);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 10, 291, 51));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        chkSkip = new QCheckBox(horizontalLayoutWidget_2);
        chkSkip->setObjectName(QString::fromUtf8("chkSkip"));
        chkSkip->setChecked(true);

        horizontalLayout_2->addWidget(chkSkip);

        chkVeto = new QCheckBox(horizontalLayoutWidget_2);
        chkVeto->setObjectName(QString::fromUtf8("chkVeto"));
        chkVeto->setChecked(true);

        horizontalLayout_2->addWidget(chkVeto);

        btnUpload = new QPushButton(horizontalLayoutWidget_2);
        btnUpload->setObjectName(QString::fromUtf8("btnUpload"));

        horizontalLayout_2->addWidget(btnUpload);


        gridLayout->addWidget(groupUpload, 1, 1, 1, 1);


        retranslateUi(DBUpload);

        QMetaObject::connectSlotsByName(DBUpload);
    } // setupUi

    void retranslateUi(QConnectedTabWidget *DBUpload)
    {
        DBUpload->setWindowTitle(QApplication::translate("DBUpload", "Run Info", 0, QApplication::UnicodeUTF8));
        groupSelLevel->setTitle(QApplication::translate("DBUpload", "Skip Level", 0, QApplication::UnicodeUTF8));
        radAll->setText(QApplication::translate("DBUpload", "Full Granularity", 0, QApplication::UnicodeUTF8));
        radFed->setText(QApplication::translate("DBUpload", "FED level", 0, QApplication::UnicodeUTF8));
        radFec->setText(QApplication::translate("DBUpload", "FEC Slot", 0, QApplication::UnicodeUTF8));
        radRing->setText(QApplication::translate("DBUpload", "Ring", 0, QApplication::UnicodeUTF8));
        radCcu->setText(QApplication::translate("DBUpload", "CCU", 0, QApplication::UnicodeUTF8));
        radCcuChan->setText(QApplication::translate("DBUpload", "CCU Channel", 0, QApplication::UnicodeUTF8));
        btnAddSkip->setText(QApplication::translate("DBUpload", "Add Channel", 0, QApplication::UnicodeUTF8));
        groupUpload->setTitle(QApplication::translate("DBUpload", "Upload", 0, QApplication::UnicodeUTF8));
        chkSkip->setText(QApplication::translate("DBUpload", "Selective Upload", 0, QApplication::UnicodeUTF8));
        chkVeto->setText(QApplication::translate("DBUpload", "Veto", 0, QApplication::UnicodeUTF8));
        btnUpload->setText(QApplication::translate("DBUpload", "Upload", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DBUpload: public Ui_DBUpload {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMDBUPLOAD_H
