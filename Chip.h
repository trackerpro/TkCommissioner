#ifndef CHIP_H
#define CHIP_H

#include "TkMapGlobals.h"

#include <QMouseEvent>
#include <TQtWidget.h>
#include <QtGui/QColor>
#include <QtGui/QGraphicsItem>
#include <TText.h>

/** \Class Chip
 * \brief Class representing a single strip tracker module within the tracker map
 *
 * Contains global information about
 * the module and in addition about APVs
 */
class Chip : public QGraphicsItem {
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
     * set SiStripFecKey for a given APV of this object
     */
    void          setAPVFecKey(int i2caddress, unsigned key ) { apvFecKeys_.insert(i2caddress, key); }
    /**
     * set SiStripFedKey for a given APV of this object
     */
    void          setAPVFedKey(int i2caddress, unsigned key ) { apvFedKeys_.insert(i2caddress, key); }
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
     * set run number
     */ 
    void          setRunNumber( int r ) { run_ = r; }
    /**
     * set flag for tool tip text
     */ 
    void          showToolTip( bool f ) { showTT_ = f; }
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
     * special handler for showing pedestals/noise for states
     */ 
    void mouseDoubleClickForState( QGraphicsSceneMouseEvent * event );
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
    /**
     * method to find min and max from a container and return these by reference
     */
    void findMinMax( const QMap<int, std::vector<double> > &map, double &min, double &max );
    /**
     * draw values for a given container onto a TQtWidget
     */
    void drawValues( TQtWidget *widget, int &pad, QMap<int, std::vector<double> >::iterator &it, double &min, double &max, TString value );

    // members
    double                         value_;                /*!< a value associated with this object used to determine its color */
    unsigned long                  detid_;                /*!< detid to uniquely identify this object */
    int                            napvs_;                /*!< the number of APVs associated with this object */
    QColor                         color_;                /*!< a QColor object to steer the current color of the object */
    QPolygonF                      polygon_;              /*!< a QPolygonF that contains the outline of the module */
    QRectF                         rect_;                 /*!< the bounding rectangle of this object */                             
    QVector<QPointF>               points_;               /*!< QVector of points associated with this object */                             
    QMap<int, QPolygonF>           apvs_;                 /*!< Map of polygons for the individual APVs */                             
    QMap<int, double>               apvValues_;           /*!< Map of values for the individual APVs */
    QMap<int, std::vector<double> > apvStripNoiseValues_; /*!< Map of strip noise values for the individual APVs */                             
    QMap<int, std::vector<double> > apvStripPedsValues_;  /*!< Map of strip pedestal values for the individual APVs */                             
    QMap<int, QColor>              apvColors_;            /*!< Map of QColor objects for the individual APVs */                             
    QMap<int, unsigned>            apvFecKeys_;           /*!< Map of SiStripFecKey for the individual APVs */                             
    QMap<int, unsigned>            apvFedKeys_;           /*!< Map of SiStripFedKey for the individual APVs */                             
    TText*                         text;                  /*!< TText object to draw various text elements */ 
    bool                           fixStatus_;            /*!< record fix status of this object */ 
    int                            run_;                  /*!< run number */    
    bool                           showTT_;               /*!< Flag for tool tip text */
    
};

#endif
