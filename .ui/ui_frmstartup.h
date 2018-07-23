/********************************************************************************
** Form generated from reading UI file 'frmstartup.ui'
**
** Created: Tue May 8 15:28:16 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSTARTUP_H
#define UI_FRMSTARTUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include "QConnectedTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Startup
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    QTableView *partitionView;
    QPushButton *btnUpdatePartitions;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnShowUnfinished;
    QPushButton *btnMarkBad;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *cmbState;
    QPushButton *btnState;
    QTableView *runView;
    QPushButton *btnUpdateRuns;
    QVBoxLayout *verticalLayout_7;
    QPushButton *btnPrepareGlobal;
    QPushButton *btnTimingO2O;
    QSpacerItem *verticalSpacer_5;
    QCheckBox *chkSaveClient;
    QCheckBox *chkUseClient;
    QCheckBox *chkUploadAnalysis;
    QSpacerItem *verticalSpacer_6;
    QCheckBox *chkUploadConfiguration;
    QSpacerItem *verticalSpacer_7;
    QCheckBox *chkUseCache;
    QPushButton *btnViewResults;
    QPushButton *btnAnalyze;
    QSpacerItem *verticalSpacer_8;
    QPushButton *btnQuit;

    void setupUi(QConnectedTabWidget *Startup)
    {
        if (Startup->objectName().isEmpty())
            Startup->setObjectName(QString::fromUtf8("Startup"));
        Startup->resize(1044, 708);
        gridLayout_2 = new QGridLayout(Startup);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        partitionView = new QTableView(Startup);
        partitionView->setObjectName(QString::fromUtf8("partitionView"));
        partitionView->setSelectionMode(QAbstractItemView::SingleSelection);
        partitionView->setSelectionBehavior(QAbstractItemView::SelectRows);
        partitionView->setSortingEnabled(true);
        partitionView->setWordWrap(false);

        verticalLayout_5->addWidget(partitionView);

        btnUpdatePartitions = new QPushButton(Startup);
        btnUpdatePartitions->setObjectName(QString::fromUtf8("btnUpdatePartitions"));

        verticalLayout_5->addWidget(btnUpdatePartitions);


        gridLayout->addLayout(verticalLayout_5, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnShowUnfinished = new QPushButton(Startup);
        btnShowUnfinished->setObjectName(QString::fromUtf8("btnShowUnfinished"));
        btnShowUnfinished->setEnabled(false);

        horizontalLayout->addWidget(btnShowUnfinished);

        btnMarkBad = new QPushButton(Startup);
        btnMarkBad->setObjectName(QString::fromUtf8("btnMarkBad"));

        horizontalLayout->addWidget(btnMarkBad);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cmbState = new QComboBox(Startup);
        cmbState->setObjectName(QString::fromUtf8("cmbState"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmbState->sizePolicy().hasHeightForWidth());
        cmbState->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(cmbState);

        btnState = new QPushButton(Startup);
        btnState->setObjectName(QString::fromUtf8("btnState"));

        horizontalLayout_2->addWidget(btnState);


        verticalLayout->addLayout(horizontalLayout_2);

        runView = new QTableView(Startup);
        runView->setObjectName(QString::fromUtf8("runView"));
        runView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        runView->setSelectionBehavior(QAbstractItemView::SelectRows);
        runView->setSortingEnabled(true);
        runView->setWordWrap(false);

        verticalLayout->addWidget(runView);

        btnUpdateRuns = new QPushButton(Startup);
        btnUpdateRuns->setObjectName(QString::fromUtf8("btnUpdateRuns"));

        verticalLayout->addWidget(btnUpdateRuns);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        btnPrepareGlobal = new QPushButton(Startup);
        btnPrepareGlobal->setObjectName(QString::fromUtf8("btnPrepareGlobal"));
        btnPrepareGlobal->setEnabled(true);

        verticalLayout_7->addWidget(btnPrepareGlobal);

        btnTimingO2O = new QPushButton(Startup);
        btnTimingO2O->setObjectName(QString::fromUtf8("btnTimingO2O"));

        verticalLayout_7->addWidget(btnTimingO2O);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_5);

        chkSaveClient = new QCheckBox(Startup);
        chkSaveClient->setObjectName(QString::fromUtf8("chkSaveClient"));

        verticalLayout_7->addWidget(chkSaveClient);

        chkUseClient = new QCheckBox(Startup);
        chkUseClient->setObjectName(QString::fromUtf8("chkUseClient"));

        verticalLayout_7->addWidget(chkUseClient);

        chkUploadAnalysis = new QCheckBox(Startup);
        chkUploadAnalysis->setObjectName(QString::fromUtf8("chkUploadAnalysis"));

        verticalLayout_7->addWidget(chkUploadAnalysis);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_6);

        chkUploadConfiguration = new QCheckBox(Startup);
        chkUploadConfiguration->setObjectName(QString::fromUtf8("chkUploadConfiguration"));

        verticalLayout_7->addWidget(chkUploadConfiguration);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_7);

        chkUseCache = new QCheckBox(Startup);
        chkUseCache->setObjectName(QString::fromUtf8("chkUseCache"));
        chkUseCache->setChecked(true);

        verticalLayout_7->addWidget(chkUseCache);

        btnViewResults = new QPushButton(Startup);
        btnViewResults->setObjectName(QString::fromUtf8("btnViewResults"));

        verticalLayout_7->addWidget(btnViewResults);

        btnAnalyze = new QPushButton(Startup);
        btnAnalyze->setObjectName(QString::fromUtf8("btnAnalyze"));

        verticalLayout_7->addWidget(btnAnalyze);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_8);

        btnQuit = new QPushButton(Startup);
        btnQuit->setObjectName(QString::fromUtf8("btnQuit"));

        verticalLayout_7->addWidget(btnQuit);


        gridLayout->addLayout(verticalLayout_7, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(Startup);

        QMetaObject::connectSlotsByName(Startup);
    } // setupUi

    void retranslateUi(QConnectedTabWidget *Startup)
    {
        Startup->setWindowTitle(QApplication::translate("Startup", "Start up", 0, QApplication::UnicodeUTF8));
        btnUpdatePartitions->setText(QApplication::translate("Startup", "Update", 0, QApplication::UnicodeUTF8));
        btnShowUnfinished->setText(QApplication::translate("Startup", "Show Unfinished Runs", 0, QApplication::UnicodeUTF8));
        btnMarkBad->setText(QApplication::translate("Startup", "Mark Run as BAD", 0, QApplication::UnicodeUTF8));
        cmbState->clear();
        cmbState->insertItems(0, QStringList()
         << QApplication::translate("Startup", "Select state...", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Startup", "Current State", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Startup", "Last O2O'ed State", 0, QApplication::UnicodeUTF8)
        );
        btnState->setText(QApplication::translate("Startup", "Show", 0, QApplication::UnicodeUTF8));
        btnUpdateRuns->setText(QApplication::translate("Startup", "Update", 0, QApplication::UnicodeUTF8));
        btnPrepareGlobal->setText(QApplication::translate("Startup", "Prepare Global Running State", 0, QApplication::UnicodeUTF8));
        btnTimingO2O->setText(QApplication::translate("Startup", "Multi-partition View (Timing O2O)", 0, QApplication::UnicodeUTF8));
        chkSaveClient->setText(QApplication::translate("Startup", "Save Client File", 0, QApplication::UnicodeUTF8));
        chkUseClient->setText(QApplication::translate("Startup", "Use Client File", 0, QApplication::UnicodeUTF8));
        chkUploadAnalysis->setText(QApplication::translate("Startup", "Upload to Analysis DB", 0, QApplication::UnicodeUTF8));
        chkUploadConfiguration->setText(QApplication::translate("Startup", "Upload to ConfDB", 0, QApplication::UnicodeUTF8));
        chkUseCache->setText(QApplication::translate("Startup", "Use Cache if Available", 0, QApplication::UnicodeUTF8));
        btnViewResults->setText(QApplication::translate("Startup", "View Results", 0, QApplication::UnicodeUTF8));
        btnAnalyze->setText(QApplication::translate("Startup", "Analyze", 0, QApplication::UnicodeUTF8));
        btnQuit->setText(QApplication::translate("Startup", "Quit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Startup: public Ui_Startup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSTARTUP_H
