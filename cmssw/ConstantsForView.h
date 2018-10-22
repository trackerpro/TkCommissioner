#ifndef ConstantsForView_H
#define ConstantsForView_H

#include "Constants.h"
#include <string>

/** 
    @file ConstantsForView.h

    @brief Constants and enumerated types for sistrip::View
*/

namespace sistrip { 

  // ---------- Constants ---------- 

  static const char unknownView_[]   = "UnknownView";
  static const char undefinedView_[] = "UndefinedView";
  
  static const char readoutView_[]   = "ReadoutView";
  static const char controlView_[]   = "ControlView";
  static const char detectorView_[]  = "DetectorView";
  
  // ---------- Enumerated type ---------- 

  enum View { UNKNOWN_VIEW   = sistrip::unknown_, 
	      UNDEFINED_VIEW = sistrip::invalid_, 
	      READOUT_VIEW   = 1, 
	      CONTROL_VIEW   = 2, 
	      DETECTOR_VIEW  = 3 
  };
  
}
  
#endif // ConstantsForView_H


