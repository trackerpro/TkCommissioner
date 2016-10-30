#ifndef FRMFEDMAP_H
#define FRMFEDMAP_H
 
#include "ui_frmfedmap.h"

#include <QVector>
#include <QPair>
#include <QString>
#include <QtCore>
#include <QtGui>

#include <TTree.h>

#include "FedView.h"
#include "FedGraphicsScene.h"

class FedMap : public QConnectedTabWidget, private Ui::FedMap {

    Q_OBJECT
 
    public:
        FedMap(QWidget *parent = 0);
        FedMap(const QVector<int>& smap, QPair<QString, QString> runid, TTree* tree = 0, QWidget *parent = 0);
        ~FedMap();

    public Q_SLOTS:
        void on_btnZoomIn_clicked();
        void on_btnZoomOut_clicked();
        void on_btnUpload_clicked();

    protected:
        virtual void wheelEvent(QWheelEvent* event);

    private:
        QVector<fedview::Rack> racks;
        FedGraphicsScene* scene;
        QMatrix matrix;

        QString run;
        QString part;
        QString mode;

        bool performUpload;

        void setViewInfoVisibility(QSlider*);
 
    private Q_SLOTS:
        void setupMatrix(); 
        void catchWheelSignal(QWheelEvent*); 
        void catchZoomSignal(const QPointF&); 
};

#endif
