#ifndef FEDGRAPHICSSCENE_H
#define FEDGRAPHICSSCENE_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class FedGraphicsScene : public QGraphicsScene {

    Q_OBJECT

    public : 
        FedGraphicsScene(QWidget* parent = NULL);

    signals:
        void sendZoomSignal(const QPointF&);
    
    protected:
        virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
};

#endif
