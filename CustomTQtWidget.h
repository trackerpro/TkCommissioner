#ifndef CUSTOMTQTWIDGET_H
#define CUSTOMTQTWIDGET_H

#include <TQtWidget.h>
#include <QMouseEvent>
#include <QRubberBand>
#include <QPoint>

/** \Class TreeBuilder 
 * 
 * We need to override the TQtWidget class in order to implement the selection functionality
 * The whole purpose of this subclass is to take over the mouse events when the need arises
 *
 */ 
class CustomTQtWidget : public TQtWidget {

    Q_OBJECT
 
    public:
        CustomTQtWidget(QWidget *parent = 0):
            rubberBand(QRubberBand::Rectangle, this),
            origin(0, 0),
            endpoint(0, 0),
            lockY(true),
            takeoverMouse(false)
        {
            Q_UNUSED(parent)
        }

        ~CustomTQtWidget() {
        }

        /**
         * return whether the y-axis is required to be "locked" -- 
         * this is done in the case of 1D plots where we only want to scan the x-axis 
         * to make a selection
         */
        bool getLockY() {
            return lockY;
        }

        /**
         * return whether the the mouse events have been "taken over" for selection purposes
         */
        bool getTakeoverMouse() {
            return takeoverMouse;
        }

        /**
         * set the flag to lock the y-axis
         */
        void setLockY(bool l) {
            lockY = l;
        }

        /**
         * set the flag to take over the mouse events
         */
        void setTakeoverMouse(bool t) {
            takeoverMouse = t;
        }

    signals:
        /**
         * signal emitted after a selection is made. Provides information about the selection coordinates
         */
        void selectSignal(QPoint, QPoint);

        /**
         * signal emitted after a double click. Meant to zoom out 
         */
        void zoomoutSignal();

    protected:
        /**
         * set the point of origin of the selection
         */
        virtual void mousePressEvent(QMouseEvent* event) {
            // If the mouse is not flagged for take-over simply do what the parent TQtWidget class does
            if (!takeoverMouse) {
                TQtWidget::mousePressEvent(event);
            }
            // Determine the pixel coordinates of the starting point of the selection. 
            else {
                origin = event->pos();
                // Constrain the selection area to be within the plot area
                if (origin.x() > GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmax())) origin.setX(GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmax()));
                if (origin.x() < GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmin())) origin.setX(GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmin()));
                if (origin.y() < GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymax())) origin.setY(GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymax()));
                if (origin.y() > GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymin())) origin.setY(GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymin()));
                // lock the y coordinate of the starting point
                if (lockY) origin.setY(GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymin()));
            
                rubberBand.setGeometry(QRect(origin, QSize()));
                rubberBand.show();
            }
        }

        /**
         * update the selection rectangle as the mouse moves
         */
        virtual void mouseMoveEvent(QMouseEvent* event) {
            if (!takeoverMouse) {
                TQtWidget::mouseMoveEvent(event);
            }
            
            else {
                QPoint pt = event->pos();
                // Constrain the selection area to be within the plot area
                if (pt.x() > GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmax())) pt.setX(GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmax()));
                if (pt.x() < GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmin())) pt.setX(GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmin()));
                if (pt.y() < GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymax())) pt.setY(GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymax()));
                if (pt.y() > GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymin())) pt.setY(GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymin()));
                // lock the y coordinate starting point of the 
                if (lockY) pt.setY(GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymax()));
            
                rubberBand.setGeometry(QRect(origin, pt).normalized());
            }
        }

        /**
         * get the end-point of the selection and emit the selection signal
         */
        virtual void mouseReleaseEvent(QMouseEvent* event) {
            if (!takeoverMouse) {
                TQtWidget::mouseReleaseEvent(event);
            }
            
            // Determine the pixel coordinates of the end-point of the selection. 
            else {
                endpoint = event->pos();
                // Constrain the selection area to be within the plot area
                if (endpoint.x() > GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmax())) endpoint.setX(GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmax()));
                if (endpoint.x() < GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmin())) endpoint.setX(GetCanvas()->XtoAbsPixel(GetCanvas()->GetUxmin()));
                if (endpoint.y() < GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymax())) endpoint.setY(GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymax()));
                if (endpoint.y() > GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymin())) endpoint.setY(GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymin()));
                // lock the y coordinate of the end point
                if (lockY) endpoint.setY(GetCanvas()->YtoAbsPixel(GetCanvas()->GetUymax()));
            
                // make the selection rectangle disapper after the mouse is released
                rubberBand.hide();
                // emit the signal informing about the selection
                emit selectSignal(origin, endpoint);
            }
        }

        /**
         * Unzoom the plot
         */
        virtual void mouseDoubleClickEvent(QMouseEvent*) {
            emit zoomoutSignal();
        }

    private:
        /**
         * The rectangle depicting the selection area while the mouse is moving
         */
        QRubberBand rubberBand;
        /**
         * Starting point of the selection
         */
        QPoint origin;
        /**
         * End point of the selection
         */
        QPoint endpoint;
        /**
         * Flag to lock the y-axis
         */
        bool lockY;
        /**
         * Flag to take over the mouse from the TQtWidget
         */
        bool takeoverMouse;
};

#endif
