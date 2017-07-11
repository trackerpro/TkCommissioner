#ifndef FEDVIEW_H
#define FEDVIEW_H

#include <QString>
#include <QtCore>
#include <QtGui>
#include <QVector>
#include <QEvent>
#include <iostream>

namespace fedview {

    struct FEChannel {
        bool isMarked;
        QGraphicsItem* fechannelframe;

        FEChannel(bool isMarked_ = false):
            isMarked(isMarked_)
        {
        }
    };

    struct FEUnit {
        bool isMarked;
        QGraphicsItem* feunitframe;
        QGraphicsItem* feunittext;
        QVector<FEChannel> channels;

        FEUnit(bool isMarked_ = false):
            isMarked(isMarked_)
        {
            for (int i = 0; i < 12; i++) channels.push_back(FEChannel());
        }
    };

    struct FED {

        unsigned id;
        bool isMarked;
        bool isSelected;
        QGraphicsItem* fedframe;
        QGraphicsItem* fedtext;
        QGraphicsItem* slottext;
        QVector<FEUnit> units;

        FED(unsigned id_ = 0, bool isMarked_ = false ):
            id(id_),
            isMarked(isMarked_),
            isSelected(false) 
        {
            for (int i = 0; i < 8; i++) units.push_back(FEUnit());
        }

    };

    struct Crate {
        bool isEmpty;
        QGraphicsItem* crateframe;
        QVector<FED> feds;

        Crate():
            isEmpty(true)
        {
            for (int i = 0; i < 21; i++) feds.push_back(FED());
        }   

        //void addFed(unsigned slot, unsigned fedid, bool marked, bool overwrite=false) {
        void addFed(unsigned slot, unsigned fedid, QVector<QVector<bool> > feinfo, bool overwrite=false) {
            if (slot > 21 || slot < 3) {
                std::cerr << "You are trying to add an invalid slot " << slot << " for FED " << fedid << std::endl;   
                return;
            } 
            if (feds[slot-1].id != 0) {
                std::cerr << "FED " << feds[slot-1].id << " already mapped in slot " << slot << "... " << (overwrite ? "overwriting" : "skipping") << std::endl;
                if (!overwrite) return;
            }   

            feds[slot-1].id = fedid;
            feds[slot-1].isMarked = (feinfo.size() > 0);
            isEmpty = false;
            if (!feds[slot-1].isMarked) return;
            for (int i = 0; i < 8; i++) {
                bool isFeUnitMarked = false;
                for (int j = 0; j < 12; j++) if (feinfo[i][j]) isFeUnitMarked = true;
                feds[slot-1].units[i].isMarked = isFeUnitMarked;
                if (feds[slot-1].units[i].isMarked) {
                    for (int j = 0; j < 12; j++) feds[slot-1].units[i].channels[j].isMarked = feinfo[i][j];
                }
            }
        }       
    };

    struct Rack {
        bool isEmpty;
        QGraphicsItem* rackframe;
        QString name;
        Crate d, h, l;
        double x0, y0, width, height;
        
        Rack();
        ~Rack();
        
        void setCoordinates(int, bool);
        void createScene(QGraphicsScene*);
    };

}

#endif
