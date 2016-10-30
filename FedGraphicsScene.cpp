#include "FedGraphicsScene.h"

FedGraphicsScene::FedGraphicsScene(QWidget* parent):
    QGraphicsScene(parent)
{
}

void FedGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)  {
    QGraphicsScene::mouseDoubleClickEvent(event);
    emit sendZoomSignal(event->pos());
}
