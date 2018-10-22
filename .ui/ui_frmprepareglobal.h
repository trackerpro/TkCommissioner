/********************************************************************************
** Form generated from reading UI file 'frmprepareglobal.ui'
**
** Created: Mon Oct 22 16:28:21 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMPREPAREGLOBAL_H
#define UI_FRMPREPAREGLOBAL_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
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
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrepareGlobal
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QFrame *line1_2_2;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel2_2_2;
    QSpacerItem *spacer28_2;
    QLabel *textLabel2_2_2_2_2;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacer12_3;
    QLabel *validReadOut;
    QSpacerItem *spacer12_2_2;
    QSpacerItem *spacer36;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacer28;
    QPushButton *btnQuit;
    QFrame *line1;
    QHBoxLayout *hboxLayout3;
    QGridLayout *gridLayout2;
    QSpacerItem *spacer33;
    QComboBox *cmbTecp;
    QPushButton *btnSetConf;
    QSpacerItem *spacer2_3;
    QComboBox *cmbTecm;
    QLabel *txtTecp;
    QPushButton *btnTecmMore;
    QSpacerItem *spacer2_6;
    QComboBox *cmbTob;
    QSpacerItem *spacer2_4;
    QPushButton *btnTobMore;
    QSpacerItem *spacer2;
    QSpacerItem *spacer2_2;
    QPushButton *btnTecpMore;
    QSpacerItem *spacer2_4_3;
    QSpacerItem *spacer2_4_3_2;
    QSpacerItem *spacer2_3_3;
    QComboBox *cmbTib;
    QSpacerItem *spacer2_2_3;
    QLabel *txtTob;
    QLabel *txtTib;
    QLabel *txtTecm;
    QPushButton *btnTibMore;
    QSpacerItem *spacer65_2_2;
    QVBoxLayout *vboxLayout2;
    QPushButton *btnCheck;
    QHBoxLayout *hboxLayout4;
    QLabel *textLabel2;
    QLineEdit *linLastIov;
    QHBoxLayout *hboxLayout5;
    QLabel *textLabel2_2;
    QLineEdit *linNextRun;
    QHBoxLayout *hboxLayout6;
    QVBoxLayout *vboxLayout3;
    QLabel *textLabel2_2_2_2;
    QSpacerItem *spacer28_2_2;
    QVBoxLayout *vboxLayout4;
    QHBoxLayout *hboxLayout7;
    QSpacerItem *spacer12;
    QLabel *lblUpdate;
    QSpacerItem *spacer12_2;
    QSpacerItem *spacer37;
    QHBoxLayout *hboxLayout8;
    QVBoxLayout *vboxLayout5;
    QGridLayout *gridLayout3;
    QLabel *latencyTecp;
    QComboBox *comboBoxReadRouteTecm;
    QSpacerItem *spacer2_4_2;
    QComboBox *comboBoxReadRouteTob;
    QComboBox *comboBoxMSMTecp;
    QLabel *labelReadRoute;
    QLabel *txtTecp_2;
    QLabel *latencyTob;
    QLabel *txtTib_2;
    QLabel *txtTob_2;
    QLabel *labelSuperMode;
    QLabel *textLabel1;
    QLabel *txtTecm_2;
    QSpacerItem *spacer2_3_2;
    QLabel *latencyTib;
    QComboBox *comboBoxMSMTib;
    QComboBox *comboBoxReadRouteTecp;
    QComboBox *comboBoxMSMTob;
    QSpacerItem *spacer2_2_2;
    QLabel *latencyTecm;
    QHBoxLayout *hboxLayout9;
    Q3Frame *frame3;
    QLabel *textLabel1_2;
    QComboBox *comboBoxReadRouteTib;
    QSpacerItem *spacer2_5;
    QComboBox *comboBoxMSMTecm;
    QHBoxLayout *hboxLayout10;
    QPushButton *btnAllToGlobal;
    QPushButton *btnAllToLocal;
    QPushButton *btnRevertConfiguration;
    QPushButton *btnApplyChanges;
    QSpacerItem *spacer65_2;

    void setupUi(QMainWindow *PrepareGlobal)
    {
        if (PrepareGlobal->objectName().isEmpty())
            PrepareGlobal->setObjectName(QString::fromUtf8("PrepareGlobal"));
        PrepareGlobal->resize(757, 473);
        widget = new QWidget(PrepareGlobal);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 1044, 708));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout1 = new QGridLayout();
        gridLayout1->setSpacing(6);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        line1_2_2 = new QFrame(widget);
        line1_2_2->setObjectName(QString::fromUtf8("line1_2_2"));
        line1_2_2->setFrameShape(QFrame::HLine);
        line1_2_2->setFrameShadow(QFrame::Sunken);

        gridLayout1->addWidget(line1_2_2, 1, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        textLabel2_2_2 = new QLabel(widget);
        textLabel2_2_2->setObjectName(QString::fromUtf8("textLabel2_2_2"));
        textLabel2_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_2_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2_2_2);

        spacer28_2 = new QSpacerItem(20, 110, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacer28_2);

        textLabel2_2_2_2_2 = new QLabel(widget);
        textLabel2_2_2_2_2->setObjectName(QString::fromUtf8("textLabel2_2_2_2_2"));
        textLabel2_2_2_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_2_2_2_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2_2_2_2_2);


        hboxLayout->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacer12_3 = new QSpacerItem(23, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacer12_3);

        validReadOut = new QLabel(widget);
        validReadOut->setObjectName(QString::fromUtf8("validReadOut"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(validReadOut->sizePolicy().hasHeightForWidth());
        validReadOut->setSizePolicy(sizePolicy);
        validReadOut->setPixmap(QPixmap(qPixmapFromMimeSource("images/round_question.png")));
        validReadOut->setScaledContents(true);
        validReadOut->setWordWrap(false);

        hboxLayout1->addWidget(validReadOut);

        spacer12_2_2 = new QSpacerItem(23, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacer12_2_2);


        vboxLayout1->addLayout(hboxLayout1);

        spacer36 = new QSpacerItem(41, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacer36);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        spacer28 = new QSpacerItem(40, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacer28);

        btnQuit = new QPushButton(widget);
        btnQuit->setObjectName(QString::fromUtf8("btnQuit"));
        btnQuit->setMinimumSize(QSize(0, 0));
        btnQuit->setDefault(true);

        hboxLayout2->addWidget(btnQuit);


        vboxLayout1->addLayout(hboxLayout2);


        hboxLayout->addLayout(vboxLayout1);


        gridLayout1->addLayout(hboxLayout, 2, 1, 1, 1);

        line1 = new QFrame(widget);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);

        gridLayout1->addWidget(line1, 1, 1, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        gridLayout2 = new QGridLayout();
        gridLayout2->setSpacing(6);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        spacer33 = new QSpacerItem(100, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacer33, 4, 0, 1, 2);

        cmbTecp = new QComboBox(widget);
        cmbTecp->setObjectName(QString::fromUtf8("cmbTecp"));
        cmbTecp->setMinimumSize(QSize(160, 0));
        cmbTecp->setDuplicatesEnabled(false);

        gridLayout2->addWidget(cmbTecp, 2, 2, 1, 1);

        btnSetConf = new QPushButton(widget);
        btnSetConf->setObjectName(QString::fromUtf8("btnSetConf"));
        btnSetConf->setMinimumSize(QSize(240, 0));

        gridLayout2->addWidget(btnSetConf, 4, 2, 1, 2);

        spacer2_3 = new QSpacerItem(10, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacer2_3, 2, 1, 1, 1);

        cmbTecm = new QComboBox(widget);
        cmbTecm->setObjectName(QString::fromUtf8("cmbTecm"));
        cmbTecm->setMinimumSize(QSize(160, 0));
        cmbTecm->setDuplicatesEnabled(false);

        gridLayout2->addWidget(cmbTecm, 3, 2, 1, 1);

        txtTecp = new QLabel(widget);
        txtTecp->setObjectName(QString::fromUtf8("txtTecp"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txtTecp->sizePolicy().hasHeightForWidth());
        txtTecp->setSizePolicy(sizePolicy1);
        txtTecp->setWordWrap(false);

        gridLayout2->addWidget(txtTecp, 2, 0, 1, 1);

        btnTecmMore = new QPushButton(widget);
        btnTecmMore->setObjectName(QString::fromUtf8("btnTecmMore"));

        gridLayout2->addWidget(btnTecmMore, 3, 3, 1, 1);

        spacer2_6 = new QSpacerItem(40, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacer2_6, 0, 4, 1, 1);

        cmbTob = new QComboBox(widget);
        cmbTob->setObjectName(QString::fromUtf8("cmbTob"));
        cmbTob->setMinimumSize(QSize(160, 0));
        cmbTob->setDuplicatesEnabled(false);

        gridLayout2->addWidget(cmbTob, 1, 2, 1, 1);

        spacer2_4 = new QSpacerItem(10, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacer2_4, 3, 1, 1, 1);

        btnTobMore = new QPushButton(widget);
        btnTobMore->setObjectName(QString::fromUtf8("btnTobMore"));

        gridLayout2->addWidget(btnTobMore, 1, 3, 1, 1);

        spacer2 = new QSpacerItem(10, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacer2, 0, 1, 1, 1);

        spacer2_2 = new QSpacerItem(10, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacer2_2, 1, 1, 1, 1);

        btnTecpMore = new QPushButton(widget);
        btnTecpMore->setObjectName(QString::fromUtf8("btnTecpMore"));

        gridLayout2->addWidget(btnTecpMore, 2, 3, 1, 1);

        spacer2_4_3 = new QSpacerItem(40, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacer2_4_3, 3, 4, 1, 1);

        spacer2_4_3_2 = new QSpacerItem(40, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacer2_4_3_2, 4, 4, 1, 1);

        spacer2_3_3 = new QSpacerItem(40, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacer2_3_3, 2, 4, 1, 1);

        cmbTib = new QComboBox(widget);
        cmbTib->setObjectName(QString::fromUtf8("cmbTib"));
        cmbTib->setMinimumSize(QSize(160, 0));
        cmbTib->setDuplicatesEnabled(false);

        gridLayout2->addWidget(cmbTib, 0, 2, 1, 1);

        spacer2_2_3 = new QSpacerItem(40, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacer2_2_3, 1, 4, 1, 1);

        txtTob = new QLabel(widget);
        txtTob->setObjectName(QString::fromUtf8("txtTob"));
        txtTob->setWordWrap(false);

        gridLayout2->addWidget(txtTob, 1, 0, 1, 1);

        txtTib = new QLabel(widget);
        txtTib->setObjectName(QString::fromUtf8("txtTib"));
        txtTib->setWordWrap(false);

        gridLayout2->addWidget(txtTib, 0, 0, 1, 1);

        txtTecm = new QLabel(widget);
        txtTecm->setObjectName(QString::fromUtf8("txtTecm"));
        txtTecm->setWordWrap(false);

        gridLayout2->addWidget(txtTecm, 3, 0, 1, 1);

        btnTibMore = new QPushButton(widget);
        btnTibMore->setObjectName(QString::fromUtf8("btnTibMore"));

        gridLayout2->addWidget(btnTibMore, 0, 3, 1, 1);


        hboxLayout3->addLayout(gridLayout2);

        spacer65_2_2 = new QSpacerItem(16, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacer65_2_2);


        gridLayout1->addLayout(hboxLayout3, 0, 0, 1, 1);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        btnCheck = new QPushButton(widget);
        btnCheck->setObjectName(QString::fromUtf8("btnCheck"));
        btnCheck->setMinimumSize(QSize(110, 0));

        vboxLayout2->addWidget(btnCheck);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        textLabel2 = new QLabel(widget);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2->setWordWrap(false);

        hboxLayout4->addWidget(textLabel2);

        linLastIov = new QLineEdit(widget);
        linLastIov->setObjectName(QString::fromUtf8("linLastIov"));
        linLastIov->setAlignment(Qt::AlignHCenter);
        linLastIov->setReadOnly(true);

        hboxLayout4->addWidget(linLastIov);


        vboxLayout2->addLayout(hboxLayout4);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        textLabel2_2 = new QLabel(widget);
        textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
        textLabel2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_2->setWordWrap(false);

        hboxLayout5->addWidget(textLabel2_2);

        linNextRun = new QLineEdit(widget);
        linNextRun->setObjectName(QString::fromUtf8("linNextRun"));
        linNextRun->setAlignment(Qt::AlignHCenter);
        linNextRun->setReadOnly(true);

        hboxLayout5->addWidget(linNextRun);


        vboxLayout2->addLayout(hboxLayout5);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        textLabel2_2_2_2 = new QLabel(widget);
        textLabel2_2_2_2->setObjectName(QString::fromUtf8("textLabel2_2_2_2"));
        textLabel2_2_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_2_2_2->setWordWrap(false);

        vboxLayout3->addWidget(textLabel2_2_2_2);

        spacer28_2_2 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout3->addItem(spacer28_2_2);


        hboxLayout6->addLayout(vboxLayout3);

        vboxLayout4 = new QVBoxLayout();
        vboxLayout4->setSpacing(6);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        spacer12 = new QSpacerItem(23, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout7->addItem(spacer12);

        lblUpdate = new QLabel(widget);
        lblUpdate->setObjectName(QString::fromUtf8("lblUpdate"));
        sizePolicy.setHeightForWidth(lblUpdate->sizePolicy().hasHeightForWidth());
        lblUpdate->setSizePolicy(sizePolicy);
        lblUpdate->setPixmap(QPixmap(qPixmapFromMimeSource("images/round_question.png")));
        lblUpdate->setScaledContents(true);
        lblUpdate->setWordWrap(false);

        hboxLayout7->addWidget(lblUpdate);

        spacer12_2 = new QSpacerItem(23, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout7->addItem(spacer12_2);


        vboxLayout4->addLayout(hboxLayout7);

        spacer37 = new QSpacerItem(21, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout4->addItem(spacer37);


        hboxLayout6->addLayout(vboxLayout4);


        vboxLayout2->addLayout(hboxLayout6);


        gridLayout1->addLayout(vboxLayout2, 0, 1, 1, 1);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        vboxLayout5 = new QVBoxLayout();
        vboxLayout5->setSpacing(6);
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        gridLayout3 = new QGridLayout();
        gridLayout3->setSpacing(6);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        latencyTecp = new QLabel(widget);
        latencyTecp->setObjectName(QString::fromUtf8("latencyTecp"));
        latencyTecp->setMinimumSize(QSize(30, 0));
        latencyTecp->setFrameShape(QFrame::Box);
        latencyTecp->setWordWrap(false);

        gridLayout3->addWidget(latencyTecp, 3, 2, 1, 1);

        comboBoxReadRouteTecm = new QComboBox(widget);
        comboBoxReadRouteTecm->setObjectName(QString::fromUtf8("comboBoxReadRouteTecm"));

        gridLayout3->addWidget(comboBoxReadRouteTecm, 4, 3, 1, 1);

        spacer2_4_2 = new QSpacerItem(16, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout3->addItem(spacer2_4_2, 4, 1, 1, 1);

        comboBoxReadRouteTob = new QComboBox(widget);
        comboBoxReadRouteTob->setObjectName(QString::fromUtf8("comboBoxReadRouteTob"));

        gridLayout3->addWidget(comboBoxReadRouteTob, 2, 3, 1, 1);

        comboBoxMSMTecp = new QComboBox(widget);
        comboBoxMSMTecp->setObjectName(QString::fromUtf8("comboBoxMSMTecp"));

        gridLayout3->addWidget(comboBoxMSMTecp, 3, 4, 1, 1);

        labelReadRoute = new QLabel(widget);
        labelReadRoute->setObjectName(QString::fromUtf8("labelReadRoute"));
        labelReadRoute->setWordWrap(false);

        gridLayout3->addWidget(labelReadRoute, 0, 3, 1, 1);

        txtTecp_2 = new QLabel(widget);
        txtTecp_2->setObjectName(QString::fromUtf8("txtTecp_2"));
        sizePolicy1.setHeightForWidth(txtTecp_2->sizePolicy().hasHeightForWidth());
        txtTecp_2->setSizePolicy(sizePolicy1);
        txtTecp_2->setWordWrap(false);

        gridLayout3->addWidget(txtTecp_2, 3, 0, 1, 1);

        latencyTob = new QLabel(widget);
        latencyTob->setObjectName(QString::fromUtf8("latencyTob"));
        latencyTob->setMinimumSize(QSize(30, 0));
        latencyTob->setFrameShape(QFrame::Box);
        latencyTob->setWordWrap(false);

        gridLayout3->addWidget(latencyTob, 2, 2, 1, 1);

        txtTib_2 = new QLabel(widget);
        txtTib_2->setObjectName(QString::fromUtf8("txtTib_2"));
        txtTib_2->setMinimumSize(QSize(140, 0));
        txtTib_2->setWordWrap(false);

        gridLayout3->addWidget(txtTib_2, 1, 0, 1, 1);

        txtTob_2 = new QLabel(widget);
        txtTob_2->setObjectName(QString::fromUtf8("txtTob_2"));
        txtTob_2->setWordWrap(false);

        gridLayout3->addWidget(txtTob_2, 2, 0, 1, 1);

        labelSuperMode = new QLabel(widget);
        labelSuperMode->setObjectName(QString::fromUtf8("labelSuperMode"));
        labelSuperMode->setWordWrap(false);

        gridLayout3->addWidget(labelSuperMode, 0, 4, 1, 1);

        textLabel1 = new QLabel(widget);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout3->addWidget(textLabel1, 0, 2, 1, 1);

        txtTecm_2 = new QLabel(widget);
        txtTecm_2->setObjectName(QString::fromUtf8("txtTecm_2"));
        txtTecm_2->setWordWrap(false);

        gridLayout3->addWidget(txtTecm_2, 4, 0, 1, 1);

        spacer2_3_2 = new QSpacerItem(19, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout3->addItem(spacer2_3_2, 3, 1, 1, 1);

        latencyTib = new QLabel(widget);
        latencyTib->setObjectName(QString::fromUtf8("latencyTib"));
        latencyTib->setMinimumSize(QSize(30, 0));
        latencyTib->setFrameShape(QFrame::Box);
        latencyTib->setWordWrap(false);

        gridLayout3->addWidget(latencyTib, 1, 2, 1, 1);

        comboBoxMSMTib = new QComboBox(widget);
        comboBoxMSMTib->setObjectName(QString::fromUtf8("comboBoxMSMTib"));

        gridLayout3->addWidget(comboBoxMSMTib, 1, 4, 1, 1);

        comboBoxReadRouteTecp = new QComboBox(widget);
        comboBoxReadRouteTecp->setObjectName(QString::fromUtf8("comboBoxReadRouteTecp"));

        gridLayout3->addWidget(comboBoxReadRouteTecp, 3, 3, 1, 1);

        comboBoxMSMTob = new QComboBox(widget);
        comboBoxMSMTob->setObjectName(QString::fromUtf8("comboBoxMSMTob"));

        gridLayout3->addWidget(comboBoxMSMTob, 2, 4, 1, 1);

        spacer2_2_2 = new QSpacerItem(19, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout3->addItem(spacer2_2_2, 2, 1, 1, 1);

        latencyTecm = new QLabel(widget);
        latencyTecm->setObjectName(QString::fromUtf8("latencyTecm"));
        latencyTecm->setMinimumSize(QSize(30, 0));
        latencyTecm->setFrameShape(QFrame::Box);
        latencyTecm->setWordWrap(false);

        gridLayout3->addWidget(latencyTecm, 4, 2, 1, 1);

        hboxLayout9 = new QHBoxLayout();
        hboxLayout9->setSpacing(6);
        hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
        frame3 = new Q3Frame(widget);
        frame3->setObjectName(QString::fromUtf8("frame3"));
        frame3->setMinimumSize(QSize(15, 15));
        frame3->setMaximumSize(QSize(30, 30));
        frame3->setFrameShape(QFrame::StyledPanel);
        frame3->setFrameShadow(QFrame::Plain);

        hboxLayout9->addWidget(frame3);

        textLabel1_2 = new QLabel(widget);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setMinimumSize(QSize(0, 30));
        textLabel1_2->setWordWrap(false);

        hboxLayout9->addWidget(textLabel1_2);


        gridLayout3->addLayout(hboxLayout9, 0, 0, 1, 1);

        comboBoxReadRouteTib = new QComboBox(widget);
        comboBoxReadRouteTib->setObjectName(QString::fromUtf8("comboBoxReadRouteTib"));

        gridLayout3->addWidget(comboBoxReadRouteTib, 1, 3, 1, 1);

        spacer2_5 = new QSpacerItem(19, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout3->addItem(spacer2_5, 1, 1, 1, 1);

        comboBoxMSMTecm = new QComboBox(widget);
        comboBoxMSMTecm->setObjectName(QString::fromUtf8("comboBoxMSMTecm"));

        gridLayout3->addWidget(comboBoxMSMTecm, 4, 4, 1, 1);


        vboxLayout5->addLayout(gridLayout3);

        hboxLayout10 = new QHBoxLayout();
        hboxLayout10->setSpacing(6);
        hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
        btnAllToGlobal = new QPushButton(widget);
        btnAllToGlobal->setObjectName(QString::fromUtf8("btnAllToGlobal"));

        hboxLayout10->addWidget(btnAllToGlobal);

        btnAllToLocal = new QPushButton(widget);
        btnAllToLocal->setObjectName(QString::fromUtf8("btnAllToLocal"));

        hboxLayout10->addWidget(btnAllToLocal);

        btnRevertConfiguration = new QPushButton(widget);
        btnRevertConfiguration->setObjectName(QString::fromUtf8("btnRevertConfiguration"));

        hboxLayout10->addWidget(btnRevertConfiguration);

        btnApplyChanges = new QPushButton(widget);
        btnApplyChanges->setObjectName(QString::fromUtf8("btnApplyChanges"));

        hboxLayout10->addWidget(btnApplyChanges);


        vboxLayout5->addLayout(hboxLayout10);


        hboxLayout8->addLayout(vboxLayout5);

        spacer65_2 = new QSpacerItem(16, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout8->addItem(spacer65_2);


        gridLayout1->addLayout(hboxLayout8, 2, 0, 1, 1);


        gridLayout->addLayout(gridLayout1, 0, 0, 1, 1);

        PrepareGlobal->setCentralWidget(widget);

        retranslateUi(PrepareGlobal);

        QMetaObject::connectSlotsByName(PrepareGlobal);
    } // setupUi

    void retranslateUi(QMainWindow *PrepareGlobal)
    {
        PrepareGlobal->setWindowTitle(QApplication::translate("PrepareGlobal", "Prepare running state", 0, QApplication::UnicodeUTF8));
        textLabel2_2_2->setText(QApplication::translate("PrepareGlobal", "Valid:", 0, QApplication::UnicodeUTF8));
        textLabel2_2_2_2_2->setText(QApplication::translate("PrepareGlobal", "Ready for \n"
"Global:", 0, QApplication::UnicodeUTF8));
        btnQuit->setText(QApplication::translate("PrepareGlobal", "Quit", 0, QApplication::UnicodeUTF8));
        btnQuit->setShortcut(QApplication::translate("PrepareGlobal", "Esc", 0, QApplication::UnicodeUTF8));
        btnSetConf->setText(QApplication::translate("PrepareGlobal", "Save && O2O", 0, QApplication::UnicodeUTF8));
        btnSetConf->setShortcut(QString());
        txtTecp->setText(QApplication::translate("PrepareGlobal", "TEC plus", 0, QApplication::UnicodeUTF8));
        btnTecmMore->setText(QApplication::translate("PrepareGlobal", "...", 0, QApplication::UnicodeUTF8));
        btnTobMore->setText(QApplication::translate("PrepareGlobal", "...", 0, QApplication::UnicodeUTF8));
        btnTecpMore->setText(QApplication::translate("PrepareGlobal", "...", 0, QApplication::UnicodeUTF8));
        txtTob->setText(QApplication::translate("PrepareGlobal", "TOB", 0, QApplication::UnicodeUTF8));
        txtTib->setText(QApplication::translate("PrepareGlobal", "TIB/TID", 0, QApplication::UnicodeUTF8));
        txtTecm->setText(QApplication::translate("PrepareGlobal", "TEC minus", 0, QApplication::UnicodeUTF8));
        btnTibMore->setText(QApplication::translate("PrepareGlobal", "...", 0, QApplication::UnicodeUTF8));
        btnCheck->setText(QApplication::translate("PrepareGlobal", "Update", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("PrepareGlobal", "Last IOV:", 0, QApplication::UnicodeUTF8));
        textLabel2_2->setText(QApplication::translate("PrepareGlobal", "Next run:", 0, QApplication::UnicodeUTF8));
        textLabel2_2_2_2->setText(QApplication::translate("PrepareGlobal", "Ready for Global:", 0, QApplication::UnicodeUTF8));
        latencyTecp->setText(QApplication::translate("PrepareGlobal", "171", 0, QApplication::UnicodeUTF8));
        labelReadRoute->setText(QApplication::translate("PrepareGlobal", "Read Route", 0, QApplication::UnicodeUTF8));
        txtTecp_2->setText(QApplication::translate("PrepareGlobal", "TEC plus", 0, QApplication::UnicodeUTF8));
        latencyTob->setText(QApplication::translate("PrepareGlobal", "171", 0, QApplication::UnicodeUTF8));
        txtTib_2->setText(QApplication::translate("PrepareGlobal", "TIB/TID", 0, QApplication::UnicodeUTF8));
        txtTob_2->setText(QApplication::translate("PrepareGlobal", "TOB", 0, QApplication::UnicodeUTF8));
        labelSuperMode->setText(QApplication::translate("PrepareGlobal", "Mode/Super Mode", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("PrepareGlobal", "Latency", 0, QApplication::UnicodeUTF8));
        txtTecm_2->setText(QApplication::translate("PrepareGlobal", "TEC minus", 0, QApplication::UnicodeUTF8));
        latencyTib->setText(QApplication::translate("PrepareGlobal", "171", 0, QApplication::UnicodeUTF8));
        latencyTecm->setText(QApplication::translate("PrepareGlobal", "171", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("PrepareGlobal", "= partition in mixed state", 0, QApplication::UnicodeUTF8));
        btnAllToGlobal->setText(QApplication::translate("PrepareGlobal", "ALL To Zero Suppressed", 0, QApplication::UnicodeUTF8));
        btnAllToLocal->setText(QApplication::translate("PrepareGlobal", "ALL To Virgin Raw", 0, QApplication::UnicodeUTF8));
        btnRevertConfiguration->setText(QApplication::translate("PrepareGlobal", "Revert", 0, QApplication::UnicodeUTF8));
        btnApplyChanges->setText(QApplication::translate("PrepareGlobal", "Apply Changes", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PrepareGlobal: public Ui_PrepareGlobal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMPREPAREGLOBAL_H
