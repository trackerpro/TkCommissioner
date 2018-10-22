/********************************************************************************
** Form generated from reading UI file 'frmaddskip.ui'
**
** Created: Mon Oct 22 16:28:21 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMADDSKIP_H
#define UI_FRMADDSKIP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddSkipChannel
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *lblFed;
    QLabel *lblFec;
    QLabel *lblRing;
    QLabel *lblCcu;
    QLabel *lblCcuChan;
    QLineEdit *lineFed;
    QLineEdit *lineFec;
    QLineEdit *lineCcu;
    QLineEdit *lineCcuChan;
    QLineEdit *lineRing;
    QLabel *lblLLDChan;
    QLineEdit *lineLLDChan;
    QLabel *lblCrate;
    QLineEdit *lineCrate;

    void setupUi(QDialog *AddSkipChannel)
    {
        if (AddSkipChannel->objectName().isEmpty())
            AddSkipChannel->setObjectName(QString::fromUtf8("AddSkipChannel"));
        AddSkipChannel->resize(279, 300);
        buttonBox = new QDialogButtonBox(AddSkipChannel);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(-10, 260, 281, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        gridLayoutWidget = new QWidget(AddSkipChannel);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 261, 241));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lblFed = new QLabel(gridLayoutWidget);
        lblFed->setObjectName(QString::fromUtf8("lblFed"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblFed->sizePolicy().hasHeightForWidth());
        lblFed->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        lblFed->setFont(font);

        gridLayout->addWidget(lblFed, 1, 0, 1, 1);

        lblFec = new QLabel(gridLayoutWidget);
        lblFec->setObjectName(QString::fromUtf8("lblFec"));
        sizePolicy.setHeightForWidth(lblFec->sizePolicy().hasHeightForWidth());
        lblFec->setSizePolicy(sizePolicy);
        lblFec->setFont(font);

        gridLayout->addWidget(lblFec, 4, 0, 1, 1);

        lblRing = new QLabel(gridLayoutWidget);
        lblRing->setObjectName(QString::fromUtf8("lblRing"));
        sizePolicy.setHeightForWidth(lblRing->sizePolicy().hasHeightForWidth());
        lblRing->setSizePolicy(sizePolicy);
        lblRing->setFont(font);

        gridLayout->addWidget(lblRing, 5, 0, 1, 1);

        lblCcu = new QLabel(gridLayoutWidget);
        lblCcu->setObjectName(QString::fromUtf8("lblCcu"));
        sizePolicy.setHeightForWidth(lblCcu->sizePolicy().hasHeightForWidth());
        lblCcu->setSizePolicy(sizePolicy);
        lblCcu->setFont(font);

        gridLayout->addWidget(lblCcu, 6, 0, 1, 1);

        lblCcuChan = new QLabel(gridLayoutWidget);
        lblCcuChan->setObjectName(QString::fromUtf8("lblCcuChan"));
        sizePolicy.setHeightForWidth(lblCcuChan->sizePolicy().hasHeightForWidth());
        lblCcuChan->setSizePolicy(sizePolicy);
        lblCcuChan->setFont(font);

        gridLayout->addWidget(lblCcuChan, 7, 0, 1, 1);

        lineFed = new QLineEdit(gridLayoutWidget);
        lineFed->setObjectName(QString::fromUtf8("lineFed"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineFed->sizePolicy().hasHeightForWidth());
        lineFed->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineFed, 1, 1, 1, 1);

        lineFec = new QLineEdit(gridLayoutWidget);
        lineFec->setObjectName(QString::fromUtf8("lineFec"));
        sizePolicy1.setHeightForWidth(lineFec->sizePolicy().hasHeightForWidth());
        lineFec->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineFec, 4, 1, 1, 1);

        lineCcu = new QLineEdit(gridLayoutWidget);
        lineCcu->setObjectName(QString::fromUtf8("lineCcu"));
        sizePolicy1.setHeightForWidth(lineCcu->sizePolicy().hasHeightForWidth());
        lineCcu->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineCcu, 6, 1, 1, 1);

        lineCcuChan = new QLineEdit(gridLayoutWidget);
        lineCcuChan->setObjectName(QString::fromUtf8("lineCcuChan"));
        sizePolicy1.setHeightForWidth(lineCcuChan->sizePolicy().hasHeightForWidth());
        lineCcuChan->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineCcuChan, 7, 1, 1, 1);

        lineRing = new QLineEdit(gridLayoutWidget);
        lineRing->setObjectName(QString::fromUtf8("lineRing"));
        sizePolicy1.setHeightForWidth(lineRing->sizePolicy().hasHeightForWidth());
        lineRing->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineRing, 5, 1, 1, 1);

        lblLLDChan = new QLabel(gridLayoutWidget);
        lblLLDChan->setObjectName(QString::fromUtf8("lblLLDChan"));
        lblLLDChan->setFont(font);

        gridLayout->addWidget(lblLLDChan, 8, 0, 1, 1);

        lineLLDChan = new QLineEdit(gridLayoutWidget);
        lineLLDChan->setObjectName(QString::fromUtf8("lineLLDChan"));
        sizePolicy1.setHeightForWidth(lineLLDChan->sizePolicy().hasHeightForWidth());
        lineLLDChan->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineLLDChan, 8, 1, 1, 1);

        lblCrate = new QLabel(gridLayoutWidget);
        lblCrate->setObjectName(QString::fromUtf8("lblCrate"));
        lblCrate->setFont(font);

        gridLayout->addWidget(lblCrate, 3, 0, 1, 1);

        lineCrate = new QLineEdit(gridLayoutWidget);
        lineCrate->setObjectName(QString::fromUtf8("lineCrate"));
        sizePolicy1.setHeightForWidth(lineCrate->sizePolicy().hasHeightForWidth());
        lineCrate->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineCrate, 3, 1, 1, 1);


        retranslateUi(AddSkipChannel);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddSkipChannel, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddSkipChannel, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddSkipChannel);
    } // setupUi

    void retranslateUi(QDialog *AddSkipChannel)
    {
        AddSkipChannel->setWindowTitle(QApplication::translate("AddSkipChannel", "Add Skip Channel", 0, QApplication::UnicodeUTF8));
        lblFed->setText(QApplication::translate("AddSkipChannel", "FED", 0, QApplication::UnicodeUTF8));
        lblFec->setText(QApplication::translate("AddSkipChannel", "FEC Slot", 0, QApplication::UnicodeUTF8));
        lblRing->setText(QApplication::translate("AddSkipChannel", "Ring", 0, QApplication::UnicodeUTF8));
        lblCcu->setText(QApplication::translate("AddSkipChannel", "CCU", 0, QApplication::UnicodeUTF8));
        lblCcuChan->setText(QApplication::translate("AddSkipChannel", "CCU Channel", 0, QApplication::UnicodeUTF8));
        lblLLDChan->setText(QApplication::translate("AddSkipChannel", "LLD Channel", 0, QApplication::UnicodeUTF8));
        lblCrate->setText(QApplication::translate("AddSkipChannel", "FEC Crate", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddSkipChannel: public Ui_AddSkipChannel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMADDSKIP_H
