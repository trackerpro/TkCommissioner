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

#include "TkView.h"

#include <QtGui>


//#ifndef QT_NO_OPENGL
//#include <QtOpenGL>
//#endif

#include <qmath.h>
#include <iostream>


void GraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
  gStyle->SetPalette(1);
  painter->save();
  painter->setBrush(QColor(Qt::white));
  painter->drawRect(rect);
  //painter->restore();
  painter->setBrush(QColor(Qt::black));
  QFont font("Times", 24);
  painter->setFont(font);
  painter->scale(1,-1);
  if (partition.startsWith("TI")) {
    painter->drawText(900,-330,"TIB L1");
    painter->drawText(900,-1000,"TIB L2");
    painter->drawText(1300,-330,"TIB L3");
    painter->drawText(1300,-1000,"TIB L4");
  }
  if (partition.startsWith("TO")) {
    painter->drawText(1700,-325,"TOB L1");
    painter->drawText(1700,-1020,"TOB L2");
    painter->drawText(2100,-325,"TOB L3");
    painter->drawText(2100,-1020,"TOB L4");
    painter->drawText(2500,-325,"TOB L5");
    painter->drawText(2500,-1020,"TOB L6");
  }
  float r=1.0,g=1.0,b=1.0;
  for( int i = 0; i < gStyle->GetNumberOfColors()-1; ++i ) {
    getColor( M::m()->min()+i*(M::m()->range()/gStyle->GetNumberOfColors()),r,g,b);
    if( scene() ) {
      if( i % 5 == 0 ) {
	painter->drawText(4400, -210-i*20, QString::number(M::m()->min()+i*(M::m()->range()/gStyle->GetNumberOfColors()),'g',3) );
      }
      painter->setBrush(QColor::fromRgbF(r,g,b));
      painter->drawRect(4350, -200-i*20,30,20);
    }
  }
  painter->scale(1,-1);
  painter->restore();

}

void GraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->delta() > 0)
            view->zoomIn(6);
        else
            view->zoomOut(6);
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}

View::View(const QString &/*name*/, QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(Sunken | StyledPanel);
    graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);

    QToolButton *zoomInIcon = new QToolButton;
    zoomInIcon->setAutoRepeat(true);
    zoomInIcon->setAutoRepeatInterval(33);
    zoomInIcon->setAutoRepeatDelay(0);
    zoomInIcon->setIcon(QPixmap("zoomin.png"));
    zoomInIcon->setIconSize(iconSize);
    QToolButton *zoomOutIcon = new QToolButton;
    zoomOutIcon->setAutoRepeat(true);
    zoomOutIcon->setAutoRepeatInterval(33);
    zoomOutIcon->setAutoRepeatDelay(0);
    zoomOutIcon->setIcon(QPixmap("zoomout.png"));
    zoomOutIcon->setIconSize(iconSize);
    zoomSlider = new QSlider;
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::TicksRight);

    // Zoom slider layout
    QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
    zoomSliderLayout->addWidget(zoomInIcon);
    zoomSliderLayout->addWidget(zoomSlider);
    zoomSliderLayout->addWidget(zoomOutIcon);

    resetButton = new QToolButton;
    resetButton->setText(tr("0"));
    resetButton->setEnabled(false);

    // Label layout
    QHBoxLayout *labelLayout = new QHBoxLayout;
    label = new QLabel(tr("Min"));
    label1 = new QLabel(tr("Max"));
    label2 = new QLabel(tr("Pointer Mode"));
    selectModeButton = new QToolButton;
    selectModeButton->setText(tr("Select"));
    selectModeButton->setCheckable(true);
    selectModeButton->setChecked(true);
    dragModeButton = new QToolButton;
    dragModeButton->setText(tr("Drag"));
    dragModeButton->setCheckable(true);
    dragModeButton->setChecked(false);
    antialiasButton = new QToolButton;
    antialiasButton->setText(tr("Antialiasing"));
    antialiasButton->setCheckable(true);
    antialiasButton->setChecked(false);

    showButton = new QToolButton;
    showButton->setText(tr("Show Selection"));
    
    fixButton = new QToolButton;
    fixButton->setText(tr("Fix"));

    releaseButton = new QToolButton;
    releaseButton->setText(tr("Release"));

    printButton = new QToolButton;
    printButton->setIcon(QIcon(QPixmap(":/fileprint.png")));

    sbMin = new QDoubleSpinBox;
    sbMax = new QDoubleSpinBox;
    sbMin->setValue(0.0);
    sbMin->setMinimum(0.0);
    sbMin->setMaximum(10000.0);
    sbMin->setSingleStep (1.0);
    sbMax->setValue(10000.0);
    sbMax->setMinimum(0.0);
    sbMax->setMaximum(10000.0);
    sbMax->setSingleStep (1.0);

    QButtonGroup *pointerModeGroup = new QButtonGroup;
    pointerModeGroup->setExclusive(true);
    pointerModeGroup->addButton(selectModeButton);
    pointerModeGroup->addButton(dragModeButton);

    labelLayout->addStretch();
    labelLayout->addWidget(label);
    labelLayout->addWidget(sbMin);
    labelLayout->addWidget(label1);
    labelLayout->addWidget(sbMax);
    labelLayout->addStretch();
    labelLayout->addWidget(label2);
    labelLayout->addWidget(selectModeButton);
    labelLayout->addWidget(dragModeButton);
    labelLayout->addStretch();
    labelLayout->addWidget(antialiasButton);
    labelLayout->addStretch();
    labelLayout->addWidget(showButton);
    labelLayout->addStretch();
    labelLayout->addWidget(fixButton);
    labelLayout->addWidget(releaseButton);
    labelLayout->addStretch();
    labelLayout->addWidget(printButton);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(labelLayout, 0, 0);
    topLayout->addWidget(graphicsView, 1, 0);
    topLayout->addLayout(zoomSliderLayout, 1, 1);
    zoomSliderLayout->addWidget(resetButton);
    setLayout(topLayout);

    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetView()));
    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(setResetButtonEnabled()));
    connect(graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(setResetButtonEnabled()));
    connect(selectModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
    connect(dragModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
    connect(antialiasButton, SIGNAL(toggled(bool)), this, SLOT(toggleAntialiasing()));
    connect(zoomInIcon, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(zoomOutIcon, SIGNAL(clicked()), this, SLOT(zoomOut()));
    connect(printButton, SIGNAL(clicked()), this, SLOT(print()));
    connect(showButton, SIGNAL(clicked()), this, SLOT( showTriggered() ) );
    connect(fixButton, SIGNAL(clicked()), this, SLOT( fixTriggered() ) );
    connect(releaseButton, SIGNAL(clicked()), this, SLOT( releaseTriggered() ) );
    connect(sbMin, SIGNAL(valueChanged ( double ) ), this, SLOT( minChanged() ) );
    connect(sbMax, SIGNAL(valueChanged ( double ) ), this, SLOT( maxChanged() ) );
    setupMatrix();

}

QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}

void View::resetView()
{
    zoomSlider->setValue(250);
    setupMatrix();
    graphicsView->fitInView(QRectF(0, 0, 3000, 1500));

    resetButton->setEnabled(false);
}

void View::setResetButtonEnabled()
{
    resetButton->setEnabled(true);
}

void View::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 325) / qreal(50));

    QMatrix matrix;
    matrix.scale(scale, -scale);
    
    graphicsView->setMatrix(matrix);
    setResetButtonEnabled();
}

void View::togglePointerMode()
{
    graphicsView->setDragMode(selectModeButton->isChecked()
                              ? QGraphicsView::RubberBandDrag
                              : QGraphicsView::ScrollHandDrag);
    graphicsView->setInteractive(selectModeButton->isChecked());
}

void View::toggleAntialiasing()
{
    graphicsView->setRenderHint(QPainter::Antialiasing, antialiasButton->isChecked());
}

void View::print()
{
#ifndef QT_NO_PRINTER
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        graphicsView->render(&painter);
    }
#endif
}

void View::zoomIn(int level)
{
    zoomSlider->setValue(zoomSlider->value() + level);
}

void View::zoomOut(int level)
{
    zoomSlider->setValue(zoomSlider->value() - level);
}



