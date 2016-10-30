#ifndef TKTERMINAL_H
#define TKTERMINAL_H

// System includes
#include <signal.h>

// Qt includes 
#include <QProcess>
#include <QCloseEvent>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QByteArray>

// UI file
#include "ui_frmterminal.h"

// Debugging output
#include "Debug.h"
// Parent widget for the TkCommissioner tabs 
#include "QConnectedTabWidget.h"

class TkTerminal : public QConnectedTabWidget, private Ui::TkTerminal {

    Q_OBJECT
 
    private:
        QProcess* process;
        bool startFail;

    protected:
        void closeEvent(QCloseEvent* event) {
            if (process != NULL) delete process;
            event->accept();
        }
    
    public:
        TkTerminal(QWidget* p = 0):
            QConnectedTabWidget(p)
        {
            setupUi(this);
            btnKill->setEnabled(true);
            startFail = false;
            
            process = new QProcess( this );
              
            connect( process, SIGNAL(readyReadStandardOutput()), this, SLOT(readFromStdout()) );
            connect( process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)) );
            connect( process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)) );
        }

        ~TkTerminal() {
            if (process != NULL) delete process;
        }
       
        bool didStartFail() {
            return startFail;
        }

        void startProcess(QString command, QStringList args) {
            if (Debug::Inst()->getEnabled()) qDebug() << "Starting analysis with command:\n" << command << args;
            process->start(command, args);
        }

    public Q_SLOTS:
        void on_btnKill_clicked() {
            if (process) {
                Q_PID thisPid = process->pid();
                
                kill(thisPid, SIGINT);
                QTimer::singleShot( 2000, process, SLOT( terminate() ) );
                QTimer::singleShot( 5000, process, SLOT( kill() ) );
                
            }
            else { 
                if (Debug::Inst()->getEnabled()) qDebug() << "Error! No handle to the launched process...";
            }
        }

        void readFromStdout() {
            if (process) {
                QByteArray newChunk;
                newChunk = process->readAllStandardOutput();
                QString newTextString(newChunk);
                textOutput->setText(textOutput->toPlainText()+newTextString);
                textOutput->ensureCursorVisible();
            }
        }

        void processFinished(int, QProcess::ExitStatus exitStatus) {
            if (Debug::Inst()->getEnabled()) {
                if (exitStatus==QProcess::NormalExit) qDebug() << "Analysis process exited successfully";
                else                                  qDebug() << "Analysis process exited with error";
            }
            btnKill->setEnabled(false);
        }

        void processError(QProcess::ProcessError error) {
            if      (error == QProcess::FailedToStart) qDebug() << "The process failed to start";
            else if (error == QProcess::Crashed      ) qDebug() << "The process crashed after starting";
            else if (error == QProcess::WriteError   ) qDebug() << "Error writing to the process";
            else                                       qDebug() << "Unknown error encountered while executing the process";
            
            startFail = true;
        }

};
#endif
