#include "frmcommissioner.h"
#include "frmtreeviewer.h"

Commissioner::Commissioner(QWidget* parent): 
    QMainWindow(parent)
{
    setupUi(this);

    /*
    Startup* startup = new Startup;
    tabCommissioner->addTab(startup, "Start up");
    */

    TreeViewer* startup = new TreeViewer;
    tabCommissioner->addTab(startup, "Start up");

    connect(tabCommissioner, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(startup, SIGNAL(closeParentSignal()), this, SLOT(closeCommissioner()));
    connect(startup, SIGNAL(showTabSignal(QConnectedTabWidget*, QString)), this, SLOT(showTab(QConnectedTabWidget*, QString)));
}

Commissioner::~Commissioner() {
}

void Commissioner::closeCommissioner() {
    this->close();
}

void Commissioner::closeTab(int i) {
    if (i != 0) {
        tabCommissioner->widget(i)->close();
        tabCommissioner->removeTab(i);
    }        
}

void Commissioner::showTab(QConnectedTabWidget* w, QString label) {
    tabCommissioner->addTab(w, label);
    tabCommissioner->setCurrentWidget(w);
    connect(w, SIGNAL(closeParentSignal()), this, SLOT(closeCommissioner()));
    connect(w, SIGNAL(showTabSignal(QConnectedTabWidget*, QString)), this, SLOT(showTab(QConnectedTabWidget*, QString)));
}

void Commissioner::setInput(const QString& tmpFileName_, std::vector<QPair<QString, QString> > treePaths_) {
    TreeViewer* startup = dynamic_cast<TreeViewer*>(tabCommissioner->widget(0));
    if (startup) startup->setTree(tmpFileName_, treePaths_);
}
