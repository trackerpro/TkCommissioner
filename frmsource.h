#ifndef FRMSOURCE_H
#define FRMSOURCE_H
 
#include "ui_frmsource.h"

#include <QStandardItemModel>
#include <QVector>
#include <QPair>
#include <QString>

#include <TFile.h>

class SourceDisplay : public QConnectedTabWidget, private Ui::SourceDisplay {

    Q_OBJECT
 
    public:
         SourceDisplay(QWidget *parent, QString, QString, const QVector<QPair<QString, QString> >&, const QVector<QPair<unsigned, unsigned> >&, const QString & = "");
        ~SourceDisplay();

    public Q_SLOTS:
        void deviceChanged(QModelIndex, QModelIndex);
        void updatePlot(QStandardItem*);
        void on_source_currentIndexChanged(int);
        void on_btnPrint_clicked();

    private:
        QStandardItemModel* selModel;
        QString currun;
        QString refrun;
	QString partition;
        QVector<QPair<QString, QString> > devices;
        QVector<QPair<unsigned, unsigned> > keys;
        TFile* curclient;
        TFile* refclient;
        bool refexists;
        bool iscurrent;
        bool updatehistitem;
        QString histitem;

        TFile* getClientFile(QString,QString);
};
#endif
