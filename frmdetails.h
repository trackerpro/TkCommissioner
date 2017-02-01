#ifndef FRMBASICDETAILS_H
#define FRMBASICDETAILS_H
 
#include "ui_frmdetails.h"

#include <QStandardItemModel>
#include <QString>
#include <QPair>
#include <TTree.h>
#include <TEventList.h>
#include <vector>
#include <map>

class SelectionDetails : public QConnectedTabWidget, private Ui::SelectionDetails {

    Q_OBJECT
 
    public:
        SelectionDetails(QWidget *parent = 0);
        ~SelectionDetails();

        void populate(TTree*, TEventList*);
        void fillMaps(TTree*);

    public Q_SLOTS:
        void on_btnSelectAll_clicked();
        void on_btnUnselectAll_clicked();
    
    private:
        QStandardItemModel* selModel;

        std::map<QString, UInt_t> uintmap;
        std::map<QString, Int_t> intmap;
        std::map<QString, Float_t> floatmap;
        std::map<QString, Double_t> doublemap;
        std::map<QString, TBranch*> branchmap;

};
#endif
