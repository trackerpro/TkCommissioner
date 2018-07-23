/********************************************************************************
** Form generated from reading UI file 'frmtimingo2o.ui'
**
** Created: Mon May 8 11:54:36 2017
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTIMINGO2O_H
#define UI_FRMTIMINGO2O_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "QConnectedTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_TimingO2O
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel3;
    QSpacerItem *Horizontal_Spacing2;
    QVBoxLayout *vboxLayout1;
    QPushButton *btnCheck;
    QComboBox *cmbRunType;
    QGridLayout *partitionLayout;
    QLabel *textLabel2_4;
    QComboBox *cmbRunTecm;
    QComboBox *cmbRunTecp;
    QLabel *textLabel1_2;
    QComboBox *cmbTobPartition;
    QLabel *textLabel1_3;
    QComboBox *cmbRunTob;
    QComboBox *cmbTecmPartition;
    QFrame *line3;
    QLabel *textLabel2_2;
    QLabel *textLabel2_3;
    QComboBox *cmbTibPartition;
    QComboBox *cmbRunTib;
    QLabel *textLabel1_4;
    QLabel *textLabel2;
    QComboBox *cmbTecpPartition;
    QLabel *textLabel1;
    QSpacerItem *spacer8_2;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnShow;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QConnectedTabWidget *TimingO2O)
    {
        if (TimingO2O->objectName().isEmpty())
            TimingO2O->setObjectName(QString::fromUtf8("TimingO2O"));
        TimingO2O->resize(941, 369);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TimingO2O->sizePolicy().hasHeightForWidth());
        TimingO2O->setSizePolicy(sizePolicy);
        TimingO2O->setProperty("sizeGripEnabled", QVariant(true));
        gridLayout = new QGridLayout(TimingO2O);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));

        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        textLabel3 = new QLabel(TimingO2O);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        textLabel3->setAlignment(Qt::AlignVCenter);
        textLabel3->setWordWrap(false);

        hboxLayout1->addWidget(textLabel3);

        Horizontal_Spacing2 = new QSpacerItem(250, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        hboxLayout1->addItem(Horizontal_Spacing2);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        btnCheck = new QPushButton(TimingO2O);
        btnCheck->setObjectName(QString::fromUtf8("btnCheck"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnCheck->sizePolicy().hasHeightForWidth());
        btnCheck->setSizePolicy(sizePolicy1);
        btnCheck->setMinimumSize(QSize(110, 0));

        vboxLayout1->addWidget(btnCheck);

        cmbRunType = new QComboBox(TimingO2O);
        cmbRunType->setObjectName(QString::fromUtf8("cmbRunType"));

        vboxLayout1->addWidget(cmbRunType);


        hboxLayout1->addLayout(vboxLayout1);


        vboxLayout->addLayout(hboxLayout1);

        partitionLayout = new QGridLayout();
        partitionLayout->setSpacing(6);
        partitionLayout->setObjectName(QString::fromUtf8("partitionLayout"));
        partitionLayout->setHorizontalSpacing(4);
        partitionLayout->setVerticalSpacing(6);
        textLabel2_4 = new QLabel(TimingO2O);
        textLabel2_4->setObjectName(QString::fromUtf8("textLabel2_4"));
        textLabel2_4->setWordWrap(false);

        partitionLayout->addWidget(textLabel2_4, 5, 0, 1, 1);

        cmbRunTecm = new QComboBox(TimingO2O);
        cmbRunTecm->setObjectName(QString::fromUtf8("cmbRunTecm"));

        partitionLayout->addWidget(cmbRunTecm, 5, 3, 1, 1);

        cmbRunTecp = new QComboBox(TimingO2O);
        cmbRunTecp->setObjectName(QString::fromUtf8("cmbRunTecp"));

        partitionLayout->addWidget(cmbRunTecp, 4, 3, 1, 1);

        textLabel1_2 = new QLabel(TimingO2O);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        partitionLayout->addWidget(textLabel1_2, 2, 2, 2, 1);

        cmbTobPartition = new QComboBox(TimingO2O);
        cmbTobPartition->setObjectName(QString::fromUtf8("cmbTobPartition"));

        partitionLayout->addWidget(cmbTobPartition, 2, 1, 2, 1);

        textLabel1_3 = new QLabel(TimingO2O);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setWordWrap(false);

        partitionLayout->addWidget(textLabel1_3, 4, 2, 1, 1);

        cmbRunTob = new QComboBox(TimingO2O);
        cmbRunTob->setObjectName(QString::fromUtf8("cmbRunTob"));

        partitionLayout->addWidget(cmbRunTob, 2, 3, 2, 1);

        cmbTecmPartition = new QComboBox(TimingO2O);
        cmbTecmPartition->setObjectName(QString::fromUtf8("cmbTecmPartition"));

        partitionLayout->addWidget(cmbTecmPartition, 5, 1, 1, 1);

        line3 = new QFrame(TimingO2O);
        line3->setObjectName(QString::fromUtf8("line3"));
        line3->setFrameShape(QFrame::HLine);
        line3->setFrameShadow(QFrame::Sunken);

        partitionLayout->addWidget(line3, 0, 0, 1, 5);

        textLabel2_2 = new QLabel(TimingO2O);
        textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
        textLabel2_2->setWordWrap(false);

        partitionLayout->addWidget(textLabel2_2, 2, 0, 2, 1);

        textLabel2_3 = new QLabel(TimingO2O);
        textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
        textLabel2_3->setWordWrap(false);

        partitionLayout->addWidget(textLabel2_3, 4, 0, 1, 1);

        cmbTibPartition = new QComboBox(TimingO2O);
        cmbTibPartition->setObjectName(QString::fromUtf8("cmbTibPartition"));

        partitionLayout->addWidget(cmbTibPartition, 1, 1, 1, 1);

        cmbRunTib = new QComboBox(TimingO2O);
        cmbRunTib->setObjectName(QString::fromUtf8("cmbRunTib"));

        partitionLayout->addWidget(cmbRunTib, 1, 3, 1, 1);

        textLabel1_4 = new QLabel(TimingO2O);
        textLabel1_4->setObjectName(QString::fromUtf8("textLabel1_4"));
        textLabel1_4->setWordWrap(false);

        partitionLayout->addWidget(textLabel1_4, 5, 2, 1, 1);

        textLabel2 = new QLabel(TimingO2O);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        partitionLayout->addWidget(textLabel2, 1, 0, 1, 1);

        cmbTecpPartition = new QComboBox(TimingO2O);
        cmbTecpPartition->setObjectName(QString::fromUtf8("cmbTecpPartition"));

        partitionLayout->addWidget(cmbTecpPartition, 4, 1, 1, 1);

        textLabel1 = new QLabel(TimingO2O);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        partitionLayout->addWidget(textLabel1, 1, 2, 1, 1);


        vboxLayout->addLayout(partitionLayout);

        spacer8_2 = new QSpacerItem(21, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacer8_2);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        hboxLayout2->addItem(horizontalSpacer);

        btnShow = new QPushButton(TimingO2O);
        btnShow->setObjectName(QString::fromUtf8("btnShow"));
        btnShow->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnShow->sizePolicy().hasHeightForWidth());
        btnShow->setSizePolicy(sizePolicy2);
        btnShow->setAutoDefault(true);

        hboxLayout2->addWidget(btnShow);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        hboxLayout2->addItem(horizontalSpacer_2);


        vboxLayout->addLayout(hboxLayout2);


        gridLayout->addLayout(vboxLayout, 0, 0, 1, 1);


        retranslateUi(TimingO2O);

        QMetaObject::connectSlotsByName(TimingO2O);
    } // setupUi

    void retranslateUi(QConnectedTabWidget *TimingO2O)
    {
        TimingO2O->setWindowTitle(QApplication::translate("TimingO2O", "All Tracker Results", 0, QApplication::UnicodeUTF8));
        textLabel3->setText(QApplication::translate("TimingO2O", "<html><head/><body><p><br/><span style=\" font-size:xx-large; font-weight:600;\">View Partitions Simultaneously</span></p><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
        btnCheck->setText(QApplication::translate("TimingO2O", "Update", 0, QApplication::UnicodeUTF8));
        textLabel2_4->setText(QApplication::translate("TimingO2O", "<p align=\"right\">TEC-</p>", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("TimingO2O", "<p align=\"right\">Run Nr.</p>", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("TimingO2O", "<p align=\"right\">Run Nr.</p>", 0, QApplication::UnicodeUTF8));
        textLabel2_2->setText(QApplication::translate("TimingO2O", "<p align=\"right\">TOB</p>", 0, QApplication::UnicodeUTF8));
        textLabel2_3->setText(QApplication::translate("TimingO2O", "<p align=\"right\">TEC+</p>", 0, QApplication::UnicodeUTF8));
        textLabel1_4->setText(QApplication::translate("TimingO2O", "<p align=\"right\">Run Nr.</p>", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("TimingO2O", "<p align=\"right\">TIB/TID</p>", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("TimingO2O", "<p align=\"right\">Run Nr.</p>", 0, QApplication::UnicodeUTF8));
        btnShow->setText(QApplication::translate("TimingO2O", "Show Results", 0, QApplication::UnicodeUTF8));
        btnShow->setShortcut(QString());
    } // retranslateUi

};

namespace Ui {
    class TimingO2O: public Ui_TimingO2O {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTIMINGO2O_H
