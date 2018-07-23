/********************************************************************************
** Form generated from reading UI file 'frmdbtag.ui'
**
** Created: Tue May 8 15:28:16 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMDBTAG_H
#define UI_FRMDBTAG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_TagCreator
{
public:
    QDialogButtonBox *btnBox;
    QLineEdit *tagLine;

    void setupUi(QDialog *TagCreator)
    {
        if (TagCreator->objectName().isEmpty())
            TagCreator->setObjectName(QString::fromUtf8("TagCreator"));
        TagCreator->resize(400, 125);
        btnBox = new QDialogButtonBox(TagCreator);
        btnBox->setObjectName(QString::fromUtf8("btnBox"));
        btnBox->setGeometry(QRect(40, 80, 341, 32));
        btnBox->setOrientation(Qt::Horizontal);
        btnBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tagLine = new QLineEdit(TagCreator);
        tagLine->setObjectName(QString::fromUtf8("tagLine"));
        tagLine->setGeometry(QRect(20, 30, 361, 21));

        retranslateUi(TagCreator);

        QMetaObject::connectSlotsByName(TagCreator);
    } // setupUi

    void retranslateUi(QDialog *TagCreator)
    {
        TagCreator->setWindowTitle(QApplication::translate("TagCreator", "Create DB Tag", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TagCreator: public Ui_TagCreator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMDBTAG_H
