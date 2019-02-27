/********************************************************************************
** Form generated from reading UI file 'frmtreeviewer.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTREEVIEWER_H
#define UI_FRMTREEVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include "CustomTQtWidget.h"
#include "QConnectedTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_TreeViewer
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *chkSelMode;
    QComboBox *cmbCutOpt;
    QPushButton *btnGetSelected;
    QPushButton *btnDBUpload;
    QLabel *lblInfo;
    QPushButton *btnRef;
    QLabel *lblCut;
    QLineEdit *lineCut;
    QPushButton *btnTkMap;
    QPushButton *btnFedMap;
    QGridLayout *gridLayout;
    CustomTQtWidget *qtCanvas;
    QFrame *line_6;
    QHBoxLayout *horizontalLayout_12;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *xLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lblX;
    QComboBox *cmbX;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblXBins;
    QSpinBox *xSpinBins;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *chkLogX;
    QCheckBox *chkDiffX;
    QCheckBox *chkRefX;
    QFrame *line;
    QVBoxLayout *yLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblY;
    QComboBox *cmbY;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lblYBins;
    QSpinBox *ySpinBins;
    QHBoxLayout *horizontalLayout_13;
    QCheckBox *chkLogY;
    QCheckBox *chkDiffY;
    QCheckBox *chkRefY;
    QFrame *line_2;
    QVBoxLayout *zLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lblZ;
    QComboBox *cmbZ;
    QHBoxLayout *horizontalLayout_8;
    QLabel *lblZBins;
    QSpinBox *zSpinBins;
    QHBoxLayout *horizontalLayout_16;
    QCheckBox *chkLogZ;
    QCheckBox *chkDiffZ;
    QCheckBox *chkRefZ;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_6;
    QPushButton *btnDraw;
    QPushButton *btnShowSummary;
    QVBoxLayout *verticalLayout_8;
    QComboBox *cmbDrawOpt;
    QComboBox *cmbSummaryHists;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_11;
    QCheckBox *chkShowInvalid;
    QPushButton *btnPrintToFile;
    QFrame *line_7;

    void setupUi(QConnectedTabWidget *TreeViewer)
    {
        if (TreeViewer->objectName().isEmpty())
            TreeViewer->setObjectName(QString::fromUtf8("TreeViewer"));
        TreeViewer->resize(1039, 709);
        gridLayout_2 = new QGridLayout(TreeViewer);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        chkSelMode = new QCheckBox(TreeViewer);
        chkSelMode->setObjectName(QString::fromUtf8("chkSelMode"));
        chkSelMode->setEnabled(false);

        horizontalLayout_2->addWidget(chkSelMode);

        cmbCutOpt = new QComboBox(TreeViewer);
        cmbCutOpt->setObjectName(QString::fromUtf8("cmbCutOpt"));
        cmbCutOpt->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmbCutOpt->sizePolicy().hasHeightForWidth());
        cmbCutOpt->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(cmbCutOpt);

        btnGetSelected = new QPushButton(TreeViewer);
        btnGetSelected->setObjectName(QString::fromUtf8("btnGetSelected"));
        btnGetSelected->setEnabled(false);

        horizontalLayout_2->addWidget(btnGetSelected);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        btnDBUpload = new QPushButton(TreeViewer);
        btnDBUpload->setObjectName(QString::fromUtf8("btnDBUpload"));

        horizontalLayout_4->addWidget(btnDBUpload);

        lblInfo = new QLabel(TreeViewer);
        lblInfo->setObjectName(QString::fromUtf8("lblInfo"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblInfo->sizePolicy().hasHeightForWidth());
        lblInfo->setSizePolicy(sizePolicy1);
        lblInfo->setFrameShape(QFrame::Box);

        horizontalLayout_4->addWidget(lblInfo);

        btnRef = new QPushButton(TreeViewer);
        btnRef->setObjectName(QString::fromUtf8("btnRef"));

        horizontalLayout_4->addWidget(btnRef);

        lblCut = new QLabel(TreeViewer);
        lblCut->setObjectName(QString::fromUtf8("lblCut"));

        horizontalLayout_4->addWidget(lblCut);

        lineCut = new QLineEdit(TreeViewer);
        lineCut->setObjectName(QString::fromUtf8("lineCut"));

        horizontalLayout_4->addWidget(lineCut);

        btnTkMap = new QPushButton(TreeViewer);
        btnTkMap->setObjectName(QString::fromUtf8("btnTkMap"));

        horizontalLayout_4->addWidget(btnTkMap);

        btnFedMap = new QPushButton(TreeViewer);
        btnFedMap->setObjectName(QString::fromUtf8("btnFedMap"));

        horizontalLayout_4->addWidget(btnFedMap);


        verticalLayout_5->addLayout(horizontalLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        qtCanvas = new CustomTQtWidget(TreeViewer);
        qtCanvas->setObjectName(QString::fromUtf8("qtCanvas"));
        qtCanvas->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(qtCanvas->sizePolicy().hasHeightForWidth());
        qtCanvas->setSizePolicy(sizePolicy2);
        qtCanvas->setMinimumSize(QSize(500, 500));
        qtCanvas->setAutoFillBackground(true);

        gridLayout->addWidget(qtCanvas, 0, 0, 1, 1);


        verticalLayout_5->addLayout(gridLayout);

        line_6 = new QFrame(TreeViewer);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_6);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        line_4 = new QFrame(TreeViewer);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_12->addWidget(line_4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        xLayout = new QVBoxLayout();
        xLayout->setObjectName(QString::fromUtf8("xLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblX = new QLabel(TreeViewer);
        lblX->setObjectName(QString::fromUtf8("lblX"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lblX->sizePolicy().hasHeightForWidth());
        lblX->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(lblX);

        cmbX = new QComboBox(TreeViewer);
        cmbX->setObjectName(QString::fromUtf8("cmbX"));

        horizontalLayout->addWidget(cmbX);


        xLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        lblXBins = new QLabel(TreeViewer);
        lblXBins->setObjectName(QString::fromUtf8("lblXBins"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lblXBins->sizePolicy().hasHeightForWidth());
        lblXBins->setSizePolicy(sizePolicy4);

        horizontalLayout_5->addWidget(lblXBins);

        xSpinBins = new QSpinBox(TreeViewer);
        xSpinBins->setObjectName(QString::fromUtf8("xSpinBins"));
        xSpinBins->setMinimum(-1);
        xSpinBins->setMaximum(100000);
        xSpinBins->setValue(-1);

        horizontalLayout_5->addWidget(xSpinBins);


        xLayout->addLayout(horizontalLayout_5);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        chkLogX = new QCheckBox(TreeViewer);
        chkLogX->setObjectName(QString::fromUtf8("chkLogX"));

        horizontalLayout_10->addWidget(chkLogX);

        chkDiffX = new QCheckBox(TreeViewer);
        chkDiffX->setObjectName(QString::fromUtf8("chkDiffX"));
        chkDiffX->setEnabled(false);

        horizontalLayout_10->addWidget(chkDiffX);

        chkRefX = new QCheckBox(TreeViewer);
        chkRefX->setObjectName(QString::fromUtf8("chkRefX"));
        chkRefX->setEnabled(false);

        horizontalLayout_10->addWidget(chkRefX);


        xLayout->addLayout(horizontalLayout_10);


        horizontalLayout_11->addLayout(xLayout);

        line = new QFrame(TreeViewer);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_11->addWidget(line);

        yLayout = new QVBoxLayout();
        yLayout->setObjectName(QString::fromUtf8("yLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lblY = new QLabel(TreeViewer);
        lblY->setObjectName(QString::fromUtf8("lblY"));
        sizePolicy3.setHeightForWidth(lblY->sizePolicy().hasHeightForWidth());
        lblY->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(lblY);

        cmbY = new QComboBox(TreeViewer);
        cmbY->setObjectName(QString::fromUtf8("cmbY"));

        horizontalLayout_3->addWidget(cmbY);


        yLayout->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        lblYBins = new QLabel(TreeViewer);
        lblYBins->setObjectName(QString::fromUtf8("lblYBins"));
        lblYBins->setEnabled(false);

        horizontalLayout_7->addWidget(lblYBins);

        ySpinBins = new QSpinBox(TreeViewer);
        ySpinBins->setObjectName(QString::fromUtf8("ySpinBins"));
        ySpinBins->setEnabled(false);
        ySpinBins->setMinimum(-1);
        ySpinBins->setMaximum(100000);
        ySpinBins->setValue(-1);

        horizontalLayout_7->addWidget(ySpinBins);


        yLayout->addLayout(horizontalLayout_7);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        chkLogY = new QCheckBox(TreeViewer);
        chkLogY->setObjectName(QString::fromUtf8("chkLogY"));

        horizontalLayout_13->addWidget(chkLogY);

        chkDiffY = new QCheckBox(TreeViewer);
        chkDiffY->setObjectName(QString::fromUtf8("chkDiffY"));
        chkDiffY->setEnabled(false);

        horizontalLayout_13->addWidget(chkDiffY);

        chkRefY = new QCheckBox(TreeViewer);
        chkRefY->setObjectName(QString::fromUtf8("chkRefY"));
        chkRefY->setEnabled(false);

        horizontalLayout_13->addWidget(chkRefY);


        yLayout->addLayout(horizontalLayout_13);


        horizontalLayout_11->addLayout(yLayout);

        line_2 = new QFrame(TreeViewer);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_11->addWidget(line_2);

        zLayout = new QVBoxLayout();
        zLayout->setObjectName(QString::fromUtf8("zLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        lblZ = new QLabel(TreeViewer);
        lblZ->setObjectName(QString::fromUtf8("lblZ"));
        sizePolicy3.setHeightForWidth(lblZ->sizePolicy().hasHeightForWidth());
        lblZ->setSizePolicy(sizePolicy3);

        horizontalLayout_6->addWidget(lblZ);

        cmbZ = new QComboBox(TreeViewer);
        cmbZ->setObjectName(QString::fromUtf8("cmbZ"));
        cmbZ->setEnabled(true);

        horizontalLayout_6->addWidget(cmbZ);


        zLayout->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        lblZBins = new QLabel(TreeViewer);
        lblZBins->setObjectName(QString::fromUtf8("lblZBins"));
        lblZBins->setEnabled(false);

        horizontalLayout_8->addWidget(lblZBins);

        zSpinBins = new QSpinBox(TreeViewer);
        zSpinBins->setObjectName(QString::fromUtf8("zSpinBins"));
        zSpinBins->setEnabled(false);
        zSpinBins->setMinimum(-1);
        zSpinBins->setMaximum(100000);
        zSpinBins->setValue(-1);

        horizontalLayout_8->addWidget(zSpinBins);


        zLayout->addLayout(horizontalLayout_8);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        chkLogZ = new QCheckBox(TreeViewer);
        chkLogZ->setObjectName(QString::fromUtf8("chkLogZ"));

        horizontalLayout_16->addWidget(chkLogZ);

        chkDiffZ = new QCheckBox(TreeViewer);
        chkDiffZ->setObjectName(QString::fromUtf8("chkDiffZ"));
        chkDiffZ->setEnabled(false);

        horizontalLayout_16->addWidget(chkDiffZ);

        chkRefZ = new QCheckBox(TreeViewer);
        chkRefZ->setObjectName(QString::fromUtf8("chkRefZ"));
        chkRefZ->setEnabled(false);

        horizontalLayout_16->addWidget(chkRefZ);


        zLayout->addLayout(horizontalLayout_16);


        horizontalLayout_11->addLayout(zLayout);

        line_3 = new QFrame(TreeViewer);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_11->addWidget(line_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        btnDraw = new QPushButton(TreeViewer);
        btnDraw->setObjectName(QString::fromUtf8("btnDraw"));

        verticalLayout_6->addWidget(btnDraw);

        btnShowSummary = new QPushButton(TreeViewer);
        btnShowSummary->setObjectName(QString::fromUtf8("btnShowSummary"));
        btnShowSummary->setEnabled(false);

        verticalLayout_6->addWidget(btnShowSummary);


        horizontalLayout_15->addLayout(verticalLayout_6);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        cmbDrawOpt = new QComboBox(TreeViewer);
        cmbDrawOpt->setObjectName(QString::fromUtf8("cmbDrawOpt"));

        verticalLayout_8->addWidget(cmbDrawOpt);

        cmbSummaryHists = new QComboBox(TreeViewer);
        cmbSummaryHists->setObjectName(QString::fromUtf8("cmbSummaryHists"));
        cmbSummaryHists->setEnabled(false);

        verticalLayout_8->addWidget(cmbSummaryHists);


        horizontalLayout_15->addLayout(verticalLayout_8);


        verticalLayout_4->addLayout(horizontalLayout_15);


        horizontalLayout_11->addLayout(verticalLayout_4);


        horizontalLayout_12->addLayout(horizontalLayout_11);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        chkShowInvalid = new QCheckBox(TreeViewer);
        chkShowInvalid->setObjectName(QString::fromUtf8("chkShowInvalid"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(chkShowInvalid->sizePolicy().hasHeightForWidth());
        chkShowInvalid->setSizePolicy(sizePolicy5);

        verticalLayout_11->addWidget(chkShowInvalid);

        btnPrintToFile = new QPushButton(TreeViewer);
        btnPrintToFile->setObjectName(QString::fromUtf8("btnPrintToFile"));
        btnPrintToFile->setEnabled(false);
        sizePolicy5.setHeightForWidth(btnPrintToFile->sizePolicy().hasHeightForWidth());
        btnPrintToFile->setSizePolicy(sizePolicy5);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../../../../../../opt/cmssw/shifter/avartak/qtRoot/NewCommissioningGui/Development/NewCommissioner/images/Save-as-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPrintToFile->setIcon(icon);

        verticalLayout_11->addWidget(btnPrintToFile);


        horizontalLayout_9->addLayout(verticalLayout_11);


        verticalLayout_7->addLayout(horizontalLayout_9);


        horizontalLayout_12->addLayout(verticalLayout_7);

        line_7 = new QFrame(TreeViewer);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        horizontalLayout_12->addWidget(line_7);


        verticalLayout_5->addLayout(horizontalLayout_12);


        gridLayout_2->addLayout(verticalLayout_5, 0, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        lblX->setBuddy(cmbX);
        lblY->setBuddy(cmbY);
        lblZ->setBuddy(cmbZ);
#endif // QT_NO_SHORTCUT

        retranslateUi(TreeViewer);

        QMetaObject::connectSlotsByName(TreeViewer);
    } // setupUi

    void retranslateUi(QConnectedTabWidget *TreeViewer)
    {
        TreeViewer->setWindowTitle(QApplication::translate("TreeViewer", "Tree Viewer", 0, QApplication::UnicodeUTF8));
        chkSelMode->setText(QApplication::translate("TreeViewer", "Selection Mode", 0, QApplication::UnicodeUTF8));
        btnGetSelected->setText(QApplication::translate("TreeViewer", "Get Selected", 0, QApplication::UnicodeUTF8));
        btnDBUpload->setText(QApplication::translate("TreeViewer", "Run Info", 0, QApplication::UnicodeUTF8));
        lblInfo->setText(QString());
        btnRef->setText(QApplication::translate("TreeViewer", "Add Reference ", 0, QApplication::UnicodeUTF8));
        lblCut->setText(QApplication::translate("TreeViewer", "Cut :", 0, QApplication::UnicodeUTF8));
        btnTkMap->setText(QApplication::translate("TreeViewer", "Tk Map", 0, QApplication::UnicodeUTF8));
        btnFedMap->setText(QApplication::translate("TreeViewer", "FED Map", 0, QApplication::UnicodeUTF8));
        lblX->setText(QApplication::translate("TreeViewer", "X", 0, QApplication::UnicodeUTF8));
        lblXBins->setText(QApplication::translate("TreeViewer", "X bins", 0, QApplication::UnicodeUTF8));
        chkLogX->setText(QApplication::translate("TreeViewer", "Log X", 0, QApplication::UnicodeUTF8));
        chkDiffX->setText(QApplication::translate("TreeViewer", "Diff X", 0, QApplication::UnicodeUTF8));
        chkRefX->setText(QApplication::translate("TreeViewer", "Use Ref X", 0, QApplication::UnicodeUTF8));
        lblY->setText(QApplication::translate("TreeViewer", "Y", 0, QApplication::UnicodeUTF8));
        lblYBins->setText(QApplication::translate("TreeViewer", "Y bins", 0, QApplication::UnicodeUTF8));
        chkLogY->setText(QApplication::translate("TreeViewer", "Log Y", 0, QApplication::UnicodeUTF8));
        chkDiffY->setText(QApplication::translate("TreeViewer", "Diff Y", 0, QApplication::UnicodeUTF8));
        chkRefY->setText(QApplication::translate("TreeViewer", "Use Ref Y", 0, QApplication::UnicodeUTF8));
        lblZ->setText(QApplication::translate("TreeViewer", "Z", 0, QApplication::UnicodeUTF8));
        lblZBins->setText(QApplication::translate("TreeViewer", "Z bins", 0, QApplication::UnicodeUTF8));
        chkLogZ->setText(QApplication::translate("TreeViewer", "Log Z", 0, QApplication::UnicodeUTF8));
        chkDiffZ->setText(QApplication::translate("TreeViewer", "Diff Z", 0, QApplication::UnicodeUTF8));
        chkRefZ->setText(QApplication::translate("TreeViewer", "Use Ref Z", 0, QApplication::UnicodeUTF8));
        btnDraw->setText(QApplication::translate("TreeViewer", "Draw", 0, QApplication::UnicodeUTF8));
        btnShowSummary->setText(QApplication::translate("TreeViewer", "Summary", 0, QApplication::UnicodeUTF8));
        chkShowInvalid->setText(QApplication::translate("TreeViewer", "Show Invalid", 0, QApplication::UnicodeUTF8));
        btnPrintToFile->setText(QApplication::translate("TreeViewer", "Print", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TreeViewer: public Ui_TreeViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTREEVIEWER_H
