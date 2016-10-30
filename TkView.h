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


#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>
#include <QCheckBox>
#include <QSlider>
#include <QString>
#include <QDoubleSpinBox>

#include "TkMapGlobals.h"

QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QToolButton)

class View;

/**
 * GraphicsView class
 */
class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
  /**
   * initialize GraphicsView. Initialize pointer to View()
   *
   * @param[in] v #View class. The #GraphicsView only stores the pointer
   * and does not own the #View.
   */
  GraphicsView(View *v) : QGraphicsView(), view(v), partition("") { }
  /**
   * draw background using QPainter and using QRectF to set the geometry
   */
  void drawBackground(QPainter *painter, const QRectF &rect);

  void setPartition(const QString& part) {partition = part;}   

protected:
    /**
     * re-implementing QWheelEvent event. Zooms in and out when
     * Qt::ControlModifier is active
     */ 
    void wheelEvent(QWheelEvent *);

private:
    View *view;
    QString partition; 
};

/**
 * Viewer class with various auxilliary functions to change the
 * view, zoom in/out, select items, fix/release them
 */ 
class View : public QFrame
{
    Q_OBJECT
public:
    /**
     * constructor passing name and possibly parent
     */ 
    View(const QString &name, QWidget *parent = 0);
    /**
     * return pointer to graphics view associated with this frame
     */ 
    QGraphicsView *view() const;
    /**
     * public interface to change value of the zoom slider
     */
    void setZoomSliderValue(int value) { zoomSlider->setValue(zoomSlider->value()+value); }

    void setPartition(const QString& part) {graphicsView->setPartition(part);}
 signals:
    /**
     * \deprecated: emitted when inverted() function is called to invert value to state
     */
    bool invertedChanged(int state);
    /**
     * emitted when class is requested to show current selection
     */
    void showSelection();
    /**
     * emitted when class is requested to fix current selection
     */
    void fixSelection();
    /**
     * emitted when class is requested to release current selection
     */
    void releaseSelection();
public slots:
    /** 
     * zoom in by a number of steps
     * \param level number of steps to zoom in
     */
    void zoomIn(int level = 1);
    /** 
     * zoom out by a number of steps
     * \param level number of steps to zoom out
     */
    void zoomOut(int level = 1);
    /**
     * reset the view. Move zoom slider to starting value and reset
     * graphics view to show full map
     */ 
    void resetView();
    /**
     * get the viewport from the GraphicsView associate with this view and update it
     */
    void viewUpdate() { QWidget* viewport = graphicsView->viewport(); if(viewport) viewport->update(); } 
private slots:
    /**
     * slot to connect to a button signal to show the current selection
     */
    void showTriggered() { emit showSelection(); }
    /**
     * slot to connect to a button signal to fix the current selection
     */
    void fixTriggered() { emit fixSelection(); }
    /**
     * slot to connect to a button signal to release the current selection
     */
    void releaseTriggered() { emit releaseSelection(); }
    /**
     * \deprecated slot to connect to a button signal to invert the current selection
     */
    void inverted(int state) { emit invertedChanged(state); } 
    /**
     * slot to activate reset button as soon as view is changed from starting value
     */
    void setResetButtonEnabled();
    /**
     * setup view matrix for this viewer
     */
    void setupMatrix();
    /**
     * toggle pointer mode between drag and select
     */
    void togglePointerMode();
    /**
     * toggle anti-aliasing for drawn objects
     */
    void toggleAntialiasing();
    /**
     * launch print dialog
     */
    void print();
    /**
     * slot to connect changes of minimum spin box
     */
    void minChanged() { if(sbMin->value() > sbMax->value() -0.25 ) sbMin->setValue(sbMax->value()-0.25); M::m()->nMin(sbMin->value()); viewUpdate(); }
    /**
     * slot to connect changes of maximum spin box
     */
    void maxChanged() { if(sbMax->value() < sbMin->value() +0.25 ) sbMax->setValue(sbMin->value()+0.25); M::m()->nMax(sbMax->value()); viewUpdate(); }

private:
    GraphicsView *graphicsView;
    QLabel *label;
    QLabel *label1;
    QLabel *label2;
    QToolButton *selectModeButton;
    QToolButton *dragModeButton;
    QToolButton *antialiasButton;
    QToolButton *printButton;
    QToolButton *resetButton;
    QToolButton *showButton;
    QToolButton *fixButton;
    QToolButton *releaseButton;
    QCheckBox *invertButton;
    QSlider *zoomSlider;
    QDoubleSpinBox *sbMin;
    QDoubleSpinBox *sbMax;
};



#endif
