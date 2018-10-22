/********************************************************************************
** Form generated from reading UI file 'frmdetails.ui'
**
** Created: Mon Oct 22 16:28:21 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMDETAILS_H
#define UI_FRMDETAILS_H

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
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include "QConnectedTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SelectionDetails
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSelectAll;
    QPushButton *btnUnselectAll;
    QPushButton *btnSelectTagged;
    QPushButton *btnUnselectTagged;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnShowAllSelected;
    QPushButton *btnShowTaggedSelected;
    QPushButton *btnShowTaggedAll;
    QTreeView *listSelection;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnShowSource;
    QPushButton *btnShowTrend;
    QPushButton *btnSave;
    QSpacerItem *horizontalSpacer;
    QCheckBox *chkCloseTkt;
    QPushButton *btnTagSelected;
    QComboBox *cmbTagList;
    QPushButton *btnAddTag;

    void setupUi(QConnectedTabWidget *SelectionDetails)
    {
        if (SelectionDetails->objectName().isEmpty())
            SelectionDetails->setObjectName(QString::fromUtf8("SelectionDetails"));
        SelectionDetails->resize(1042, 684);
        gridLayout = new QGridLayout(SelectionDetails);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnSelectAll = new QPushButton(SelectionDetails);
        btnSelectAll->setObjectName(QString::fromUtf8("btnSelectAll"));

        horizontalLayout->addWidget(btnSelectAll);

        btnUnselectAll = new QPushButton(SelectionDetails);
        btnUnselectAll->setObjectName(QString::fromUtf8("btnUnselectAll"));

        horizontalLayout->addWidget(btnUnselectAll);

        btnSelectTagged = new QPushButton(SelectionDetails);
        btnSelectTagged->setObjectName(QString::fromUtf8("btnSelectTagged"));

        horizontalLayout->addWidget(btnSelectTagged);

        btnUnselectTagged = new QPushButton(SelectionDetails);
        btnUnselectTagged->setObjectName(QString::fromUtf8("btnUnselectTagged"));

        horizontalLayout->addWidget(btnUnselectTagged);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnShowAllSelected = new QPushButton(SelectionDetails);
        btnShowAllSelected->setObjectName(QString::fromUtf8("btnShowAllSelected"));

        horizontalLayout->addWidget(btnShowAllSelected);

        btnShowTaggedSelected = new QPushButton(SelectionDetails);
        btnShowTaggedSelected->setObjectName(QString::fromUtf8("btnShowTaggedSelected"));

        horizontalLayout->addWidget(btnShowTaggedSelected);

        btnShowTaggedAll = new QPushButton(SelectionDetails);
        btnShowTaggedAll->setObjectName(QString::fromUtf8("btnShowTaggedAll"));

        horizontalLayout->addWidget(btnShowTaggedAll);


        verticalLayout->addLayout(horizontalLayout);

        listSelection = new QTreeView(SelectionDetails);
        listSelection->setObjectName(QString::fromUtf8("listSelection"));
        listSelection->setSortingEnabled(false);

        verticalLayout->addWidget(listSelection);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btnShowSource = new QPushButton(SelectionDetails);
        btnShowSource->setObjectName(QString::fromUtf8("btnShowSource"));

        horizontalLayout_4->addWidget(btnShowSource);

        btnShowTrend = new QPushButton(SelectionDetails);
        btnShowTrend->setObjectName(QString::fromUtf8("btnShowTrend"));

        horizontalLayout_4->addWidget(btnShowTrend);

        btnSave = new QPushButton(SelectionDetails);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        horizontalLayout_4->addWidget(btnSave);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        chkCloseTkt = new QCheckBox(SelectionDetails);
        chkCloseTkt->setObjectName(QString::fromUtf8("chkCloseTkt"));

        horizontalLayout_4->addWidget(chkCloseTkt);

        btnTagSelected = new QPushButton(SelectionDetails);
        btnTagSelected->setObjectName(QString::fromUtf8("btnTagSelected"));
        btnTagSelected->setEnabled(true);

        horizontalLayout_4->addWidget(btnTagSelected);

        cmbTagList = new QComboBox(SelectionDetails);
        cmbTagList->setObjectName(QString::fromUtf8("cmbTagList"));

        horizontalLayout_4->addWidget(cmbTagList);

        btnAddTag = new QPushButton(SelectionDetails);
        btnAddTag->setObjectName(QString::fromUtf8("btnAddTag"));

        horizontalLayout_4->addWidget(btnAddTag);


        horizontalLayout_3->addLayout(horizontalLayout_4);


        horizontalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(SelectionDetails);

        QMetaObject::connectSlotsByName(SelectionDetails);
    } // setupUi

    void retranslateUi(QConnectedTabWidget *SelectionDetails)
    {
        SelectionDetails->setWindowTitle(QApplication::translate("SelectionDetails", "Selection Details", 0, QApplication::UnicodeUTF8));
        btnSelectAll->setText(QApplication::translate("SelectionDetails", "Check All", 0, QApplication::UnicodeUTF8));
        btnUnselectAll->setText(QApplication::translate("SelectionDetails", "Uncheck All", 0, QApplication::UnicodeUTF8));
        btnSelectTagged->setText(QApplication::translate("SelectionDetails", "Check Tagged", 0, QApplication::UnicodeUTF8));
        btnUnselectTagged->setText(QApplication::translate("SelectionDetails", "Uncheck Tagged", 0, QApplication::UnicodeUTF8));
        btnShowAllSelected->setText(QApplication::translate("SelectionDetails", "Show All Selected", 0, QApplication::UnicodeUTF8));
        btnShowTaggedSelected->setText(QApplication::translate("SelectionDetails", "Show Tagged Selected", 0, QApplication::UnicodeUTF8));
        btnShowTaggedAll->setText(QApplication::translate("SelectionDetails", "Show All Tagged", 0, QApplication::UnicodeUTF8));
        btnShowSource->setText(QApplication::translate("SelectionDetails", "Source Histograms", 0, QApplication::UnicodeUTF8));
        btnShowTrend->setText(QApplication::translate("SelectionDetails", "Show Trend", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("SelectionDetails", "Save", 0, QApplication::UnicodeUTF8));
        chkCloseTkt->setText(QApplication::translate("SelectionDetails", "Close Ticket", 0, QApplication::UnicodeUTF8));
        btnTagSelected->setText(QApplication::translate("SelectionDetails", "Tag Selected", 0, QApplication::UnicodeUTF8));
        btnAddTag->setText(QApplication::translate("SelectionDetails", "Add Tag", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SelectionDetails: public Ui_SelectionDetails {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMDETAILS_H
