#include "frmdetails.h"
//#include "frmtrends.h"
#include <QDate>
#include <QTime>
#include <QStandardItem>
#include <QModelIndex>
#include <QList>
#include <QStringList>
#include <QDateTime>
#include <TBranch.h>
#include <TLeaf.h>
#include <TGraph.h>
#include <sstream>
#include <iostream>
#include <utility>

SelectionDetails::SelectionDetails(QWidget* p): 
    QConnectedTabWidget(p)
{
    setupUi(this);

    btnSelectTagged->setVisible(false);    
    btnUnselectTagged->setVisible(false);
    btnShowTaggedSelected->setVisible(false);
    btnShowTaggedAll->setVisible(false);
    btnShowAllSelected->setVisible(false);

    btnShowSummary->setVisible(false);
    btnShowTrend->setVisible(false);
    btnTagSelected->setVisible(false);
    cmbTagList->setVisible(false);
    btnAddTag->setVisible(false);
}

SelectionDetails::~SelectionDetails() {
}

void SelectionDetails::populate(TTree* tree, TEventList* eventList) {
    if (!tree || !eventList) return;

    eventList->Sort();

    fillMaps(tree);
    
    selModel = new QStandardItemModel(0, branchmap.size(), this);
    listSelection->setModel(selModel);
    listSelection->setSortingEnabled(true);
    selModel = selModel;

    QStringList headerLabels;
    for (std::map<QString, UInt_t>::iterator it = uintmap.begin(); it != uintmap.end(); ++it) headerLabels << it->first;
    for (std::map<QString, Int_t>::iterator it = intmap.begin(); it != intmap.end(); ++it) headerLabels << it->first;
    for (std::map<QString, Float_t>::iterator it = floatmap.begin(); it != floatmap.end(); ++it) headerLabels << it->first;
    for (std::map<QString, Double_t>::iterator it = doublemap.begin(); it != doublemap.end(); ++it) headerLabels << it->first;
    selModel->setHorizontalHeaderLabels(headerLabels);

    for(int i = 0; i < eventList->GetN(); i++) {
        QList<QStandardItem*> list;
        for (std::map<QString, TBranch*>::iterator it = branchmap.begin(); it != branchmap.end(); ++it) it->second->GetEvent(eventList->GetEntry(i));

        for (std::map<QString, UInt_t>::iterator it = uintmap.begin(); it != uintmap.end(); ++it) {
            QStandardItem* qsitem = new QStandardItem(QString::number(it->second, 'g', 10));
            list.append(qsitem);
        }
        for (std::map<QString, Int_t>::iterator it = intmap.begin(); it != intmap.end(); ++it) {
            QStandardItem* qsitem = new QStandardItem(QString::number(it->second, 'g', 10));
            list.append(qsitem);
        }
        for (std::map<QString, Float_t>::iterator it = floatmap.begin(); it != floatmap.end(); ++it) {
            QStandardItem* qsitem = new QStandardItem(QString::number(it->second, 'g', 10));
            list.append(qsitem);
        }
        for (std::map<QString, Double_t>::iterator it = doublemap.begin(); it != doublemap.end(); ++it) {
            QStandardItem* qsitem = new QStandardItem(QString::number(it->second, 'g', 10));
            list.append(qsitem);
        }

        if (list.size() > 0) list.at(0)->setCheckable(true);
        selModel->appendRow(list);
    }

    listSelection->expandAll();
    for (int i = 0; i < 3; i++) listSelection->resizeColumnToContents(i);
    listSelection->collapseAll();

    for (std::map<QString, TBranch*>::iterator it = branchmap.begin(); it != branchmap.end(); ++it) it->second->ResetAddress();
}

void SelectionDetails::on_btnSelectAll_clicked() {
    for (int i = 0; i < selModel->rowCount(); i++) {
        if (!listSelection->isRowHidden(i, QModelIndex())) selModel->item(i, 0)->setCheckState(Qt::Checked);
    }
}

void SelectionDetails::on_btnUnselectAll_clicked() {
    for (int i = 0; i < selModel->rowCount(); i++) {
        if (!listSelection->isRowHidden(i, QModelIndex())) selModel->item(i, 0)->setCheckState(Qt::Unchecked);
    }
}

void SelectionDetails::fillMaps(TTree* tree) {
    TObjArray* branchList = tree->GetListOfBranches();
    for(Int_t i = 0; i < branchList->GetEntries(); ++i ) {
        TBranch *branch = static_cast<TBranch*>(branchList->At(i));
        if (!branch || !branch->GetLeaf(branch->GetName())) continue;
        QString branchName(branch->GetName());
        QString typeName(branch->GetLeaf(branch->GetName())->GetTypeName());

        if (typeName == "UInt_t" || typeName == "unsigned" || typeName == "unsigned int") {
            //std::cout << branch->GetName() << " : " << qPrintable(typeName) << std::endl; 
            uintmap[branch->GetName()] = 0;
            branchmap[branch->GetName()] = branch;
            branch->SetAddress(&(uintmap[branch->GetName()]));
        }
        if (typeName == "Int_t" || typeName == "int") {
            //std::cout << branch->GetName() << " : " << qPrintable(typeName) << std::endl; 
            intmap[branch->GetName()] = 0;
            branchmap[branch->GetName()] = branch;
            branch->SetAddress(&(intmap[branch->GetName()]));
        }            
        if (typeName == "Float_t" || typeName == "float") {
            //std::cout << branch->GetName() << " : " << qPrintable(typeName) << std::endl; 
            floatmap[branch->GetName()] = 0.0;
            branchmap[branch->GetName()] = branch;
            branch->SetAddress(&(floatmap[branch->GetName()]));
        }
        if (typeName == "Double_t" || typeName == "double") {
            //std::cout << branch->GetName() << " : " << qPrintable(typeName) << std::endl; 
            doublemap[branch->GetName()] = 0.0;
            branchmap[branch->GetName()] = branch;
            branch->SetAddress(&(doublemap[branch->GetName()]));
        }
    }

}
