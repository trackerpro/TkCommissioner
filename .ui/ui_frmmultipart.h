/********************************************************************************
** Form generated from reading UI file 'frmmultipart.ui'
**
** Created: Tue May 8 15:28:16 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMULTIPART_H
#define UI_FRMMULTIPART_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "QConnectedTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MultiPart
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *textLabel3;
    QSpacerItem *Horizontal_Spacing2;
    QVBoxLayout *vboxLayout1;
    QPushButton *btnUpdate;
    QComboBox *cmbRunType;
    QGridLayout *partitionLayout;
    QLabel *textLabel1_4;
    QLabel *textLabel2_4;
    QComboBox *cmbRunTecm;
    QComboBox *cmbRunTecp;
    QLabel *textLabel1_3;
    QComboBox *cmbTecmPartition;
    QLabel *textLabel2_3;
    QComboBox *cmbTibPartition;
    QComboBox *cmbRunTib;
    QLabel *textLabel2;
    QComboBox *cmbTecpPartition;
    QLabel *textLabel1;
    QComboBox *cmbRunTob;
    QComboBox *cmbTobPartition;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout1;
    QLabel *lblTibAna;
    QLabel *lblConnversion;
    QLabel *lblFedversion;
    QLabel *lblFecVersion;
    QLabel *lblTibConn;
    QLabel *lblTecp;
    QLabel *lblTecm;
    QLabel *lblTob;
    QLabel *lblTobConn;
    QLabel *lblTib;
    QLabel *lblTibFed;
    QLabel *lblTobFec;
    QLabel *lblTecpConn;
    QLabel *lblTibFec;
    QLabel *lblTecmConn;
    QLabel *lblPartname;
    QLabel *lblTibMask;
    QLabel *lblTecmMask;
    QLabel *lblMaskversion;
    QLabel *lblAnalysisversion;
    QLabel *lblTobFed;
    QLabel *lblTecpFed;
    QLabel *lblTecmFed;
    QLabel *lblTecpFec;
    QLabel *lblTecmFec;
    QLabel *lblTobMask;
    QLabel *lblTecpMask;
    QLabel *lblTobAna;
    QLabel *lblTecpAna;
    QLabel *lblTecmAna;
    QLabel *lblDcu;
    QLabel *lblTibDcu;
    QLabel *lblTecmDcu;
    QLabel *lblTobDcu;
    QLabel *lblTecpDcu;
    QLabel *lblDcupsu;
    QLabel *lblTibDcupsu;
    QLabel *lblTobDcupsu;
    QLabel *lblTecpDcupsu;
    QLabel *lblTecmDcupsu;
    QSpacerItem *spacer8_2;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnShow;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QConnectedTabWidget *MultiPart)
    {
        if (MultiPart->objectName().isEmpty())
            MultiPart->setObjectName(QString::fromUtf8("MultiPart"));
        MultiPart->resize(1079, 766);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MultiPart->sizePolicy().hasHeightForWidth());
        MultiPart->setSizePolicy(sizePolicy);
        MultiPart->setProperty("sizeGripEnabled", QVariant(true));
        gridLayout = new QGridLayout(MultiPart);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(-1, -1, 200, -1);
        textLabel3 = new QLabel(MultiPart);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        textLabel3->setAlignment(Qt::AlignVCenter);
        textLabel3->setWordWrap(false);

        hboxLayout->addWidget(textLabel3);

        Horizontal_Spacing2 = new QSpacerItem(250, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        hboxLayout->addItem(Horizontal_Spacing2);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        btnUpdate = new QPushButton(MultiPart);
        btnUpdate->setObjectName(QString::fromUtf8("btnUpdate"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnUpdate->sizePolicy().hasHeightForWidth());
        btnUpdate->setSizePolicy(sizePolicy1);
        btnUpdate->setMinimumSize(QSize(150, 0));

        vboxLayout1->addWidget(btnUpdate);

        cmbRunType = new QComboBox(MultiPart);
        cmbRunType->setObjectName(QString::fromUtf8("cmbRunType"));
        sizePolicy1.setHeightForWidth(cmbRunType->sizePolicy().hasHeightForWidth());
        cmbRunType->setSizePolicy(sizePolicy1);
        cmbRunType->setMinimumSize(QSize(150, 0));

        vboxLayout1->addWidget(cmbRunType);


        hboxLayout->addLayout(vboxLayout1);


        vboxLayout->addLayout(hboxLayout);

        partitionLayout = new QGridLayout();
        partitionLayout->setSpacing(6);
        partitionLayout->setObjectName(QString::fromUtf8("partitionLayout"));
        partitionLayout->setHorizontalSpacing(30);
        partitionLayout->setVerticalSpacing(6);
        partitionLayout->setContentsMargins(-1, -1, 200, -1);
        textLabel1_4 = new QLabel(MultiPart);
        textLabel1_4->setObjectName(QString::fromUtf8("textLabel1_4"));
        QFont font;
        font.setPointSize(12);
        textLabel1_4->setFont(font);
        textLabel1_4->setWordWrap(false);

        partitionLayout->addWidget(textLabel1_4, 3, 2, 1, 1);

        textLabel2_4 = new QLabel(MultiPart);
        textLabel2_4->setObjectName(QString::fromUtf8("textLabel2_4"));
        textLabel2_4->setFont(font);
        textLabel2_4->setWordWrap(false);

        partitionLayout->addWidget(textLabel2_4, 3, 0, 1, 1);

        cmbRunTecm = new QComboBox(MultiPart);
        cmbRunTecm->setObjectName(QString::fromUtf8("cmbRunTecm"));

        partitionLayout->addWidget(cmbRunTecm, 3, 3, 1, 1);

        cmbRunTecp = new QComboBox(MultiPart);
        cmbRunTecp->setObjectName(QString::fromUtf8("cmbRunTecp"));

        partitionLayout->addWidget(cmbRunTecp, 2, 3, 1, 1);

        textLabel1_3 = new QLabel(MultiPart);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setFont(font);
        textLabel1_3->setWordWrap(false);

        partitionLayout->addWidget(textLabel1_3, 2, 2, 1, 1);

        cmbTecmPartition = new QComboBox(MultiPart);
        cmbTecmPartition->setObjectName(QString::fromUtf8("cmbTecmPartition"));

        partitionLayout->addWidget(cmbTecmPartition, 3, 1, 1, 1);

        textLabel2_3 = new QLabel(MultiPart);
        textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
        textLabel2_3->setFont(font);
        textLabel2_3->setWordWrap(false);

        partitionLayout->addWidget(textLabel2_3, 2, 0, 1, 1);

        cmbTibPartition = new QComboBox(MultiPart);
        cmbTibPartition->setObjectName(QString::fromUtf8("cmbTibPartition"));

        partitionLayout->addWidget(cmbTibPartition, 0, 1, 1, 1);

        cmbRunTib = new QComboBox(MultiPart);
        cmbRunTib->setObjectName(QString::fromUtf8("cmbRunTib"));

        partitionLayout->addWidget(cmbRunTib, 0, 3, 1, 1);

        textLabel2 = new QLabel(MultiPart);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setFont(font);
        textLabel2->setWordWrap(false);

        partitionLayout->addWidget(textLabel2, 0, 0, 1, 1);

        cmbTecpPartition = new QComboBox(MultiPart);
        cmbTecpPartition->setObjectName(QString::fromUtf8("cmbTecpPartition"));

        partitionLayout->addWidget(cmbTecpPartition, 2, 1, 1, 1);

        textLabel1 = new QLabel(MultiPart);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setFont(font);
        textLabel1->setWordWrap(false);

        partitionLayout->addWidget(textLabel1, 0, 2, 1, 1);

        cmbRunTob = new QComboBox(MultiPart);
        cmbRunTob->setObjectName(QString::fromUtf8("cmbRunTob"));

        partitionLayout->addWidget(cmbRunTob, 1, 3, 1, 1);

        cmbTobPartition = new QComboBox(MultiPart);
        cmbTobPartition->setObjectName(QString::fromUtf8("cmbTobPartition"));

        partitionLayout->addWidget(cmbTobPartition, 1, 1, 1, 1);

        label_2 = new QLabel(MultiPart);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        partitionLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(MultiPart);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        partitionLayout->addWidget(label_3, 1, 2, 1, 1);


        vboxLayout->addLayout(partitionLayout);

        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Minimum);

        vboxLayout->addItem(verticalSpacer);

        gridLayout1 = new QGridLayout();
        gridLayout1->setSpacing(5);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gridLayout1->setContentsMargins(50, -1, 50, 10);
        lblTibAna = new QLabel(MultiPart);
        lblTibAna->setObjectName(QString::fromUtf8("lblTibAna"));
        lblTibAna->setFont(font);
        lblTibAna->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTibAna, 1, 5, 1, 1);

        lblConnversion = new QLabel(MultiPart);
        lblConnversion->setObjectName(QString::fromUtf8("lblConnversion"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        lblConnversion->setFont(font1);
        lblConnversion->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblConnversion, 0, 1, 1, 1);

        lblFedversion = new QLabel(MultiPart);
        lblFedversion->setObjectName(QString::fromUtf8("lblFedversion"));
        lblFedversion->setFont(font1);
        lblFedversion->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblFedversion, 0, 2, 1, 1);

        lblFecVersion = new QLabel(MultiPart);
        lblFecVersion->setObjectName(QString::fromUtf8("lblFecVersion"));
        lblFecVersion->setFont(font1);
        lblFecVersion->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblFecVersion, 0, 3, 1, 1);

        lblTibConn = new QLabel(MultiPart);
        lblTibConn->setObjectName(QString::fromUtf8("lblTibConn"));
        lblTibConn->setFont(font);
        lblTibConn->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTibConn, 1, 1, 1, 1);

        lblTecp = new QLabel(MultiPart);
        lblTecp->setObjectName(QString::fromUtf8("lblTecp"));
        lblTecp->setFont(font);
        lblTecp->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecp, 3, 0, 1, 1);

        lblTecm = new QLabel(MultiPart);
        lblTecm->setObjectName(QString::fromUtf8("lblTecm"));
        lblTecm->setFont(font);
        lblTecm->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecm, 4, 0, 1, 1);

        lblTob = new QLabel(MultiPart);
        lblTob->setObjectName(QString::fromUtf8("lblTob"));
        lblTob->setFont(font);
        lblTob->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTob, 2, 0, 1, 1);

        lblTobConn = new QLabel(MultiPart);
        lblTobConn->setObjectName(QString::fromUtf8("lblTobConn"));
        lblTobConn->setFont(font);
        lblTobConn->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTobConn, 2, 1, 1, 1);

        lblTib = new QLabel(MultiPart);
        lblTib->setObjectName(QString::fromUtf8("lblTib"));
        lblTib->setFont(font);
        lblTib->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTib, 1, 0, 1, 1);

        lblTibFed = new QLabel(MultiPart);
        lblTibFed->setObjectName(QString::fromUtf8("lblTibFed"));
        lblTibFed->setFont(font);
        lblTibFed->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTibFed, 1, 2, 1, 1);

        lblTobFec = new QLabel(MultiPart);
        lblTobFec->setObjectName(QString::fromUtf8("lblTobFec"));
        lblTobFec->setFont(font);
        lblTobFec->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTobFec, 2, 3, 1, 1);

        lblTecpConn = new QLabel(MultiPart);
        lblTecpConn->setObjectName(QString::fromUtf8("lblTecpConn"));
        lblTecpConn->setFont(font);
        lblTecpConn->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecpConn, 3, 1, 1, 1);

        lblTibFec = new QLabel(MultiPart);
        lblTibFec->setObjectName(QString::fromUtf8("lblTibFec"));
        lblTibFec->setFont(font);
        lblTibFec->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTibFec, 1, 3, 1, 1);

        lblTecmConn = new QLabel(MultiPart);
        lblTecmConn->setObjectName(QString::fromUtf8("lblTecmConn"));
        lblTecmConn->setFont(font);
        lblTecmConn->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecmConn, 4, 1, 1, 1);

        lblPartname = new QLabel(MultiPart);
        lblPartname->setObjectName(QString::fromUtf8("lblPartname"));
        lblPartname->setFont(font1);
        lblPartname->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblPartname, 0, 0, 1, 1);

        lblTibMask = new QLabel(MultiPart);
        lblTibMask->setObjectName(QString::fromUtf8("lblTibMask"));
        lblTibMask->setFont(font);
        lblTibMask->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTibMask, 1, 4, 1, 1);

        lblTecmMask = new QLabel(MultiPart);
        lblTecmMask->setObjectName(QString::fromUtf8("lblTecmMask"));
        lblTecmMask->setFont(font);
        lblTecmMask->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecmMask, 4, 4, 1, 1);

        lblMaskversion = new QLabel(MultiPart);
        lblMaskversion->setObjectName(QString::fromUtf8("lblMaskversion"));
        lblMaskversion->setFont(font1);
        lblMaskversion->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblMaskversion, 0, 4, 1, 1);

        lblAnalysisversion = new QLabel(MultiPart);
        lblAnalysisversion->setObjectName(QString::fromUtf8("lblAnalysisversion"));
        lblAnalysisversion->setFont(font1);
        lblAnalysisversion->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblAnalysisversion, 0, 5, 1, 1);

        lblTobFed = new QLabel(MultiPart);
        lblTobFed->setObjectName(QString::fromUtf8("lblTobFed"));
        lblTobFed->setFont(font);
        lblTobFed->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTobFed, 2, 2, 1, 1);

        lblTecpFed = new QLabel(MultiPart);
        lblTecpFed->setObjectName(QString::fromUtf8("lblTecpFed"));
        lblTecpFed->setFont(font);
        lblTecpFed->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecpFed, 3, 2, 1, 1);

        lblTecmFed = new QLabel(MultiPart);
        lblTecmFed->setObjectName(QString::fromUtf8("lblTecmFed"));
        lblTecmFed->setFont(font);
        lblTecmFed->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecmFed, 4, 2, 1, 1);

        lblTecpFec = new QLabel(MultiPart);
        lblTecpFec->setObjectName(QString::fromUtf8("lblTecpFec"));
        lblTecpFec->setFont(font);
        lblTecpFec->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecpFec, 3, 3, 1, 1);

        lblTecmFec = new QLabel(MultiPart);
        lblTecmFec->setObjectName(QString::fromUtf8("lblTecmFec"));
        lblTecmFec->setFont(font);
        lblTecmFec->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecmFec, 4, 3, 1, 1);

        lblTobMask = new QLabel(MultiPart);
        lblTobMask->setObjectName(QString::fromUtf8("lblTobMask"));
        lblTobMask->setFont(font);
        lblTobMask->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTobMask, 2, 4, 1, 1);

        lblTecpMask = new QLabel(MultiPart);
        lblTecpMask->setObjectName(QString::fromUtf8("lblTecpMask"));
        lblTecpMask->setFont(font);
        lblTecpMask->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecpMask, 3, 4, 1, 1);

        lblTobAna = new QLabel(MultiPart);
        lblTobAna->setObjectName(QString::fromUtf8("lblTobAna"));
        lblTobAna->setFont(font);
        lblTobAna->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTobAna, 2, 5, 1, 1);

        lblTecpAna = new QLabel(MultiPart);
        lblTecpAna->setObjectName(QString::fromUtf8("lblTecpAna"));
        lblTecpAna->setFont(font);
        lblTecpAna->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecpAna, 3, 5, 1, 1);

        lblTecmAna = new QLabel(MultiPart);
        lblTecmAna->setObjectName(QString::fromUtf8("lblTecmAna"));
        lblTecmAna->setFont(font);
        lblTecmAna->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecmAna, 4, 5, 1, 1);

        lblDcu = new QLabel(MultiPart);
        lblDcu->setObjectName(QString::fromUtf8("lblDcu"));
        lblDcu->setFont(font1);
        lblDcu->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblDcu, 0, 6, 1, 1);

        lblTibDcu = new QLabel(MultiPart);
        lblTibDcu->setObjectName(QString::fromUtf8("lblTibDcu"));
        lblTibDcu->setFont(font);
        lblTibDcu->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTibDcu, 1, 6, 1, 1);

        lblTecmDcu = new QLabel(MultiPart);
        lblTecmDcu->setObjectName(QString::fromUtf8("lblTecmDcu"));
        lblTecmDcu->setFont(font);
        lblTecmDcu->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecmDcu, 4, 6, 1, 1);

        lblTobDcu = new QLabel(MultiPart);
        lblTobDcu->setObjectName(QString::fromUtf8("lblTobDcu"));
        lblTobDcu->setFont(font);
        lblTobDcu->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTobDcu, 2, 6, 1, 1);

        lblTecpDcu = new QLabel(MultiPart);
        lblTecpDcu->setObjectName(QString::fromUtf8("lblTecpDcu"));
        lblTecpDcu->setFont(font);
        lblTecpDcu->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecpDcu, 3, 6, 1, 1);

        lblDcupsu = new QLabel(MultiPart);
        lblDcupsu->setObjectName(QString::fromUtf8("lblDcupsu"));
        lblDcupsu->setFont(font1);
        lblDcupsu->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblDcupsu, 0, 7, 1, 1);

        lblTibDcupsu = new QLabel(MultiPart);
        lblTibDcupsu->setObjectName(QString::fromUtf8("lblTibDcupsu"));
        lblTibDcupsu->setFont(font);
        lblTibDcupsu->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTibDcupsu, 1, 7, 1, 1);

        lblTobDcupsu = new QLabel(MultiPart);
        lblTobDcupsu->setObjectName(QString::fromUtf8("lblTobDcupsu"));
        lblTobDcupsu->setFont(font);
        lblTobDcupsu->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTobDcupsu, 2, 7, 1, 1);

        lblTecpDcupsu = new QLabel(MultiPart);
        lblTecpDcupsu->setObjectName(QString::fromUtf8("lblTecpDcupsu"));
        lblTecpDcupsu->setFont(font);
        lblTecpDcupsu->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecpDcupsu, 3, 7, 1, 1);

        lblTecmDcupsu = new QLabel(MultiPart);
        lblTecmDcupsu->setObjectName(QString::fromUtf8("lblTecmDcupsu"));
        lblTecmDcupsu->setFont(font);
        lblTecmDcupsu->setStyleSheet(QString::fromUtf8("border: 2px solid black"));

        gridLayout1->addWidget(lblTecmDcupsu, 4, 7, 1, 1);


        vboxLayout->addLayout(gridLayout1);

        spacer8_2 = new QSpacerItem(21, 150, QSizePolicy::Minimum, QSizePolicy::Minimum);

        vboxLayout->addItem(spacer8_2);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        hboxLayout1->addItem(horizontalSpacer);

        btnShow = new QPushButton(MultiPart);
        btnShow->setObjectName(QString::fromUtf8("btnShow"));
        btnShow->setEnabled(true);
        sizePolicy1.setHeightForWidth(btnShow->sizePolicy().hasHeightForWidth());
        btnShow->setSizePolicy(sizePolicy1);
        btnShow->setMinimumSize(QSize(100, 100));
        QFont font2;
        font2.setPointSize(14);
        btnShow->setFont(font2);
        btnShow->setAutoDefault(true);

        hboxLayout1->addWidget(btnShow);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        hboxLayout1->addItem(horizontalSpacer_2);


        vboxLayout->addLayout(hboxLayout1);


        gridLayout->addLayout(vboxLayout, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);


        retranslateUi(MultiPart);

        QMetaObject::connectSlotsByName(MultiPart);
    } // setupUi

    void retranslateUi(QConnectedTabWidget *MultiPart)
    {
        MultiPart->setWindowTitle(QApplication::translate("MultiPart", "All Tracker Results", 0, QApplication::UnicodeUTF8));
        textLabel3->setText(QApplication::translate("MultiPart", "<html><head/><body><p><br/><span style=\" font-size:xx-large; font-weight:600;\">View Partitions Simultaneously</span></p><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
        btnUpdate->setText(QApplication::translate("MultiPart", "Update", 0, QApplication::UnicodeUTF8));
        textLabel1_4->setText(QApplication::translate("MultiPart", "<p align=\"right\">Run Nr.</p>", 0, QApplication::UnicodeUTF8));
        textLabel2_4->setText(QApplication::translate("MultiPart", "<p align=\"right\">TEC-</p>", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("MultiPart", "<p align=\"right\">Run Nr.</p>", 0, QApplication::UnicodeUTF8));
        textLabel2_3->setText(QApplication::translate("MultiPart", "<p align=\"right\">TEC+</p>", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("MultiPart", "<p align=\"right\">TIB/TID</p>", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("MultiPart", "<p align=\"right\">Run Nr.</p>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MultiPart", "<html><head/><body><p align=\"right\">TOB</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MultiPart", "<html><head/><body><p align=\"right\">Run Nr.</p></body></html>", 0, QApplication::UnicodeUTF8));
        lblTibAna->setText(QString());
        lblConnversion->setText(QApplication::translate("MultiPart", "Connection", 0, QApplication::UnicodeUTF8));
        lblFedversion->setText(QApplication::translate("MultiPart", "FED", 0, QApplication::UnicodeUTF8));
        lblFecVersion->setText(QApplication::translate("MultiPart", "FEC", 0, QApplication::UnicodeUTF8));
        lblTibConn->setText(QString());
        lblTecp->setText(QApplication::translate("MultiPart", "TEC+", 0, QApplication::UnicodeUTF8));
        lblTecm->setText(QApplication::translate("MultiPart", "TEC-", 0, QApplication::UnicodeUTF8));
        lblTob->setText(QApplication::translate("MultiPart", "TOB", 0, QApplication::UnicodeUTF8));
        lblTobConn->setText(QString());
        lblTib->setText(QApplication::translate("MultiPart", "TIB/TID", 0, QApplication::UnicodeUTF8));
        lblTibFed->setText(QString());
        lblTobFec->setText(QString());
        lblTecpConn->setText(QString());
        lblTibFec->setText(QString());
        lblTecmConn->setText(QString());
        lblPartname->setText(QApplication::translate("MultiPart", "Partition", 0, QApplication::UnicodeUTF8));
        lblTibMask->setText(QString());
        lblTecmMask->setText(QString());
        lblMaskversion->setText(QApplication::translate("MultiPart", "Mask", 0, QApplication::UnicodeUTF8));
        lblAnalysisversion->setText(QApplication::translate("MultiPart", "Analysis", 0, QApplication::UnicodeUTF8));
        lblTobFed->setText(QString());
        lblTecpFed->setText(QString());
        lblTecmFed->setText(QString());
        lblTecpFec->setText(QString());
        lblTecmFec->setText(QString());
        lblTobMask->setText(QString());
        lblTecpMask->setText(QString());
        lblTobAna->setText(QString());
        lblTecpAna->setText(QString());
        lblTecmAna->setText(QString());
        lblDcu->setText(QApplication::translate("MultiPart", "DCU Info", 0, QApplication::UnicodeUTF8));
        lblTibDcu->setText(QString());
        lblTecmDcu->setText(QString());
        lblTobDcu->setText(QString());
        lblTecpDcu->setText(QString());
        lblDcupsu->setText(QApplication::translate("MultiPart", "DCU-PSU Map", 0, QApplication::UnicodeUTF8));
        lblTibDcupsu->setText(QString());
        lblTobDcupsu->setText(QString());
        lblTecpDcupsu->setText(QString());
        lblTecmDcupsu->setText(QString());
        btnShow->setText(QApplication::translate("MultiPart", "Show Results", 0, QApplication::UnicodeUTF8));
        btnShow->setShortcut(QString());
    } // retranslateUi

};

namespace Ui {
    class MultiPart: public Ui_MultiPart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMULTIPART_H
