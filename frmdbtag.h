#ifndef TAGCREATOR_H
#define TAGCREATOR_H

// Qt includes
#include <QValidator> 
#include <QRegExpValidator> 
#include <QRegExp> 
#include <QMessageBox>
#include <QTextStream>
#include <QString>

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

            btnOk->setEnabled(false);
            
            QRegExp rx( "^[a-z0-9\\s]{1,99}$" );
            rx.setCaseSensitivity(Qt::CaseInsensitive);
            QValidator* validator = new QRegExpValidator( rx, this );
            tagLine->setValidator( validator );
        }

        ~TagCreator() {
        }

    public Q_SLOTS:
        void on_btnOk_clicked() {
            if (Debug::Inst()->getEnabled()) qDebug() << "Creating new DB Tag";

            QString squery;
            QTextStream myQuery(&squery);
            myQuery << "BEGIN PkgTkAnalysisLog.addTagDescription('" << tagLine->text() << "'); END;";

            /*
            QSqlQuery query;
            query.prepare(squery);
            query.exec();
            */

            qDebug() << squery;    
        }

        void on_btnCancel_clicked() {
            done(0);
        }

        void on_tagLine_textChanged(const QString &) {
            QString t = tagLine->text();
            int p = 0;
            bool on = (tagLine->validator()->validate(t, p) == QValidator::Acceptable);
            btnOk->setEnabled(on);
        }

};
#endif
