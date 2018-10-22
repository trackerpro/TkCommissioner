/********************************************************************************
** Form generated from reading UI file 'frmcommissioner.ui'
**
** Created: Mon Oct 22 16:28:21 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCOMMISSIONER_H
#define UI_FRMCOMMISSIONER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QTabWidget>

QT_BEGIN_NAMESPACE

class Ui_Commissioner
{
public:
    QTabWidget *tabController;

    void setupUi(QMainWindow *Commissioner)
    {
        if (Commissioner->objectName().isEmpty())
            Commissioner->setObjectName(QString::fromUtf8("Commissioner"));
        Commissioner->resize(1051, 741);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Commissioner->sizePolicy().hasHeightForWidth());
        Commissioner->setSizePolicy(sizePolicy);
        tabController = new QTabWidget(Commissioner);
        tabController->setObjectName(QString::fromUtf8("tabController"));
        tabController->setTabsClosable(true);
        Commissioner->setCentralWidget(tabController);

        retranslateUi(Commissioner);

        tabController->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Commissioner);
    } // setupUi

    void retranslateUi(QMainWindow *Commissioner)
    {
        Commissioner->setWindowTitle(QApplication::translate("Commissioner", "Tk Commissioner", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Commissioner: public Ui_Commissioner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCOMMISSIONER_H
