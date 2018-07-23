/********************************************************************************
** Form generated from reading UI file 'frmtrends.ui'
**
** Created: Tue May 8 15:28:16 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTRENDS_H
#define UI_FRMTRENDS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTableView>
#include "CustomTQtWidget.h"
#include "QConnectedTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Trends
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    CustomTQtWidget *qtCanvas;
    QHBoxLayout *horizontalLayout_2;
    QTableView *selView;

    void setupUi(QConnectedTabWidget *Trends)
    {
        if (Trends->objectName().isEmpty())
            Trends->setObjectName(QString::fromUtf8("Trends"));
        Trends->resize(1042, 686);
        gridLayout = new QGridLayout(Trends);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        qtCanvas = new CustomTQtWidget(Trends);
        qtCanvas->setObjectName(QString::fromUtf8("qtCanvas"));
        qtCanvas->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qtCanvas->sizePolicy().hasHeightForWidth());
        qtCanvas->setSizePolicy(sizePolicy);
        qtCanvas->setMinimumSize(QSize(500, 500));
        qtCanvas->setAutoFillBackground(true);

        horizontalLayout->addWidget(qtCanvas);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        selView = new QTableView(Trends);
        selView->setObjectName(QString::fromUtf8("selView"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(selView->sizePolicy().hasHeightForWidth());
        selView->setSizePolicy(sizePolicy1);
        selView->setSelectionMode(QAbstractItemView::SingleSelection);
        selView->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout_2->addWidget(selView);


        gridLayout->addLayout(horizontalLayout_2, 0, 1, 1, 1);


        retranslateUi(Trends);

        QMetaObject::connectSlotsByName(Trends);
    } // setupUi

    void retranslateUi(QConnectedTabWidget *Trends)
    {
        Trends->setWindowTitle(QApplication::translate("Trends", "Trends", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Trends: public Ui_Trends {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTRENDS_H
