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

#ifndef CHIP_H
#define CHIP_H

class QMouseEvent;
class TQtWidget;

#include "TkMapGlobals.h"

#include <QtGui/QColor>
#include <QtGui/QGraphicsItem>
#include <TText.h>

/** \Class Chip
 * \brief Class representing a single strip tracker module within the tracker map
 *
 * Contains global information about
 * the module and in addition about APVs
 */
class Chip : public QGraphicsItem
{
public:
    /**
     * default constructor
     */ 
    Chip();
    /**
     * constructor passing a QColor object
     */ 
    Chip(const QColor &color);

    /**
     * return the bounding rectangle of this object
     */
    QRectF        boundingRect() const; 
    /**
     * return a QPainterPath with the polygon of this object
     */
    QPainterPath  shape() const;
    /**
     * paint method to determine how this object should appear
     */
    void          paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    /**
     * set points 
     * @param points QVector of QPointF objects
     */
    void          setShape(const QVector<QPointF> &points) ;
    /**
     * set global value associated with this object
     */
    void          setValue(double value) { value_ = value;   setFlags(ItemIsSelectable ); }
    /**
     * set QColor object in this class
     */ 
    void          setColor(QColor color) { color_ = color; }
    /**
     * method set the value for a given APV of this object
     * 
     * @param[in] i2caddress The i2caddress of the APV whose value should be set 
     * @param[in] value The new value for this APV
     */
    void          setAPVValue(int i2caddress, double value) { apvValues_.insert(i2caddress,value); }
    /**
     * set strip noise values for a given APV of this object
     */
    void          setAPVStripNoiseValues(int i2caddress, double *value );
    /**
     * set strip pedestal values for a given APV of this object
     */
    void          setAPVStripPedsValues(int i2caddress, double *value );
    /**
     * set QColor object for a given APV of this object
     */
    void          setAPVColor(int i2caddress, QColor color) { apvColors_.insert(i2caddress,color); }
    /**
     * set detid of this object, derive number of APVs on this type of module using #nAPV method
     */
    void          setDetid(unsigned long detid) { detid_ = detid;  napvs_ = nAPV(detid_); if( points_.size() > 0 ) constructApvs(); }
    /**
     * get global value for this object
     */
    double         getValue() { return value_; }
    /**
     * get detid of this object
     */ 
    unsigned long getDetid() { return detid_; }
    /**
     * set fix status of this object
     */ 
    int getNAPVs() { return napvs_; }
    /**
     * set fix status of this object
     */ 
    void          setFixStatus( bool rhs ) { fixStatus_ = rhs; }
    /**
     * get fix status of this object
     */ 
    bool          fixStatus() { return fixStatus_; }
    /**
     * initiate to construct APVs in this object
     */ 
    void          constructApvs();

 protected:
    /**
     * overload of QGraphicsItem::mouseDoubleClickEvent
     * displays dialog with QtWidget to display information from APVs
     */ 
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
    /**
     * overload of QGraphicsItem::mousePressEvent
     * changes selection status of the item
     */ 
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * overload of QGraphicsItem::mouseMoveEvent
     * this method only forwards the event to the base class
     */ 
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /**
     * overload of QGraphicsItem::mouseReleaseEvent
     * this method only forwards the event to the base class
     */ 
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

 private:
    // private methods
    /**
     * method to find min and max from a container and return these by reference
     */
    void findMinMax( const QMap<int, std::vector<double> > &map, double &min, double &max );
    /**
     * draw values for a given container onto a TQtWidget
     */
    void drawValues( TQtWidget *widget, int &pad, QMap<int, std::vector<double> >::iterator &it, double &min, double &max, TString value );

    // members
    double                          value_;               /*!< a value associated with this object used to determine its color */
    unsigned long                  detid_;               /*!< detid to uniquely identify this object */
    int                            napvs_;               /*!< the number of APVs associated with this object */
    QColor                         color_;               /*!< a QColor object to steer the current color of the object */
    QPolygonF                      polygon_;             /*!< a QPolygonF that contains the outline of the module */
    QRectF                         rect_;                /*!< the bounding rectangle of this object */                             
    QVector<QPointF>               points_;              /*!< QVector of points associated with this object */                             
    QMap<int, QPolygonF>           apvs_;                /*!< Map of polygons for the individual APVs */                             
    QMap<int, double>               apvValues_;           /*!< Map of values for the individual APVs */
    QMap<int, std::vector<double> > apvStripNoiseValues_; /*!< Map of strip noise values for the individual APVs */                             
    QMap<int, std::vector<double> > apvStripPedsValues_;  /*!< Map of strip pedestal values for the individual APVs */                             
    QMap<int, QColor>              apvColors_;           /*!< Map of QColor objects for the individual APVs */                             
    TText                         *text;                 /*!< TText object to draw various text elements */ 
    bool                           fixStatus_;           /*!< record fix status of this object */ 
    
    
};

#endif
