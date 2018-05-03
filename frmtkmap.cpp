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

#include "frmtkmap.h"
#include "cmssw/SiStripFecKey.h"
#include "cmssw/SiStripFedKey.h"
#include "TkView.h"
#include "Chip.h"

#include <QtGui>
#include <QTextStream>
#include <QFile>


#include <TObjArray.h>
#include <TObjString.h>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"

#include <iostream>



inline const char* getColor(float value, float maxvalue, float minvalue) 
{
  gStyle->SetPalette(1);
  Float_t range = maxvalue - minvalue;
  Int_t nColors = gStyle->GetNumberOfColors()-1;
  Float_t stepsize = static_cast<Float_t>(nColors) / range;
  TColor *color = gROOT->GetColor(static_cast<Int_t>(static_cast<Int_t>( (  value - minvalue) ) * stepsize + 51));
  if( !color ) return qPrintable(QString("#ffffff"));
  return color->AsHexString();
}




TkMap::TkMap(QConnectedTabWidget *parent, TTree* tree, const QVector<int>& sm, const QString& vName, float min, float max, const QString& run)
  : QConnectedTabWidget(parent),
    tree_(tree),
    varName_(vName),
    rangeMin_(min),
    rangeMax_(max),
    run_(run)
{
    smap.clear();
    for (int i = 0; i < sm.size(); i++) smap.push_back(sm[i]);    

    if( tree_ == NULL ) {
        std::cerr << "Input tree to the TkMap is NULL" << std::endl;
        return;
    }
    populateScene();
    
    srand ( time(NULL) );
    view = new View("Top left view", NULL, rangeMin_, rangeMax_);
    view->view()->setScene(scene);
        
    
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
    
    //setWindowTitle(tr("Tracker Map"));
    
    //this->resize(QSize(1000,600));
    
    connect(view, SIGNAL(showSelection()    ), this, SLOT(printSelection()   ) );
    connect(view, SIGNAL(fixSelection()     ), this, SLOT(fixSelection()     ) );
    connect(view, SIGNAL(releaseSelection() ), this, SLOT(releaseSelection() ) );

}



void TkMap::populateScene()
{
  scene = new QGraphicsScene;
  QColor background(Qt::cyan);
  background = background.lighter();
  scene->setBackgroundBrush(background);
  
  QGraphicsTextItem* item = scene->addText(QString::fromAscii(""));
  item->setPos(3200,0);
  item = scene->addText(QString::fromAscii(""));
  item->setPos(3200,1500);
  item = scene->addText(QString::fromAscii(""));
  item->setPos(500,1500);
  item = scene->addText(QString::fromAscii(""));
  item->setPos(500,0);

  // open input stream to read ascii file with tk map layout
  QFile file("tkmap_bare");
  bool in = file.open(QIODevice::ReadOnly);
  QTextStream stream(&file);

  if(!in) {
    std::cerr << "Could not open tk map layout file" << std::endl;
    return;
  } 

  UInt_t count = 0;
  Double_t minx = 0xFFFFFF, maxx = -0xFFFFFF, miny = 0xFFFFFF, maxy = -0xFFFFFFF;

  while( ! file.atEnd() ) {

    float x[5],y[5];
    Long64_t detid = 0;
    ++count;

    QString line = stream.readLine();
    TString string( qPrintable(line) );

    // going via TString::Tokenize because the line length is not
    // fixed, hence I don't like to use ifstream::operator>>
    TObjArray* array = string.Tokenize(" ");

    // no content, move on
    if( array->GetEntries() == 0 ) continue;

    QVector<QPointF> points;

    int ix = 0, iy = 0;
    for( Int_t i = 0; i < array->GetEntries(); ++i ) {
      if( i == 0 ) { 
	// casting madness: TObjArray contains TObjString* so need to
	// cast the result of At() to TObjString, then get the
	// String() from that guy and afterwards convert it to what it
	// actually is: a long integer. 
	detid = static_cast<TObjString*>(array->At(i))->String().Atoll();
      }
      else {
	// x-coordinate in even fields and y in odd
	// fields..... Reading this again this may actually be the
	// other way around but shouldn't really matter
	if( i % 2 == 0 ) {
	  x[ix] =  static_cast<TObjString*>(array->At(i))->String().Atof();
	  if( x[ix] < minx ) minx = x[ix];
	  if( x[ix] > maxx ) maxx = x[ix];
	  ++ix;
	} else {
	  y[iy] =  static_cast<TObjString*>(array->At(i))->String().Atof();
	  if( y[iy] < miny ) miny = y[iy];
	  if( y[iy] > maxy ) maxy = y[iy];
	  ++iy;
	}
      }
    }
    if( detid == 0 ) {
      std::cerr << "Could not parse any detid from line " << count << std::endl;
      continue;
    }
    if(ix != iy ) {
      std::cerr << "Did not find the same number of x and y points in line " << count << std::endl;
      continue;
    }
    if( ix == 0 ) { 
      std::cerr << "Did not find any points for detid " << detid << " in line " << count << std::endl;
      continue;
    }
    // < TIB = Pixel
    //if( subdet(detid) < TIB ) continue;

    for( int i = 0; i < ix; ++i ) {
      points.push_back(QPointF(x[i],y[i]));
    }
    QPolygonF polygon(points);
    Chip *chip = new Chip();
    chip->setDetid(detid);
    chip->setShape(points);

    chip->setVisible(true);

    QGraphicsItem* item = dynamic_cast<QGraphicsItem*>(chip);

    // from the Qt documentation: 
    //
    // void QGraphicsScene::addItem ( QGraphicsItem * item ) 
    //
    // Adds or moves the item and all its childen to this scene. This
    // scene takes ownership of the item. So while we are not
    // deleting the Chip object, there should be no memory leaked
    scene->addItem(item);
    modules[detid] = chip;

  }

  if( tree_ ) {
    TObjArray* branchList = tree_->GetListOfBranches();
 
    QString typeName = "";
    Double_t var = 0.0;
    Double_t did = 0.0;
    Double_t di2c = 0.0;
    Float_t fvar = 0.0;
    Double_t dvar = 0.0;
    Int_t ivar = 0;
    UInt_t uvar = 0;
    //Double_t noisevar[128];
    //Double_t pedsvar[128];

    //TBranch* bFecCrate       = tree_->GetBranch("FecCrate");
    //TBranch* bFec            = tree_->GetBranch("Fec");
    //TBranch* bRing           = tree_->GetBranch("Ring");
    //TBranch* bCcu            = tree_->GetBranch("Ccu");
    //TBranch* bI2CChannel     = tree_->GetBranch("I2CChannel");
    //TBranch* blasChan        = tree_->GetBranch("lasChan");
    TBranch* bFecKey         = tree_->GetBranch("FecKey");
    TBranch* bFedId          = tree_->GetBranch("FedId");
    TBranch* bFeUnit         = tree_->GetBranch("FeUnit");
    TBranch* bFeChan         = tree_->GetBranch("FeChan");
    TBranch* bFeApv          = tree_->GetBranch("FeApv");

    //double   FecCrate        = 0.0;
    //double   Fec             = 0.0;
    //double   Ring            = 0.0;
    //double   Ccu             = 0.0;
    //double   I2CChannel      = 0.0;
    //double   lasChan         = 0.0;
    uint32_t FecKey          = 0;
    double   FedId           = 0.0;
    double   FeUnit          = 0.0;
    double   FeChan          = 0.0;
    double   FeApv           = 0.0;

    //bFecCrate      ->SetAddress(&FecCrate);
    //bFec           ->SetAddress(&Fec);
    //bRing          ->SetAddress(&Ring);
    //bCcu           ->SetAddress(&Ccu);
    //bI2CChannel    ->SetAddress(&I2CChannel);
    //blasChan       ->SetAddress(&lasChan);
    bFecKey        ->SetAddress(&FecKey);
    bFedId         ->SetAddress(&FedId);
    bFeUnit        ->SetAddress(&FeUnit);
    bFeChan        ->SetAddress(&FeChan);
    bFeApv         ->SetAddress(&FeApv);
    QMap<unsigned long, double> values;
    QMap<unsigned long, double> counts;

    for(Int_t i = 0; i < branchList->GetEntries(); ++i ) {
        TBranch *branch = static_cast<TBranch*>(branchList->At(i));
        if (!branch || !branch->GetLeaf(branch->GetName())) continue;
        if (varName_ != QString(branch->GetName())) continue;
        typeName = branch->GetLeaf(branch->GetName())->GetTypeName();
    }

    QMap<unsigned long, Chip*>::iterator it = modules.end();
    // the branch type is obviously correct, but the detid needn't be
    // a double (and maybe shouldn't be no matter what)
    unsigned long detid;
    int i2c;
    /*
    if      (varName_ == "Pedestal" || varName_ == "Noise") {
        tree_->SetBranchAddress(varName_.toStdString().c_str(), pedsvar);
        tree_->SetBranchAddress(varName_.toStdString().c_str(), noisevar);
    }
    */
    if      (varName_ == "Pedestal") tree_->SetBranchAddress("PedsMean", &dvar);
    else if (varName_ == "Noise") tree_->SetBranchAddress("NoiseMean", &dvar);
    else if (varName_ == "NoisyStrips") tree_->SetBranchAddress("Noisy", &dvar);
    else if (typeName == "UInt_t" || typeName == "unsigned" || typeName == "unsigned int") tree_->SetBranchAddress(varName_.toStdString().c_str(), &uvar);
    else if (typeName == "Int_t" || typeName == "int") tree_->SetBranchAddress(varName_.toStdString().c_str(), &ivar);
    else if (typeName == "Float_t" || typeName == "float") tree_->SetBranchAddress(varName_.toStdString().c_str(), &fvar);
    else if (typeName == "Double_t" || typeName == "double") tree_->SetBranchAddress(varName_.toStdString().c_str(), &dvar);
    else {
        std::cout << "Cannot identify branch type of the variable to be plotted on the TkMap\n"; 
        return;
    }

    tree_->SetBranchAddress("Detid",&did);
    tree_->SetBranchAddress("I2CAddress",&di2c);
    
    M::m()->nMin(rangeMin_);M::m()->nMax(rangeMax_);

    for(int i = 0; i < tree_->GetEntries(); i++) {
        if (smap[i] == 0) continue;
        tree_->GetEntry(i);
        detid = static_cast<unsigned long>(did);
        i2c = int(di2c);

        //uint16_t iFecCrate   = uint16_t(FecCrate);
        //uint16_t iFec        = uint16_t(Fec);
        //uint16_t iRing       = uint16_t(Ring);
        //uint16_t iCcu        = uint16_t(Ccu);
        //uint16_t iI2CChannel = uint16_t(I2CChannel);
        //uint16_t ilasChan    = uint16_t(lasChan);
        uint16_t iFedId      = uint16_t(FedId);        
        uint16_t iFeUnit     = uint16_t(FeUnit);        
        uint16_t iFeChan     = uint16_t(FeChan);        
        uint16_t iFeApv      = uint16_t(FeApv);

        SiStripFecKey feckey(FecKey-480);
        //SiStripFecKey feckey2(iFecCrate, iFec, iRing, iCcu, iI2CChannel, ilasChan+1, uint16_t(i2c));
        //if (feckey.key() != feckey2.key()) qDebug() << feckey.key() - feckey2.key();
        SiStripFedKey fedkey(iFedId, iFeUnit, iFeChan, iFeApv);

        it = modules.find(static_cast<unsigned long>(detid));
        if( it != modules.end() ) {
            if      (varName_ == "Pedestal" || varName_ == "Noise" || varName_ == "NoisyStrips") var = dvar;
            else if (typeName == "UInt_t" || typeName == "unsigned" || typeName == "unsigned int") var = double(uvar);
            else if (typeName == "Int_t" || typeName == "int") var = double(ivar);
            else if (typeName == "Float_t" || typeName == "float") var = double(fvar);
            else if (typeName == "Double_t" || typeName == "double") var = dvar;
            //if (varName_ == "Pedestal" || varName_ == "Noise") mapModule(it.value(), i2c, pedsvar, noisevar, feckey.key(), fedkey.key(), run_.toInt());
            //else mapModule(it.value(), i2c, var, feckey.key(), fedkey.key(), run_.toInt());
            mapModule(it.value(), i2c, var, feckey.key(), fedkey.key(), run_.toInt());
            if( values.find(detid) != values.end() ) { 
              values[detid] += var;
              counts[detid]++;
            } else {
              values.insert(detid,var);
              counts.insert(detid,1);
            }
        }
    }
    for(  QMap<unsigned long, double>::iterator ittt = values.begin() ; ittt != values.end(); ++ittt) {
        it = modules.find(ittt.key());
        if( it != modules.end() ) {
            ittt.value() /= counts[ittt.key()];
            it.value()->setValue(ittt.value());
            it.value()->setColor(QColor(getColor(ittt.value(),M::m()->max(),M::m()->min())));
        }
    }

  }

}

void TkMap::mapModule(Chip* c, int i2cadd, Double_t v, unsigned feckey, unsigned fedkey, int r) {
    Double_t stripnoise[128];
    for (int i = 0; i < 128; i++) stripnoise[i] = v;
    c->setAPVValue(i2cadd, v);
    c->setAPVStripNoiseValues(i2cadd,stripnoise);
    c->setAPVStripPedsValues(i2cadd,stripnoise);
    c->setAPVFecKey(i2cadd,feckey);
    c->setAPVFedKey(i2cadd,fedkey);
    c->setAPVColor(i2cadd, QColor(getColor(v,M::m()->max(),M::m()->min())));
    c->setRunNumber(r);
    c->showToolTip(true);
}

void TkMap::mapModule(Chip* c, int i2cadd, Double_t* p, Double_t* n, unsigned feckey, unsigned fedkey, int r) {
    Double_t strippeds[128];
    Double_t stripnoise[128];
    Double_t pedv = 0.;
    for (int i = 0; i < 128; i++) strippeds[i] = p[i];
    for (int i = 0; i < 128; i++) stripnoise[i] = n[i];
    for (int i = 0; i < 128; i++) pedv += strippeds[i];
    pedv/=128.0;

    c->setAPVValue(i2cadd, pedv);
    c->setAPVStripNoiseValues(i2cadd,stripnoise);
    c->setAPVStripPedsValues(i2cadd,stripnoise);
    c->setAPVFecKey(i2cadd,feckey);
    c->setAPVFedKey(i2cadd,fedkey);
    c->setAPVColor(i2cadd, QColor(getColor(pedv,M::m()->max(),M::m()->min())));
    c->setRunNumber(r);
    c->showToolTip(true);
}

void TkMap::printSelection() 
{
                  
  QList<QGraphicsItem*> fixedItems = scene->items();
  
  std::cout << "\nFixed Selection:\n==================" << std::endl;

  for( int i = 0; i < fixedItems.count(); ++i ) {
    Chip *item = dynamic_cast<Chip*>(fixedItems.at(i));
    if( !item ) continue;
    if( !item->fixStatus() ) continue;
    std::cout << item->getDetid() << '\t' << item->getValue() << std::endl;
  }


}


void TkMap::fixSelection()
{
  QList<QGraphicsItem*> items = scene->selectedItems();
  setSelection(items,true);
}


void TkMap::releaseSelection()
{
  QList<QGraphicsItem*> items = scene->selectedItems();
  if( items.count() == 0 ) 
    items = scene->items();
  setSelection(items,false);
}

void TkMap::setSelection(QList<QGraphicsItem*> &items, bool status)
{
  for( int i = 0; i < items.count(); ++i ) {
    Chip *item = dynamic_cast<Chip*>(items.at(i));
    if( !item ) continue;
    item->setFixStatus(status);
  }
  scene->clearSelection();
  if( view ) view->viewUpdate();
}
