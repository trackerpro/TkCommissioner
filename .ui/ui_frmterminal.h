/********************************************************************************
** Form generated from reading UI file 'frmterminal.ui'
**
** Created: Tue May 8 15:28:16 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTERMINAL_H
#define UI_FRMTERMINAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include "QConnectedTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_TkTerminal
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTextEdit *textOutput;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnKill;
    QSpacerItem *horizontalSpacer;

    void setupUi(QConnectedTabWidget *TkTerminal)
    {
        if (TkTerminal->objectName().isEmpty())
            TkTerminal->setObjectName(QString::fromUtf8("TkTerminal"));
        TkTerminal->resize(1042, 686);
        gridLayout = new QGridLayout(TkTerminal);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textOutput = new QTextEdit(TkTerminal);
        textOutput->setObjectName(QString::fromUtf8("textOutput"));
        QPalette palette;
        QBrush brush(QColor(0, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        QBrush brush2(QColor(106, 104, 100, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        QBrush brush3(QColor(212, 208, 200, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        textOutput->setPalette(palette);
        textOutput->setReadOnly(true);

        verticalLayout->addWidget(textOutput);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnKill = new QPushButton(TkTerminal);
        btnKill->setObjectName(QString::fromUtf8("btnKill"));

        horizontalLayout->addWidget(btnKill);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(TkTerminal);

        QMetaObject::connectSlotsByName(TkTerminal);
    } // setupUi

    void retranslateUi(QConnectedTabWidget *TkTerminal)
    {
        TkTerminal->setWindowTitle(QApplication::translate("TkTerminal", "Running analysis", 0, QApplication::UnicodeUTF8));
        btnKill->setText(QApplication::translate("TkTerminal", "Kill the analysis!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TkTerminal: public Ui_TkTerminal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTERMINAL_H
