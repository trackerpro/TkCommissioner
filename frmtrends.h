#ifndef TRENDS_H
#define TRENDS_H
 
// UI file
#include "ui_frmtrends.h"

// Qt includes
#include <QStandardItemModel>
#include <QMap>
#include <QPair>

// ROOT includes
#include <TGraph.h>
#include <TColor.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMath.h>
#include <TAxis.h>
#include <TDatime.h>

class Trends : public QConnectedTabWidget, private Ui::Trends {

    Q_OBJECT
 
    public:
        Trends(QWidget *parent = 0):
            QConnectedTabWidget(parent)
        {
            setupUi(this);
            
            selModel = new QStandardItemModel(0, 2,this);
            selView->setModel(selModel);
            selView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
            
            connect(selModel, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(focusChanged(QModelIndex,QModelIndex)));
            connect(selModel, SIGNAL(itemChanged(QStandardItem*))               , this, SLOT(updateGraphs(QStandardItem*)));
        }
        ~Trends() {
        }

        void getSelectionInfo(QMap<QPair<QString, QString>, TGraph*> graphMap) {
            int counter = 0;
            TDatime da(2000, 1, 1, 0, 0, 0);
            gStyle->SetTimeOffset(da.Convert());
            for (QMap<QPair<QString, QString>, TGraph*>::const_iterator iter = graphMap.begin(); iter != graphMap.end(); iter++) {
                nextColor(counter);
                TColor* fontcolor = gROOT->GetColor(counter);
                QPixmap pixmap(100,100);
                pixmap.fill(QColor(int(fontcolor->GetRed()*255), int(fontcolor->GetGreen()*255), int(fontcolor->GetBlue()*255)));

                QList<QStandardItem*> list;
                QStandardItem* detid = new QStandardItem((iter.key()).first);
                QStandardItem* i2cad = new QStandardItem((iter.key()).second);
                detid->setCheckable(true);
                detid->setCheckState(Qt::Checked);
                i2cad->setIcon(QIcon(pixmap));
                list.append(detid);
                list.append(i2cad);
                selModel->appendRow(list);

                qtCanvas->GetCanvas()->cd();
                graphs.push_back(iter.value());
                iter.value()->SetLineColor(counter);
                iter.value()->SetEditable(kFALSE);
                iter.value()->GetXaxis()->SetTimeDisplay(1);
                iter.value()->GetXaxis()->SetTimeFormat("%d-%m-%y");
                iter.value()->GetXaxis()->SetNdivisions(4);
                iter.value()->SetLineWidth(1);
                if (iter ==  graphMap.begin()) iter.value()->Draw("AL");
                else iter.value()->Draw("L SAME");
            }
    
            selModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Detid"));
            selModel->setHeaderData(1, Qt::Horizontal, QObject::tr("I2CAddress"));
            selView->selectRow(0);
        }

    public Q_SLOTS:
        void focusChanged(QModelIndex current, QModelIndex) {
            if (selModel->item(current.row(), 0)->checkState() != Qt::Checked) return;
            for (int i = 0; i < graphs.size(); i++) graphs[i]->SetLineWidth(1);
            graphs[current.row()]->SetLineWidth(2);
            drawGraphs();
        }

        void updateGraphs(QStandardItem*) {
            drawGraphs();
        }

    private:
        QStandardItemModel* selModel;
        QVector<TGraph*> graphs;

        void nextColor(int& color) {
            color++;
            if ( color == 5     ) color++;
            if ( color == 7     ) color++;
            if ( color == 10    ) color = 40;
            if ( color == 50    ) color = kRed - 10;
            if ( color == kRed  ) color = kCyan - 10;
            if ( color == kCyan ) color = kGreen - 10;
            if ( color == kGreen) color = kOrange - 9;
        }

        void drawGraphs() {
            double ymax = 0.0;
            double ymin = 0.0;
            
            for (int i = 0; i < graphs.size(); i++) {
                double grmax = TMath::MaxElement(graphs[i]->GetN(), graphs[i]->GetY());
                double grmin = TMath::MinElement(graphs[i]->GetN(), graphs[i]->GetY());
                if (grmax > ymax) ymax = grmax;
                if (grmin < ymin) ymin = grmin;
            }
            
            bool drawn = false;
            for (int i = 0; i < graphs.size(); i++) {
                if (selModel->item(i, 0)->checkState() == Qt::Checked) {
                    if (!drawn) {
                        graphs[i]->GetYaxis()->SetRangeUser(ymin*0.9, ymax*1.1);
                        graphs[i]->Draw("AL");
                        drawn = true;
                    }
                    else graphs[i]->Draw("L SAME");
                }
            }        
            for (int i = 0; i < graphs.size(); i++) {
                if (selModel->item(i, 0)->checkState() == Qt::Checked && graphs[i]->GetLineWidth() == 2) graphs[i]->Draw("L SAME");
            }        
            
            if (!drawn) qtCanvas->GetCanvas()->Clear();
            qtCanvas->GetCanvas()->Update();
            qtCanvas->GetCanvas()->Modified();

        }
};
#endif
