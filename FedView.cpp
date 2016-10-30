#include "FedView.h"
#include <sstream>
#include <iostream>

fedview::Rack::Rack():
    isEmpty(true),
    x0(0.), y0(0.), width(0.), height(0.)
{
}

fedview::Rack::~Rack() {
}

void fedview::Rack::setCoordinates(int place, bool isB) {
    x0 = place*600., 
    y0 = isB ? 80. : 1580.;
    width = 360.; 
    height = 1140.;
}

void fedview::Rack::createScene(QGraphicsScene* scene) {
    QFont font("Courier New");
    font.setPixelSize(50);
    QGraphicsTextItem* text = scene->addText(name, font);
    text->setPos(x0, y0-80);

    rackframe = scene->addRect(QRectF(x0, y0, width, height));

    h.crateframe = scene->addRect(QRectF(x0+12., (0. * height/3.) + y0+30., width-24., height/3. - 60.));
    l.crateframe = scene->addRect(QRectF(x0+12., (1. * height/3.) + y0+30., width-24., height/3. - 60.));
    d.crateframe = scene->addRect(QRectF(x0+12., (2. * height/3.) + y0+30., width-24., height/3. - 60.));

    if (!h.isEmpty) {
        for (std::size_t i = 0; i < 21; i++) {
            if (h.feds[i].id != 0) {
                QPen redpen(Qt::red);
                QPen graypen(Qt::gray);
                redpen.setWidth(2);
                QGraphicsRectItem* slot = scene->addRect(QRectF(x0+12.+i*16., (0. * height/3.) + y0+30., 10., height/3. - 60.), h.feds[i].isMarked ? redpen : graypen, QBrush(Qt::gray));
                slot->setFlag(QGraphicsItem::ItemIsSelectable, true);
                slot->setData(0, QString::number(h.feds[i].id));
                std::stringstream tooltipss;
                tooltipss << "FED ID : " << h.feds[i].id << std::endl;
                tooltipss << "SLOT : " << i+1 << std::endl;
                slot->setToolTip(tooltipss.str().c_str());
                h.feds[i].fedframe = slot;
                QFont fedtextfont("Times");
                fedtextfont.setPixelSize(5);
                h.feds[i].fedtext = scene->addText(QString::number(h.feds[i].id), fedtextfont);
                h.feds[i].fedtext->setPos(x0+8.+i*16., (0. * height/3.) + y0+30. + height/3. - 60. + 5);
                h.feds[i].fedtext->setVisible(false);
                h.feds[i].slottext = scene->addText(QString::number(i+1), fedtextfont);
                h.feds[i].slottext->setPos(x0+8.+i*16., (0. * height/3.) + y0+30.- 15);
                h.feds[i].slottext->setVisible(false);

                for (std::size_t j = 0; j < 8; j++) {
                    bool isUnitMarked = h.feds[i].units[j].isMarked;
                    h.feds[i].units[j].feunitframe = scene->addRect(QRectF(x0+13.+i*16., (0. * height/3.) + y0+30. + (-2*j+15)*(height/3. - 60.)/16., 8., 8), isUnitMarked ? redpen : graypen, QBrush(Qt::white));
                    h.feds[i].units[j].feunitframe->setToolTip(QString("FE Unit : ")+QString::number(j+1));
                    QFont fedunittextfont("Times");
                    fedunittextfont.setPixelSize(3);
                    h.feds[i].units[j].feunittext = scene->addText(QString::number(j+1), fedunittextfont);
                    h.feds[i].units[j].feunittext->setPos(x0+13.+i*16., (0. * height/3.) + y0+30. + (-2*j+15)*(height/3. - 60.)/16. - 10.);
                    h.feds[i].units[j].feunittext->setVisible(false);
                    for (int k = 0; k < 12; k++) {
                        bool isChanMarked = h.feds[i].units[j].channels[k].isMarked;
                        h.feds[i].units[j].channels[k].fechannelframe = 
                        scene->addRect(QRectF(x0+14.8+i*16.+2.5*(2-int((k%3)))*(0.7), (0. * height/3.) + y0+30. + (-2*j+15)*(height/3. - 60.)/16. + 1.4 + 1.5*(3-int(k/3)), 0.75, 0.75), isChanMarked ? QPen(Qt::red):graypen, QBrush(Qt::white));
                        h.feds[i].units[j].channels[k].fechannelframe->setToolTip(QString("FE Channel : ")+QString::number(k+1));
                        h.feds[i].units[j].channels[k].fechannelframe->setVisible(false);
                    }
                }
            }
        }
    }

    if (!l.isEmpty) {
        for (std::size_t i = 0; i < 21; i++) {
            if (l.feds[i].id != 0) {
                QPen redpen(Qt::red);
                QPen graypen(Qt::gray);
                redpen.setWidth(2);
                QGraphicsRectItem* slot = scene->addRect(QRectF(x0+12.+i*16., (1. * height/3.) + y0+30., 10, height/3. - 60.), l.feds[i].isMarked ? redpen : graypen, QBrush(Qt::gray));
                slot->setFlag(QGraphicsItem::ItemIsSelectable, true);
                slot->setData(0, QString::number(l.feds[i].id));
                std::stringstream tooltipss;
                tooltipss << "FED ID : " << l.feds[i].id << std::endl;
                tooltipss << "SLOT : " << i+1 << std::endl;
                slot->setToolTip(tooltipss.str().c_str());
                l.feds[i].fedframe = slot;
                QFont fedtextfont("Times");
                fedtextfont.setPixelSize(5);
                l.feds[i].fedtext = scene->addText(QString::number(l.feds[i].id), fedtextfont);
                l.feds[i].fedtext->setPos(x0+8.+i*16., (1. * height/3.) + y0+30. + height/3. - 60. + 5);
                l.feds[i].fedtext->setVisible(false);
                l.feds[i].slottext = scene->addText(QString::number(i+1), fedtextfont);
                l.feds[i].slottext->setPos(x0+8.+i*16., (1. * height/3.) + y0+30.- 15);
                l.feds[i].slottext->setVisible(false);

                for (std::size_t j = 0; j < 8; j++) {
                    bool isUnitMarked = l.feds[i].units[j].isMarked;
                    l.feds[i].units[j].feunitframe = scene->addRect(QRectF(x0+13.+i*16., (1. * height/3.) + y0+30. + (-2*j+15)*(height/3. - 60.)/16., 8., 8), isUnitMarked ? redpen : graypen, QBrush(Qt::white));
                    l.feds[i].units[j].feunitframe->setToolTip(QString("FE Unit : ")+QString::number(j+1));
                    QFont fedunittextfont("Times");
                    fedunittextfont.setPixelSize(3);
                    l.feds[i].units[j].feunittext = scene->addText(QString::number(j+1), fedunittextfont);
                    l.feds[i].units[j].feunittext->setPos(x0+13.+i*16., (1. * height/3.) + y0+30. + (-2*j+15)*(height/3. - 60.)/16. - 10.);
                    l.feds[i].units[j].feunittext->setVisible(false);
                    for (int k = 0; k < 12; k++) {
                        bool isChanMarked = l.feds[i].units[j].channels[k].isMarked;
                        l.feds[i].units[j].channels[k].fechannelframe = 
                        scene->addRect(QRectF(x0+14.8+i*16.+2.5*(2-int((k%3)))*(0.7), (1. * height/3.) + y0+30. + (-2*j+15)*(height/3. - 60.)/16. + 1.4 + 1.5*(3-int(k/3)), 0.75, 0.75), isChanMarked ? QPen(Qt::red):graypen, QBrush(Qt::white));
                        l.feds[i].units[j].channels[k].fechannelframe->setToolTip(QString("FE Channel : ")+QString::number(k+1));
                        l.feds[i].units[j].channels[k].fechannelframe->setVisible(false);
                    }
                }
            }
        }
    }

    if (!d.isEmpty) {
        for (std::size_t i = 0; i < 21; i++) {
            if (d.feds[i].id != 0) {
                QPen redpen(Qt::red);
                QPen graypen(Qt::gray);
                redpen.setWidth(2);
                QGraphicsRectItem* slot = scene->addRect(QRectF(x0+12.+i*16., (2. * height/3.) + y0+30., 10., height/3. - 60.), d.feds[i].isMarked ? redpen : graypen, QBrush(Qt::gray));
                slot->setFlag(QGraphicsItem::ItemIsSelectable, true);
                slot->setData(0, QString::number(d.feds[i].id));
                std::stringstream tooltipss;
                tooltipss << "FED ID : " << d.feds[i].id << std::endl;
                tooltipss << "SLOT : " << i+1 << std::endl;
                slot->setToolTip(tooltipss.str().c_str());
                d.feds[i].fedframe = slot;
                QFont fedtextfont("Times");
                fedtextfont.setPixelSize(5);
                d.feds[i].fedtext = scene->addText(QString::number(d.feds[i].id), fedtextfont);
                d.feds[i].fedtext->setPos(x0+8.+i*16., (2. * height/3.) + y0+30. + height/3. - 60. + 5);
                d.feds[i].fedtext->setVisible(false);
                d.feds[i].slottext = scene->addText(QString::number(i+1), fedtextfont);
                d.feds[i].slottext->setPos(x0+8.+i*16., (2. * height/3.) + y0+30.- 15);
                d.feds[i].slottext->setVisible(false);

                for (std::size_t j = 0; j < 8; j++) {
                    bool isUnitMarked = d.feds[i].units[j].isMarked;
                    d.feds[i].units[j].feunitframe = scene->addRect(QRectF(x0+13.+i*16., (2. * height/3.) + y0+30. + (-2*j+15)*(height/3. - 60.)/16., 8., 8), isUnitMarked ? redpen : graypen, QBrush(Qt::white));
                    d.feds[i].units[j].feunitframe->setToolTip(QString("FE Unit : ")+QString::number(j+1));
                    QFont fedunittextfont("Times");
                    fedunittextfont.setPixelSize(3);
                    d.feds[i].units[j].feunittext = scene->addText(QString::number(j+1), fedunittextfont);
                    d.feds[i].units[j].feunittext->setPos(x0+13.+i*16., (2. * height/3.) + y0+30. + (-2*j+15)*(height/3. - 60.)/16. - 10.);
                    d.feds[i].units[j].feunittext->setVisible(false);
                    for (int k = 0; k < 12; k++) {
                        bool isChanMarked = d.feds[i].units[j].channels[k].isMarked;
                        d.feds[i].units[j].channels[k].fechannelframe = 
                        scene->addRect(QRectF(x0+14.8+i*16.+2.5*(2-int((k%3)))*(0.7), (2. * height/3.) + y0+30. + (-2*j+15)*(height/3. - 60.)/16. + 1.4 + 1.5*(3-int(k/3)), 0.75, 0.75), isChanMarked ? QPen(Qt::red):graypen, QBrush(Qt::white));
                        d.feds[i].units[j].channels[k].fechannelframe->setToolTip(QString("FE Channel : ")+QString::number(k+1));
                        d.feds[i].units[j].channels[k].fechannelframe->setVisible(false);
                    }
                }
            }
        }
    }
}

