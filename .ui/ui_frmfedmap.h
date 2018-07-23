/********************************************************************************
** Form generated from reading UI file 'frmfedmap.ui'
**
** Created: Tue May 8 15:28:16 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMFEDMAP_H
#define UI_FRMFEDMAP_H

#include <FedGraphicsView.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QVBoxLayout>
#include "QConnectedTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_FedMap
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *bufferLabel1;
    QLabel *bufferLabel2;
    QCheckBox *chkEnable;
    QCheckBox *chkVeto;
    QPushButton *btnUpload;
    QLabel *bufferLabel3;
    QLabel *bufferLabel4;
    FedGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QPushButton *btnZoomIn;
    QSlider *zoomSlider;
    QPushButton *btnZoomOut;

    void setupUi(QConnectedTabWidget *FedMap)
    {
        if (FedMap->objectName().isEmpty())
            FedMap->setObjectName(QString::fromUtf8("FedMap"));
        FedMap->resize(1041, 709);
        horizontalLayout_2 = new QHBoxLayout(FedMap);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        bufferLabel1 = new QLabel(FedMap);
        bufferLabel1->setObjectName(QString::fromUtf8("bufferLabel1"));

        horizontalLayout_3->addWidget(bufferLabel1);

        bufferLabel2 = new QLabel(FedMap);
        bufferLabel2->setObjectName(QString::fromUtf8("bufferLabel2"));

        horizontalLayout_3->addWidget(bufferLabel2);

        chkEnable = new QCheckBox(FedMap);
        chkEnable->setObjectName(QString::fromUtf8("chkEnable"));
        chkEnable->setChecked(true);

        horizontalLayout_3->addWidget(chkEnable);

        chkVeto = new QCheckBox(FedMap);
        chkVeto->setObjectName(QString::fromUtf8("chkVeto"));
        chkVeto->setChecked(true);

        horizontalLayout_3->addWidget(chkVeto);

        btnUpload = new QPushButton(FedMap);
        btnUpload->setObjectName(QString::fromUtf8("btnUpload"));

        horizontalLayout_3->addWidget(btnUpload);

        bufferLabel3 = new QLabel(FedMap);
        bufferLabel3->setObjectName(QString::fromUtf8("bufferLabel3"));

        horizontalLayout_3->addWidget(bufferLabel3);

        bufferLabel4 = new QLabel(FedMap);
        bufferLabel4->setObjectName(QString::fromUtf8("bufferLabel4"));

        horizontalLayout_3->addWidget(bufferLabel4);


        verticalLayout_2->addLayout(horizontalLayout_3);

        graphicsView = new FedGraphicsView(FedMap);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout_2->addWidget(graphicsView);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnZoomIn = new QPushButton(FedMap);
        btnZoomIn->setObjectName(QString::fromUtf8("btnZoomIn"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("images/zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnZoomIn->setIcon(icon);

        verticalLayout->addWidget(btnZoomIn);

        zoomSlider = new QSlider(FedMap);
        zoomSlider->setObjectName(QString::fromUtf8("zoomSlider"));
        zoomSlider->setMinimum(-50);
        zoomSlider->setMaximum(50);
        zoomSlider->setValue(0);
        zoomSlider->setOrientation(Qt::Vertical);

        verticalLayout->addWidget(zoomSlider);

        btnZoomOut = new QPushButton(FedMap);
        btnZoomOut->setObjectName(QString::fromUtf8("btnZoomOut"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("images/zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnZoomOut->setIcon(icon1);

        verticalLayout->addWidget(btnZoomOut);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(FedMap);

        QMetaObject::connectSlotsByName(FedMap);
    } // setupUi

    void retranslateUi(QConnectedTabWidget *FedMap)
    {
        FedMap->setWindowTitle(QApplication::translate("FedMap", "FED Map", 0, QApplication::UnicodeUTF8));
        bufferLabel1->setText(QString());
        bufferLabel2->setText(QString());
        chkEnable->setText(QApplication::translate("FedMap", "Enable selective upload", 0, QApplication::UnicodeUTF8));
        chkVeto->setText(QApplication::translate("FedMap", "Veto FED", 0, QApplication::UnicodeUTF8));
        btnUpload->setText(QApplication::translate("FedMap", "Selective upload", 0, QApplication::UnicodeUTF8));
        bufferLabel3->setText(QString());
        bufferLabel4->setText(QString());
        btnZoomIn->setText(QString());
        btnZoomOut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FedMap: public Ui_FedMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMFEDMAP_H
