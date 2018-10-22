/********************************************************************************
** Form generated from reading UI file 'frmsavetags.ui'
**
** Created: Mon Oct 22 16:28:21 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSAVETAGS_H
#define UI_FRMSAVETAGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TagUpload
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *topLabel;
    QSpacerItem *spacer3;
    QPushButton *btnAddComment;
    QTableView *uploadList;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel2;
    QSpacerItem *spacer14;
    QCheckBox *confirmCheck;
    QLabel *displayTag;
    QHBoxLayout *hboxLayout2;
    QPushButton *buttonOk;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonCancel;

    void setupUi(QDialog *TagUpload)
    {
        if (TagUpload->objectName().isEmpty())
            TagUpload->setObjectName(QString::fromUtf8("TagUpload"));
        TagUpload->resize(619, 395);
        TagUpload->setSizeGripEnabled(true);
        vboxLayout = new QVBoxLayout(TagUpload);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        topLabel = new QLabel(TagUpload);
        topLabel->setObjectName(QString::fromUtf8("topLabel"));
        topLabel->setWordWrap(false);

        hboxLayout->addWidget(topLabel);

        spacer3 = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer3);

        btnAddComment = new QPushButton(TagUpload);
        btnAddComment->setObjectName(QString::fromUtf8("btnAddComment"));

        hboxLayout->addWidget(btnAddComment);


        vboxLayout->addLayout(hboxLayout);

        uploadList = new QTableView(TagUpload);
        uploadList->setObjectName(QString::fromUtf8("uploadList"));

        vboxLayout->addWidget(uploadList);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        textLabel2 = new QLabel(TagUpload);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        hboxLayout1->addWidget(textLabel2);

        spacer14 = new QSpacerItem(361, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacer14);

        confirmCheck = new QCheckBox(TagUpload);
        confirmCheck->setObjectName(QString::fromUtf8("confirmCheck"));

        hboxLayout1->addWidget(confirmCheck);


        vboxLayout->addLayout(hboxLayout1);

        displayTag = new QLabel(TagUpload);
        displayTag->setObjectName(QString::fromUtf8("displayTag"));
        displayTag->setMinimumSize(QSize(0, 30));
        displayTag->setLineWidth(4);
        displayTag->setWordWrap(false);

        vboxLayout->addWidget(displayTag);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        buttonOk = new QPushButton(TagUpload);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout2->addWidget(buttonOk);

        Horizontal_Spacing2 = new QSpacerItem(430, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(Horizontal_Spacing2);

        buttonCancel = new QPushButton(TagUpload);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        hboxLayout2->addWidget(buttonCancel);


        vboxLayout->addLayout(hboxLayout2);


        retranslateUi(TagUpload);

        QMetaObject::connectSlotsByName(TagUpload);
    } // setupUi

    void retranslateUi(QDialog *TagUpload)
    {
        TagUpload->setWindowTitle(QApplication::translate("TagUpload", "Upload to Analysis Log", 0, QApplication::UnicodeUTF8));
        topLabel->setText(QApplication::translate("TagUpload", "You want to open/update tickets for the following items in the database", 0, QApplication::UnicodeUTF8));
        btnAddComment->setText(QApplication::translate("TagUpload", "Add Comment", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("TagUpload", "with Tag", 0, QApplication::UnicodeUTF8));
        confirmCheck->setText(QApplication::translate("TagUpload", "confirm", 0, QApplication::UnicodeUTF8));
        displayTag->setText(QString());
        buttonOk->setText(QApplication::translate("TagUpload", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("TagUpload", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
    } // retranslateUi

};

namespace Ui {
    class TagUpload: public Ui_TagUpload {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSAVETAGS_H
