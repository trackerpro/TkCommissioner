/********************************************************************************
** Form generated from reading UI file 'frmsource.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSOURCE_H
#define UI_FRMSOURCE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include "CustomTQtWidget.h"
#include "QConnectedTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SourceDisplay
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    CustomTQtWidget *qtCanvas;
    QVBoxLayout *verticalLayout;
    QComboBox *source;
    QTableView *selView;
    QPushButton *btnPrint;

    void setupUi(QConnectedTabWidget *SourceDisplay)
    {
        if (SourceDisplay->objectName().isEmpty())
            SourceDisplay->setObjectName(QString::fromUtf8("SourceDisplay"));
        SourceDisplay->resize(1042, 686);
        gridLayout = new QGridLayout(SourceDisplay);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        qtCanvas = new CustomTQtWidget(SourceDisplay);
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


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        source = new QComboBox(SourceDisplay);
        source->setObjectName(QString::fromUtf8("source"));

        verticalLayout->addWidget(source);

        selView = new QTableView(SourceDisplay);
        selView->setObjectName(QString::fromUtf8("selView"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(selView->sizePolicy().hasHeightForWidth());
        selView->setSizePolicy(sizePolicy1);
        selView->setSelectionMode(QAbstractItemView::SingleSelection);
        selView->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(selView);

        btnPrint = new QPushButton(SourceDisplay);
        btnPrint->setObjectName(QString::fromUtf8("btnPrint"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("images/Save-as-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPrint->setIcon(icon);

        verticalLayout->addWidget(btnPrint);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);


        retranslateUi(SourceDisplay);

        QMetaObject::connectSlotsByName(SourceDisplay);
    } // setupUi

    void retranslateUi(QConnectedTabWidget *SourceDisplay)
    {
        SourceDisplay->setWindowTitle(QApplication::translate("SourceDisplay", "Source", 0, QApplication::UnicodeUTF8));
        btnPrint->setText(QApplication::translate("SourceDisplay", "Print", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SourceDisplay: public Ui_SourceDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSOURCE_H
