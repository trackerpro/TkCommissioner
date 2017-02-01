#ifndef FRMCOMMISSIONER_H
#define FRMCOMMISSIONER_H
 
#include "ui_frmcommissioner.h"

#include <QMainWindow>
#include <QString>
#include <QPair>
#include "QConnectedTabWidget.h"

class Commissioner : public QMainWindow, private Ui::Commissioner {

    Q_OBJECT
 
    public:
        Commissioner(QWidget* parent = 0);
        ~Commissioner();

    public Q_SLOTS:
        void closeCommissioner();
        void closeTab(int);
        void showTab(QConnectedTabWidget*, QString);
        void setInput(const QString&, std::vector<QPair<QString, QString> >);
};

#endif
