#ifndef FRMADDSKIP_H
#define FRMADDSKIP_H
 
#include "ui_frmaddskip.h"

#include <QString>
#include <TTree.h>

class AddSkipChannel : public QDialog, private Ui::AddSkipChannel {

    Q_OBJECT
 
    public:
        AddSkipChannel(bool fed, bool crate, bool fec, bool ring, bool ccu, bool ccuchan, bool lldchan, QWidget *parent = 0);
        ~AddSkipChannel();

        void inputs(QString*, QString*, QString*, QString*, QString*, QString*, QString*, bool*);

    signals:
        void key(QPair<unsigned,unsigned>);

    public Q_SLOTS:
        void accept();
        void reject();

    private:
        bool enableFed;
        bool enableCrate;
        bool enableFec;
        bool enableRing;
        bool enableCcu;
        bool enableCcuChan;
        bool enableLLDChan;

};
#endif
