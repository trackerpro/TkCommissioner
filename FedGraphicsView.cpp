#include "FedGraphicsView.h"

FedGraphicsView::FedGraphicsView(QWidget* parent):
    QGraphicsView(parent)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setDragMode(ScrollHandDrag);
}

void FedGraphicsView::wheelEvent(QWheelEvent* event) {
    emit sendWheelSignal(event);
}

