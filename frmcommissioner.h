#ifndef COMMISSIONER_H
#define COMMISSIONER_H
 
#include <QString>
// Container of the Tk Commissioner GUI
#include <QMainWindow>
// To decide how to quit the application
#include <QCloseEvent>

// Parent widget for the TkCommissioner tabs 
#include "QConnectedTabWidget.h"
// Opening window of the Tk Commissioner
#include "frmstartup.h"

// UI file
#include "ui_frmcommissioner.h"

class Commissioner : public QMainWindow, private Ui::Commissioner {

    Q_OBJECT
 
    public:
        Commissioner(QWidget* parent = 0): 
            QMainWindow(parent)
        {
            setupUi(this);
            
            startup = new Startup;
            tabController->addTab(startup, "Home");
            
            connect(tabController, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
            connect(startup, SIGNAL(closeParentSignal()), this, SLOT(closeCommissioner()));
            connect(startup, SIGNAL(showTabSignal(QConnectedTabWidget*, QString)), this, SLOT(showTab(QConnectedTabWidget*, QString)));
        }

        ~Commissioner() {
            if (startup != NULL) delete startup;
        }

    public Q_SLOTS:
        void closeCommissioner() {
            this->close();
        }

        void closeTab(int i) {
            if (i != 0) {
                tabController->widget(i)->close();
                tabController->removeTab(i);
            }        

        }

        void showTab(QConnectedTabWidget* w, QString label) {
            tabController->addTab(w, label);
            tabController->setCurrentWidget(w);
            connect(w, SIGNAL(closeParentSignal()), this, SLOT(closeCommissioner()));
            connect(w, SIGNAL(showTabSignal(QConnectedTabWidget*, QString)), this, SLOT(showTab(QConnectedTabWidget*, QString)));

        }

    protected:
        void closeEvent(QCloseEvent* event) {
            if (startup != NULL) delete startup;
            event->accept();
        }
    
    private:
        Startup* startup;
};

#endif
