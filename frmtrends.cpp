#include "frmtrends.h"
#include <TStyle.h>
#include <TDatime.h>
#include <TAxis.h>
#include <TColor.h>
#include <TROOT.h>
#include <TMath.h>
#include <QList>
#include <QStandardItem>
#include <QPixmap>
#include <QColor>
#include <iostream>


void Trends::nextColor( int &color ) {
    color++;
    if( color == 5 ) color++;
    if( color == 7 ) color++;
    if( color == 10 ) color = 40;
    if( color == 50 ) color = kRed - 10;
    if( color == kRed ) color = kCyan - 10;
    if( color == kCyan ) color = kGreen - 10;
    if( color == kGreen ) color = kOrange - 9;
}


Trends::Trends(QWidget* p): 
    QConnectedTabWidget(p)
{
    setupUi(this);

    selModel = new QStandardItemModel(0, 2,this);
    selView->setModel(selModel);
    selView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    
    connect(selView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(focusChanged(QModelIndex,QModelIndex)));
    connect(selModel,SIGNAL(itemChanged(QStandardItem*)),SLOT(updateGraphs(QStandardItem*)));
}

Trends::~Trends() {
}

void Trends::getSelectionInfo(std::map<std::pair<QString, QString>, TGraph*> graphMap) {
    int counter = 0;
    TDatime da(2000, 1, 1, 0, 0, 0);
    gStyle->SetTimeOffset(da.Convert());
    for (std::map<std::pair<QString, QString>, TGraph*>::iterator iter = graphMap.begin(); iter != graphMap.end(); iter++) {
        nextColor(counter);
        QList<QStandardItem*> list;
        QStandardItem* detid = new QStandardItem((iter->first).first);
        QStandardItem* i2cad = new QStandardItem((iter->first).second);
        detid->setCheckable(true);
        detid->setCheckState(Qt::Checked);
        TColor* fontcolor = gROOT->GetColor(counter);
        QPixmap pixmap(100,100);
        pixmap.fill(QColor(int(fontcolor->GetRed()*255), int(fontcolor->GetGreen()*255), int(fontcolor->GetBlue()*255)));
        i2cad->setIcon(QIcon(pixmap));
        list.append(detid);
        list.append(i2cad);
        selModel->appendRow(list);
        qtCanvas->GetCanvas()->cd();
        graphs.push_back(iter->second);
        iter->second->SetLineColor(counter);
        iter->second->SetEditable(kFALSE);
        iter->second->GetXaxis()->SetTimeDisplay(1);
        iter->second->GetXaxis()->SetTimeFormat("%d-%m-%y");
        iter->second->GetXaxis()->SetNdivisions(4);
        iter->second->SetLineWidth(1);
        if (iter ==  graphMap.begin()) iter->second->Draw("AL");
        else iter->second->Draw("L SAME");
    }
    
    selModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Detid"));
    selModel->setHeaderData(1, Qt::Horizontal, QObject::tr("I2CAddress"));
    selView->selectRow(0);
}

void Trends::focusChanged(QModelIndex current, QModelIndex) {
    if (selModel->item(current.row(), 0)->checkState() != Qt::Checked) return;

    graphs[current.row()]->SetLineWidth(2);

    for (std::size_t i = 0; i < graphs.size(); i++) {
        if (int(i) != current.row()) graphs[i]->SetLineWidth(1);
    }

    drawGraphs();
}

void Trends::drawGraphs() {
    double ymax = 0.0;
    double ymin = 0.0;

    for (std::size_t i = 0; i < graphs.size(); i++) {
        double grmax = TMath::MaxElement(graphs[i]->GetN(), graphs[i]->GetY());
        double grmin = TMath::MinElement(graphs[i]->GetN(), graphs[i]->GetY());
        if (grmax > ymax) ymax = grmax;
        if (grmin < ymin) ymin = grmin;
    }

    bool drawn = false;
    for (std::size_t i = 0; i < graphs.size(); i++) {
        if (selModel->item(i, 0)->checkState() == Qt::Checked) {
            if (!drawn) {
                graphs[i]->GetYaxis()->SetRangeUser(ymin*0.9, ymax*1.1);
                graphs[i]->Draw("AL");
                drawn = true;
            }
            else graphs[i]->Draw("L SAME");
        }
    }        
    for (std::size_t i = 0; i < graphs.size(); i++) {
        if (selModel->item(i, 0)->checkState() == Qt::Checked && graphs[i]->GetLineWidth() == 2) graphs[i]->Draw("L SAME");
    }        
    
    if (!drawn) qtCanvas->GetCanvas()->Clear();
    qtCanvas->GetCanvas()->Modified();
    qtCanvas->GetCanvas()->Update();
}

void Trends::updateGraphs(QStandardItem*) {
    drawGraphs();
}

