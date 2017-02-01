#ifndef QCONNECTEDTABWIDGET_H
#define QCONNECTEDTABWIDGET_H

#include <QWidget>

class QConnectedTabWidget : public QWidget {

    Q_OBJECT
 
    public:
        QConnectedTabWidget(QWidget *parent = 0);
        ~QConnectedTabWidget();

    signals:
        /**
         * Sends a signal to show a new tab with a given widget
         */
        void showTabSignal(QConnectedTabWidget*, QString);
        /**
         * Sends a signal to the commissioner to shut down
         */
        void closeParentSignal();
};        

#endif
