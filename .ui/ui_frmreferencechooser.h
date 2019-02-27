/********************************************************************************
** Form generated from reading UI file 'frmreferencechooser.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMREFERENCECHOOSER_H
#define UI_FRMREFERENCECHOOSER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_ReferenceChooser
{
public:
    QDialogButtonBox *buttonBox;
    QTableView *refRunView;

    void setupUi(QDialog *ReferenceChooser)
    {
        if (ReferenceChooser->objectName().isEmpty())
            ReferenceChooser->setObjectName(QString::fromUtf8("ReferenceChooser"));
        ReferenceChooser->resize(452, 454);
        buttonBox = new QDialogButtonBox(ReferenceChooser);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(110, 410, 321, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        refRunView = new QTableView(ReferenceChooser);
        refRunView->setObjectName(QString::fromUtf8("refRunView"));
        refRunView->setGeometry(QRect(20, 20, 411, 371));
        refRunView->setSelectionBehavior(QAbstractItemView::SelectRows);
        refRunView->setSortingEnabled(true);

        retranslateUi(ReferenceChooser);
        QObject::connect(buttonBox, SIGNAL(accepted()), ReferenceChooser, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ReferenceChooser, SLOT(reject()));

        QMetaObject::connectSlotsByName(ReferenceChooser);
    } // setupUi

    void retranslateUi(QDialog *ReferenceChooser)
    {
        ReferenceChooser->setWindowTitle(QApplication::translate("ReferenceChooser", "Choose Reference Run", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ReferenceChooser: public Ui_ReferenceChooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMREFERENCECHOOSER_H
