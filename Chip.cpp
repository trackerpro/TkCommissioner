/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "Chip.h"

#include <QtGui>
#include <iostream>
#include <TQtWidget.h>
#include <TH1.h>


Chip::Chip()
  : value_(0), detid_(0), napvs_(0), color_(Qt::gray), text(new TText), fixStatus_(0)
{

}


Chip::Chip(const QColor &color)
  : value_(0), detid_(0), napvs_(0), color_(color), text(new TText), fixStatus_(0)
{
  //setFlags(ItemIsSelectable | ItemIsMovable);
}

QRectF Chip::boundingRect() const
{
  return rect_;
}

QPainterPath Chip::shape() const
{
  QPainterPath path;
  path.addPolygon(polygon_);
  return path;
  
}
void Chip::setShape(const QVector<QPointF> &points) 
{
  points_ = points;
  polygon_ = points_;
  rect_ = polygon_.boundingRect();

  QPointF point = rect_.center();
  polygon_.translate(- point);
  QTransform trans;  
  trans.scale(0.8,1);
  polygon_ = trans.map( polygon_ );
  polygon_.translate(point);

  if( detid_ != 0 ) constructApvs();
}

void Chip::constructApvs()
{
  if( napvs_ == 0 && detid_ != 0 ) napvs_ = nAPV(detid_);
  QLineF base;
  QLineF slope;
  
  if( points_.size() == 3 ) { 
    base.setP1( polygon_.at(2));
    base.setP2( polygon_.at(1));
    slope.setP1(polygon_.at(2));
    slope.setP2(polygon_.at(0));
  }
  if( points_.size() == 4 ) { 
    base.setP1( polygon_.at(0));
    base.setP2( polygon_.at(3));
    slope.setP1(polygon_.at(1));
    slope.setP2(polygon_.at(2));

  }

    
  base.setLength(base.length()/napvs_);
  slope.setLength(slope.length()/napvs_);
  
  // draw individual APVs (4 or 6)
  int i2c = 32;
  for( int i = 0; i < napvs_; ++i, ++i2c ) {
    if (napvs_ == 4 && i2c == 34 ) i2c += 2;
    QPolygonF apv;
    apv << base.p1() << base.p2() << slope.p2() << slope.p1() << base.p1();
    apvs_.insert(i2c,apv);
    apvColors_.insert(i2c,QColor(Qt::white));
    base.translate(base.dx(),base.dy());
    slope.translate(slope.dx(),slope.dy());
  }	

}

void Chip::setAPVStripNoiseValues(int i2caddress, double *value )
{
  std::vector<double> tmp; tmp.resize(128); 
  std::copy(value, value+128,tmp.begin()); 
  apvStripNoiseValues_.insert(i2caddress,tmp);
}

void Chip::setAPVStripPedsValues(int i2caddress, double *value )
{
  std::vector<double> tmp; tmp.resize(128); 
  std::copy(value, value+128,tmp.begin()); 
  apvStripPedsValues_.insert(i2caddress,tmp);
}


void Chip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(widget);

  // this is the real magic of this class: get the 'level of detail'
  // from the QPainter that is responsible for drawing these objects
  // this level corresponds basically to the zoom level and hence we
  // can use this information to decide what we want to show (APVs or
  // not)
  const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

  painter->save();

  // add a tool tip, i.e. mouseover information for this module
  this->setToolTip(QString("<table>")+
		   QString("<tr><td>Detid: </td><td>")+QString::number(detid_)+QString("</td></tr>")+
		   QString("<tr><td>value: </td><td>")+QString::number(value_)+QString("</td</tr>"));
 
  /* Not need for the offline  
  // if we are zoomed in, also include information about the APVs
  if( lod >= 3 ) {
    this->setToolTip(this->toolTip()+QString("<tr><td>I2CAddress</td><td>Values</td></tr>"));

    QMap<int, double>::iterator it = apvValues_.begin();
    for( ; it != apvValues_.end(); ++it ) {
      this->setToolTip(this->toolTip()+QString("<tr><td>")+QString::number(it.key()%31)+QString("</td><td>")+QString::number(it.value())+QString("</td</tr>"));
    }
  }
  */

  this->setToolTip(this->toolTip()+QString("</table>"));
  Float_t r=100,g=100,b=100;
  getColor(value_,r,g,b);

  // set pen size depending on zoom-level so that we don't draw too
  // thick lines
  QPen newPen;
  if( lod < 3 ) { 
    newPen.setWidthF(0.5);
  } else if ( lod >= 3 && lod < 10 ) {
    newPen.setWidthF(0.5);
  } else {
    newPen.setWidthF(0.25);
  }

  // change outline of the module depending if it is selected and/or
  // fixed
  if ( (option->state & QStyle::State_Selected) ) {
    newPen.setColor( QColor(Qt::red) );
    newPen.setWidthF(1.5);
  } else {
    if( fixStatus_ ) { 
      newPen.setWidthF(1.5);
      newPen.setColor(QColor(Qt::blue));
    } else if(  lod < 0.55 && !( value_ < 1e-6 && value_ > -1e-6 ) ) {
      newPen.setColor(QColor::fromRgbF(r,g,b));
    } else {
      newPen.setColor(QColor(Qt::black));
    }
  }

  // if we are zoomed in, we paint the APV objects
  if (lod >= 3) {
    painter->setPen(QPen(Qt::black,0));
    QMap<int, QPolygonF>::iterator it = apvs_.begin();
    for( ; it != apvs_.end(); ++it ) {
      r=100;g=100;b=100;
      getColor(apvValues_[it.key()],r,g,b);
      painter->setBrush(QColor::fromRgbF(r,g,b));
      painter->drawPolygon(it.value());
    }
  }

  painter->setPen(newPen);
  painter->setBrush(QBrush(QColor::fromRgbF(r,g,b), lod >= 3 ? Qt::NoBrush : Qt::SolidPattern  ) );
  painter->drawPolygon(polygon_);
  painter->restore();  

}


void Chip::findMinMax( const QMap<int, std::vector<double> > &map, double &min, double &max ) 
{
  for( QMap<int, std::vector<double> >::const_iterator it = map.begin(); it != map.end(); ++it ) {
    double tmin = *std::min_element(it.value().begin(),it.value().end());
    double tmax = *std::max_element(it.value().begin(),it.value().end());
    if( tmin < min ) min = tmin;
    if( tmax > max ) max = tmax;
  }  

}

void Chip::drawValues(TQtWidget *widget, int &pad, QMap<int, std::vector<double> >::iterator &it , double &min, double &max, TString value  )
{
  widget->GetCanvas()->cd(pad)->DrawFrame(0.5,min-min*0.1,128.5,max+max*0.1);
  text->DrawTextNDC(0.2,0.9,TString::Format("Detid %ld APV %d",detid_,it.key()%31));
  // check if we already have a histogram for this APV in the current
  // session, if so, we just re-use it and return....
  TH1F *tmp = static_cast<TH1F*>(gROOT->FindObject(Form("%s_%ld_%d",value.Data(),detid_,it.key())));
  if( tmp ) {
    tmp->DrawCopy("histsame");
    ++pad;
    return;
  }
  // ... if it doesn't exist, we create a new one and populate it
  tmp = new TH1F(Form("%s_%ld_%d", value.Data(),detid_,it.key()),"",128,0.5,128.5);
  for( int i = 0; i < 128; ++i ) {
    tmp->SetBinContent(i+1,it.value()[i]);
  }
  tmp->DrawCopy("histsame");
  ++pad;
}

void Chip::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  Q_UNUSED(event);
}


void Chip::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

  Q_UNUSED(event);
  if( apvStripNoiseValues_.size() == 0 ) return;

  if( apvStripNoiseValues_.size() != apvStripPedsValues_.size() ) {
    std::cerr << "Not all APVs have both pedestal and noise values\nThis should not happen!" << std::endl;
    return;
  }

  QDialog *dialog = new QDialog;
  QRectF area = QApplication::desktop()->screenGeometry();
  float theWidth = area.width()/6.0;
  float theHeight = area.height()/2.0;
  dialog->resize(theWidth*apvs_.size(),theHeight);
  QGridLayout *topLayout = new QGridLayout;
  TQtWidget *widget = new TQtWidget;
  //widget->GetCanvas()->Divide(apvs_.size(),2,0);
  widget->GetCanvas()->Divide(apvs_.size(),1,0);
  QMap<int, std::vector<double> >::iterator it = apvStripPedsValues_.begin();
  double min = 0xFFFF, max = -0xFFFF;

  findMinMax(apvStripPedsValues_,min,max);
  
  int pad = 1;
  for( ; it != apvStripPedsValues_.end(); ++it ) {
    drawValues(widget, pad,it,min,max,"Noise");
  }

  /*
  it = apvStripNoiseValues_.begin();
  min = 0xFFFF; max = -0xFFFF;

  findMinMax(apvStripNoiseValues_,min,max);
  for( ; it != apvStripNoiseValues_.end(); ++it ) {
    drawValues(widget, pad,it,min,max,"Pedestal");
  }
  */


  topLayout->addWidget(widget);
  dialog->setLayout(topLayout);
  dialog->show();

  QGraphicsItem::mousePressEvent(event);
  update();
}

void Chip::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->modifiers() & Qt::ShiftModifier) {
    update();
    return;
  }
  QGraphicsItem::mouseMoveEvent(event);
}

void Chip::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mouseReleaseEvent(event);
  update();
}
