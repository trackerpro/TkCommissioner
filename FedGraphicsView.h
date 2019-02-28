#ifndef FEDGRAPHICSVIEW_H
#define FEDGRAPHICSVIEW_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>

class FedGraphicsView : public QGraphicsView {

    Q_OBJECT

    public : 
        FedGraphicsView(QWidget* parent = NULL);

    signals:
        void sendWheelSignal(QWheelEvent*);
    
    protected:
        virtual void wheelEvent(QWheelEvent*);

};

#endif
