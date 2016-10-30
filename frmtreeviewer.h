#ifndef FRMTREEVIEWER_H
#define FRMTREEVIEWER_H

// ROOT includes
#include <TH1F.h>
#include <TTree.h>
#include <TFile.h>
#include <TEventList.h>

// Qt includes
#include <QVector>

// UI file
#include "ui_frmtreeviewer.h"

// Qt project includes 
#include "TreeViewerRunInfo.h"

class TreeViewer : public QConnectedTabWidget, private Ui::TreeViewer {

    Q_OBJECT
 
    public:
        typedef QPair<QString,QString> QRunId;
        
        TreeViewer(const QString& tmpfilename, bool useCache = false, QWidget *parent = 0);
        ~TreeViewer();
        bool addRun(QString, QString, bool);

    public Q_SLOTS:
        void catchRef(QString, QString, bool);
        void catchSelect(QPoint, QPoint);
        void catchZoomout();

        void on_btnDraw_clicked();
        void on_btnShowSummary_clicked();
        void on_btnPrintToFile_clicked();
        void on_btnRef_clicked();
        void on_btnRunInfo_clicked();
        void on_btnGetSelected_clicked();
        void on_btnTkMap_clicked();
        void on_btnFedMap_clicked();

        void on_cmbX_currentIndexChanged(const QString & text);
        void on_cmbY_currentIndexChanged(const QString & text);
        void on_cmbZ_currentIndexChanged(const QString & text); 

        void on_xSpinBins_valueChanged(int bins);
        void on_ySpinBins_valueChanged(int bins);
        void on_zSpinBins_valueChanged(int bins);

        void on_chkLogX_stateChanged(int state);
        void on_chkLogY_stateChanged(int state);
        void on_chkLogZ_stateChanged(int state);

        void on_chkRefX_stateChanged(int);
        void on_chkRefY_stateChanged(int);
        void on_chkRefZ_stateChanged(int);

    signals:
        

    protected:
        virtual void closeEvent(QCloseEvent* event);
    
    private:
        TCanvas *getCanvas();
        void updateCanvas();

        void fillBranchNames(bool, char);
        void fillSummaryHists(const QString&);
        void varChanged(const QString& text, QString& var, int& bins, QSpinBox *box, QLabel *label, char);
        void setDrawOptions(int d);
        void draw(bool, bool);
        QString getDimString(char);
        QString getDrawString(QString, unsigned int bins = 0, double min = 0., double max = 0.);
        QString getInvalidCutString(bool);
        QString setText(const QString& text, char);

        bool useCachedTrees;      
        bool invChecked;      
        int xBins,yBins,zBins;

        TFile* clientFile;
        QVector<TH1*> summaryHists;
        TreeViewerRunInfo treeInfo;
        QVector<int> selMap;
        QVector<QPair<QString, QString> > varList, refVarList;
        QString X, Y, Z, curX, curY, curZ, curDrawX, curDrawY, curDrawZ;
        bool curRefX, curRefY, curRefZ, curDiffX, curDiffY, curDiffZ;
        bool sameRefRunType;
        QString drawOpt, cutString;
        double xboundmin, xboundmax, yboundmin, yboundmax;
};
#endif
