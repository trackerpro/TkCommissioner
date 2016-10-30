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

#ifndef TKMAP_H
#define TKMAP_H

#include "QConnectedTabWidget.h"
#include "Chip.h"

#include <vector>
#include <TTree.h>
#include <TEventList.h>

#include <QMap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>



class View;
class TkMap : public QConnectedTabWidget
{
    Q_OBJECT
public:
    TkMap(QConnectedTabWidget *parent, TTree* tree, const QVector<int>& sm, const QString& vName, float min, float max, const QString& run);


    public slots:
    /**
     * slot to print selected items from view
     */
    void printSelection();
    /**
     * slot to fix selected items from view
     */
    void fixSelection();
    /**
     * slot to release selected items from view
     */
    void releaseSelection();
    /**
     * slot to change the status of item list
     * 
     * @param items Container of items to have their status changed
     * @param status new status to be set
     */
    void setSelection(QList<QGraphicsItem*> &items, bool status);
private:
    /**
     * set up matrix of the main view
     */
    void setupMatrix();
    /**
     * populate GraphicsView with items
     */
    void populateScene();
    /**
     * Map the module on the TkMap
     */
    void mapModule(Chip*, int, Double_t, unsigned, unsigned, int);
    /**
     * Map the module on the TkMap
     */
    void mapModule(Chip*, int, Double_t*, Double_t*, unsigned, unsigned, int);

    QGraphicsScene *scene;
    View *view;
    QMap<unsigned long,Chip*> modules;
    TTree* tree_;
    QVector<int> smap;
    QString varName_;
    float rangeMin_, rangeMax_;
    QString run_;
};

#endif
