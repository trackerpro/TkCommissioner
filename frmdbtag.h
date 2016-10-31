#ifndef TAGCREATOR_H
#define TAGCREATOR_H

// Qt includes
#include <QValidator> 
#include <QRegExpValidator> 
#include <QRegExp> 
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QtSql/QSqlQuery>

// Debug output
#include "Debug.h"
#include "DbConnection.h"

// UI file
#include "ui_frmdbtag.h"

class TagCreator : public QDialog, private Ui::TagCreator {

    Q_OBJECT
 
    public:
        TagCreator(QWidget *parent = 0) {
            Q_UNUSED(parent);

            setupUi(this); 

            btnBox->button( QDialogButtonBox::Ok )->setEnabled(false);
            
            QRegExp rx( "^[a-z0-9\\s]{1,99}$" );
            rx.setCaseSensitivity(Qt::CaseInsensitive);
            QValidator* validator = new QRegExpValidator( rx, this );
            tagLine->setValidator( validator );

            connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));
            connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));
        }

        ~TagCreator() {
        }

    public Q_SLOTS:
        void on_tagLine_textChanged(const QString &) {
            QString t = tagLine->text();
            int p = 0;
            bool on = (tagLine->validator()->validate(t, p) == QValidator::Acceptable);
            btnBox->button( QDialogButtonBox::Ok )->setEnabled(on);
        }

        void accept() {
            if (Debug::Inst()->getEnabled()) qDebug() << "Creating new DB Tag";

            QString squery;
            QTextStream myQuery(&squery);
            myQuery << "BEGIN PkgTkAnalysisLog.addTagDescription('" << tagLine->text() << "'); END;";

            QSqlQuery query;
            query.prepare(squery);
            query.exec();
        }

        void reject() {
            done(0);
        }

};
#endif
