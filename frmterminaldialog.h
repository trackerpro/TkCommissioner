#ifndef TKTERMINALDIALOG_H
#define TKTERMINALDIALOG_H

// System includes
#include <signal.h>

// Qt includes 
#include <QProcess>
#include <QCloseEvent>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QByteArray>
#include <QDialog>

// UI file
#include "ui_frmterminaldialog.h"

// Debugging output
#include "Debug.h"

class TkTerminalDialog : public QDialog, private Ui::TkTerminalDialog {

    Q_OBJECT
 
    private:
        QProcess* thisProcess_;
        bool correctProcess_;

    protected:
        void closeEvent(QCloseEvent* event) {
            if (thisProcess_ != NULL) delete thisProcess_;
            event->accept();
        }
    
    public:
        TkTerminalDialog(QWidget* p = 0):
            QDialog(p)
        {
            setupUi(this);
            btnDone->setEnabled(false);
            correctProcess_ = false;
	    // textOutput->setCenterOnScroll(true);
        }

        ~TkTerminalDialog() {
            if (thisProcess_ != NULL) delete thisProcess_;
        }
      
        void setProcessPtr(QProcess* newProcess) {
            thisProcess_ = newProcess;
        }

    public Q_SLOTS:

        void readFromStdout() {
            if (thisProcess_) {
                QByteArray newChunk;
                newChunk = thisProcess_->readAllStandardOutput();
                QString newTextString(newChunk);
                //textOutput->setText(textOutput->text()+newTextString);
		textOutput->append(newTextString);
		//textOutput->scrollToBottom();
		textOutput->ensureCursorVisible();
            }
        }

        void processFinished(int, QProcess::ExitStatus exitStatus) {
            if (exitStatus == QProcess::NormalExit) correctProcess_ = true;
            btnDone->setEnabled(true);
            if (correctProcess_) done(QDialog::Accepted);
        }


        void executeWaitForReadyRead() {
            thisProcess_->waitForReadyRead();
        }

 
};
#endif
