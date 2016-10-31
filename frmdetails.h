#ifndef DETAILS_H
#define DETAILS_H
 
#include "ui_frmdetails.h"

#include <QStandardItemModel>
#include <QString>
#include <QVector>

#include <TTree.h>

#include "TreeViewerRunInfo.h"

class SelectionDetails : public QConnectedTabWidget, private Ui::SelectionDetails {

    Q_OBJECT
 
    public:
        SelectionDetails(QWidget*, const TreeViewerRunInfo&);
        ~SelectionDetails();

        void populate(TTree* tree, const QVector<int>& sel, const QString& varname);

    public Q_SLOTS:
        void on_btnSelectAll_clicked();
        void on_btnUnselectAll_clicked();
        void on_btnSelectTagged_clicked();
        void on_btnUnselectTagged_clicked();
        void on_btnShowTaggedSelected_clicked();
        void on_btnShowAllSelected_clicked();
        void on_btnShowTaggedAll_clicked();
        void on_btnAddTag_clicked();
        void on_btnTagSelected_clicked();
        void on_btnShowSource_clicked();
        void on_btnShowTrend_clicked();

    private:
        QStandardItemModel* selModel;
        QStandardItemModel* tagModel;
        QStandardItemModel* curModel;

        QString var;
        QString run;
        QString refrun;
};
#endif
