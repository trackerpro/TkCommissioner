#ifndef FRMDBUPLOAD_H
#define FRMDBUPLOAD_H
 
#include "ui_frmdbupload.h"

#include <QString>
#include <QVector>
#include <QMap>
#include <QStandardItemModel>
#include <TTree.h>
#include <sstream>

class DBUpload : public QConnectedTabWidget, private Ui::DBUpload {

    Q_OBJECT
 
    public:
        DBUpload(QWidget *parent = 0);
        ~DBUpload();

        typedef QPair<QString,QString> QRunId; /**< unique ID of a run consisting of partition name and run number */

        void setCurrentRun(const QString&);
        void setCurrentPartition(const QString&);
        void setTree(TTree*);
        void setSelMap(QVector<int>);
        QString getCurrentRun();
        QString getCurrentPartition();
        bool displayRunInfo();

    private:
        QStandardItemModel* skipModel;
        QString currentRun; 
        QString currentPartition; 
        QString analysisType; 
        QString selLevel;
        TTree* tree;            
        QVector<int> selMap;
        QMap<unsigned, unsigned> selLevelMap;
        QMap<unsigned, unsigned> unselLevelMap;
        QMap<unsigned, unsigned> addLevelMap;

        std::stringstream infoss;
        std::stringstream partss;            
        std::stringstream skipss;            

        bool fillSkipList();

    public Q_SLOTS:
        void on_radAll_toggled(bool);
        void on_radFed_toggled(bool);
        void on_radFec_toggled(bool);
        void on_radRing_toggled(bool);
        void on_radCcu_toggled(bool);
        void on_radCcuChan_toggled(bool);
        void on_btnUpload_clicked();
        void on_btnAddSkip_clicked();

        void channelCheckChanged(QStandardItem*);
        void addSkipChannel(QPair<unsigned, unsigned>);
};
#endif
