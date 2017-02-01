/** \file global.hpp
 * Global function definitions and helper classes
 * This file contains functions which can be used from any of the
 * project classes. In addition it contains global singleton classes
 * to configure items independent of the thread it is used in
 */




#ifndef SELECTION_GLOBALS
#define SELECTION_GLOBALS

#include "TColor.h"
#include "TROOT.h"
#include "TStyle.h"


static const int kSubdetOffset       = 25; /**< offset to extract subdetector ID from detid */

/** 
 * An enum to define the various subdetectors in the strip tracker
 */
enum SubDetector 
  { 
    UNKNOWN = 0, /**< UNKNOWN subdetector (0) */
    TIB     = 3, /**< TIB subdetector offset (3)*/
    TID     = 4, /**< TID subdetector offset (4)*/
    TOB     = 5, /**< TOB subdetector offset (5)*/
    TEC     = 6, /**< TEC subdetector offset (6)*/
    TECM    = 7, /**< TECM subdetector offset (7)*/
    TECP    = 8  /**< TECP subdetector offset (8)*/
  };

/**
 * An enum to define the various geometries of the strip tracker modules
 */
enum ModuleGeometry {UNKNOWNGEOMETRY, IB1, IB2, OB1, OB2, W1A, W2A, W3A, W1B, W2B, W3B, W4, W5, W6, W7};

static const unsigned layerStartBit_ = 14;  /**< start bit to extract layer from detid */
static const unsigned layerMask_ = 0x7;     /**< mask to extract layer from detid */
static const unsigned ringStartBitTID_= 9;  /**< start bit to extract TID ring from detid */
static const unsigned ringMaskTID_= 0x3;    /**< mask to extract TID ring from detid */
static const unsigned ringStartBitTEC_= 5;  /**< start bit to extract TEC ring from detid */
static const unsigned ringMaskTEC_= 0x7;    /**< mask to extract TEC ring from detid */

/** 
 * inline method to extract subdet ID from detid
 */
inline int subdet(const unsigned int& id_) { return ((id_>>kSubdetOffset)&0x7); }

/** 
 * inline method to extract module geometry from detid
 */
inline int moduleGeometry(const unsigned int& id_)  
{
  switch(subdet(id_)) {
  case TIB: return int((id_>>layerStartBit_) & layerMask_)<3? IB1 : IB2;
  case TOB: return int((id_>>layerStartBit_) & layerMask_)<5? OB2 : OB1;
  case TID: switch ((id_>>ringStartBitTID_) & ringMaskTID_) {
    case 1: return W1A;
    case 2: return W2A;
    case 3: return W3A;
    }
  case TEC: switch ((id_>>ringStartBitTEC_) & ringMaskTEC_) {
    case 1: return W1B;
    case 2: return W2B;
    case 3: return W3B;
    case 4: return W4;
    case 5: return W5;
    case 6: return W6;
    case 7: return W7;
    }
  default: 
    return UNKNOWNGEOMETRY;
  } 
}

/**
 * inline method to get number of APVs for a given detid
 */
inline int nAPV(const unsigned int& id_)
{
  int geom = moduleGeometry(id_);
  if( geom == W1A || geom == W2A || //geom == W3A || 
      geom == W1B || geom == W2B || //geom == W3B || 
      geom == IB1 || geom == OB1 ) 
    return 6;
  else 
    return 4;
}


/*! \brief Singleton class to store constants */
class M
{

 public:
  /**
   * return instance
   */
  static M* m( ) { static M instance;; return &instance; }
  ~M( ) {};
  /**
   * get stored minimum
   */
  float min()   { return min_; }
  /**
   * get stored maximum
   */
  float max()   { return max_; }
  /**
   * get range between minimum and maximum
   */
  float range() { return range_; }
  /**
   * set new minimum
   */ 
  void nMin(float rhs) { min_ = rhs; range_ = max_ - min_; }
  /**
   * set new maximum
   */ 
  void nMax(float rhs) { max_ = rhs; range_ = max_ - min_; }
 private:
  M( ) {};
  float min_; /*!< minimum */
  float max_; /*!< maximum */
  float range_; /*!< range between minimum and maximum */
};

/**
 * inline method to get r,g,b color values for a value 
 * relies on #M singleton class
 * @param[in] value  
 * @param[out] r,g,b red green and blue color values (range [0:1])
 */
inline void getColor(float value, float &r , float &g, float &b) 
{
  gStyle->SetPalette(1);
  Int_t nColors = gStyle->GetNumberOfColors()-1;

  // value is zero
  if ( value < 1e-6 && value > -1e-6)   { 
    r = 1.0; g = 1.0; b = 1.0; 
    return; 
  } 
  // value is smaller than minimum of scale
  if( value < M::m()->min() ) {
    r=0.573333; g=0.0; b=1.0;
    return;
  }
  // value is greater than maximum of scale
  if( value > M::m()->max() ) {
    r=1.0; g=0.0; b=0.0;
    return;
  }
  
  Float_t stepsize = static_cast<Float_t>(nColors) / M::m()->range();
  // magic number 51 => default number of colors in the TPalette which consitute the 'rainbow'
  TColor *color = gROOT->GetColor(static_cast<Int_t>( (  value - M::m()->min() )  * stepsize + 51 ) ) ;
  if( !color  ) { r = 1.0; g = 1.0; b = 1.0; return; } 
  color->GetRGB(r,g,b);
  return;
}




#endif
