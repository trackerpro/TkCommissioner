#ifndef FRMRUNINFO_H
#define FRMRUNINFO_H
 
#include "ui_frmruninfo.h"

#include <QString>

class RunInfo : public QConnectedTabWidget, private Ui::RunInfo {

    Q_OBJECT
 
    public:
        RunInfo(QWidget *parent = 0);
        ~RunInfo();

        void setCurrentRun(QString);
        QString getCurrentRun();
        void displayRunInfo();

    private:
        QString currentRun; 

};
#endif
