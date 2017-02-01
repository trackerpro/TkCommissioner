#ifndef FRMBASICTREEVIEWER_H
#define FRMBASICTREEVIEWER_H
 
#include "ui_frmtreeviewer.h"
#include "TreeBuilder.h"

#include <map>
#include <utility>
#include <vector>

#include <TH1F.h>
#include <TTree.h>
#include <TFile.h>
#include <TCutG.h>
#include <TEventList.h>

#include <QString>

namespace Const {
    static const QString none = "(NONE)";
    static const unsigned int _1D=1,_2D=2,_3D=3;
    static const unsigned int _dimX=1,_dimY=2,_dimZ=3;
    typedef unsigned int Dimension;
}
 
using namespace Const;

class TreeViewer : public QConnectedTabWidget, private Ui::TreeViewer {

    Q_OBJECT
 
    public:
        TreeViewer(QWidget *parent = 0);
        ~TreeViewer();
        TCanvas *getCanvas();
        //bool setTree(const QString&, const QString&, const QString&, const QString&, const QString&);
        bool setTree(const QString&, std::vector<QPair<QString, QString> >);

    public Q_SLOTS:
        void catchSelect(QPoint, QPoint);
        void catchZoomout();
        void on_btnDraw_clicked();
        void on_btnPrintToFile_clicked();
        void on_btnGetSelected_clicked();
        void on_btnTkMap_clicked();
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
    protected:
        virtual void closeEvent(QCloseEvent* event);
    
    private:
        void freeTrees();
        void fillBranchNames(bool, unsigned int);
        void varChanged(const QString& text, QString& var, int& bins, QSpinBox *box, QLabel *label, unsigned int);
        void setDrawOptions(Dimension d);
        void draw(bool, bool);
        void update();
        QString getDimString(unsigned int);
        QString getDrawString(QString, unsigned int bins = 0, double min = 0., double max = 0.);
        QString setText(const QString& text, unsigned int);

        TreeBuilder treebuilder;
        int xBins,yBins,zBins;
        std::vector<int> selMap;
        std::vector<QPair<QString, QString> > varList, refVarList;
        QString X, Y, Z;
        QString curX, curY, curZ, curDrawX, curDrawY, curDrawZ;
        bool curRefX, curRefY, curRefZ, curDiffX, curDiffY, curDiffZ;
        QString drawOpt, cutString;
        double xboundmin, xboundmax, yboundmin, yboundmax;
};
#endif
