#ifndef FRMRUNINFO_H
#define FRMRUNINFO_H
 
#include "ui_frmruninfo.h"

#include <QString>
#include <TTree.h>

class RunInfo : public QConnectedTabWidget, private Ui::RunInfo {

    Q_OBJECT
 
    public:
        RunInfo(QWidget *parent = 0);
        ~RunInfo();

        typedef QPair<QString,QString> QRunId; /**< unique ID of a run consisting of partition name and run number */

        void setCurrentRun(QString);
        void setCurrentPartition(QString);
        void setTree(TTree*);
        void setSelMap(QVector<int>);
        QString getCurrentRun();
        QString getCurrentPartition();
        bool displayRunInfo();

    private:
        QString currentRun; 
        QString currentPartition; 
        TTree* tree;            
        QVector<int> selMap;

};
#endif
