
#ifndef ConstantsForMonitorable_H
#define ConstantsForMonitorable_H

#include "Constants.h"
#include <string>

/** 
    @file ConstantsForMonitorable.h

    @brief Constants and enumerated types for sistrip::Monitorable
*/

namespace sistrip { 

  // ---------- Constants ---------- 

  // misc monitorables
  static const char unknownMonitorable_[]   = "UnknownMonitorable";
  static const char undefinedMonitorable_[] = "UndefinedMonitorable";
  
  // fed cabling
  static const char fedCablingFedId_[]    = "FedId";
  static const char fedCablingFedCh_[]    = "FedCh";
  static const char fedCablingAdcLevel_[] = "AdcLevel";

  // fast cabling
  static const char fastCablingDcuId_[]       = "DcuId";
  static const char fastCablingLldCh_[]       = "LldCh";
  static const char fastCablingHighLevel_[]   = "HighLightLevel";
  static const char fastCablingHighRms_[]     = "SpreadInHighLightLevel";
  static const char fastCablingLowLevel_[]    = "LowLightLevel";
  static const char fastCablingLowRms_[]      = "SpreadInLowLightLevel";
  static const char fastCablingAdcRange_[]    = "AdcRangeInLightLevel";
  static const char fastCablingMax_[]         = "MaximumLightLevel";
  static const char fastCablingMin_[]         = "MinimumLightLevel";
  static const char fastCablingConnsPerFed_[] = "ConnectionsPerFed";

  // timing
  static const char apvTimingTime_[]   = "TimeOfTickMarkEdge";
  static const char apvTimingMax_[]    = "MaxSamplingPoint";
  static const char apvTimingDelay_[]  = "RequiredDelayAdjustment";
  static const char apvTimingError_[]  = "ErrorOnTickMarkEdge";
  static const char apvTimingBase_[]   = "TickMarkBase";
  static const char apvTimingPeak_[]   = "TickMarkPeak";
  static const char apvTimingHeight_[] = "TickMarkHeight";

  // timing
  static const char fedTimingTime_[]   = "TimeOfTickMarkEdge";
  static const char fedTimingMax_[]    = "MaxSamplingPoint";
  static const char fedTimingDelay_[]  = "RequiredDelayAdjustment";
  static const char fedTimingError_[]  = "ErrorOnTickMarkEdge";
  static const char fedTimingBase_[]   = "TickMarkBase";
  static const char fedTimingPeak_[]   = "TickMarkPeak";
  static const char fedTimingHeight_[] = "TickMarkHeight";

  // opto scan
  static const char optoScanLldBias_[]     = "LldBiasSetting";
  static const char optoScanLldGain_[]     = "LldGainSetting";
  static const char optoScanMeasGain_[]    = "MeasuredGain";
  static const char optoScanZeroLight_[]   = "ZeroLightLevel";
  static const char optoScanLinkNoise_[]   = "LinkNoise";
  static const char optoScanBaseLiftOff_[] = "BaselineLiftOff";
  static const char optoScanLaserThresh_[] = "LaserThreshold";
  static const char optoScanTickHeight_[]  = "TickHeight";

  // vpsp scan
  static const char vpspScanBothApvs_[]    = "ApvVpspSettings";
  static const char vpspScanApv0_[]        = "Apv0VpspSetting";
  static const char vpspScanApv1_[]        = "Apv1VpspSetting";
  static const char vpspScanAdcLevel_[]    = "BaselineLevel";
  static const char vpspScanDigitalHigh_[] = "DigitalHigh";
  static const char vpspScanDigitalLow_[]  = "DigitalLow";

  // pedestals
  static const char pedestalsAllStrips_[] = "StripPedestals";
  static const char pedestalsMean_[]      = "PedestalMean";
  static const char pedestalsSpread_[]    = "PedestalRmsSpread";
  static const char pedestalsMax_[]       = "PedestalMax";
  static const char pedestalsMin_[]       = "PedestalMin";

  // noise
  static const char noiseAllStrips_[]       = "StripNoise";
  static const char noiseMean_[]            = "NoiseMean";
  static const char noiseSpread_[]          = "NoiseRmsSpread";
  static const char noiseMax_[]             = "NoiseMax";
  static const char noiseMin_[]             = "NoiseMin";
  static const char numOfDead_[]            = "NumOfDeadStrips";
  static const char numOfNoisy_[]           = "NumOfNoisyStrips";
  static const char noiseKSAllStrips_[]     = "StripNoiseKS";
  static const char noiseChi2AllStrips_[]   = "StripNoiseChi2";
  static const char noiseGausAllStrips_[]   = "StripNoiseGaus";
  static const char noiseBin84AllStrips_[]  = "StripNoiseBin84";
  static const char noiseRMSAllStrips_[]    = "StripNoiseRMS";
  static const char noiseSignif_[]  	    = "StripNoiseSignif";
  
  // Fine Delay
  static const char fineDelayPos_[]       = "FineDelayPosition";
  static const char fineDelayErr_[]       = "FineDelayError";

  // Calibration
  static const char calibrationAmplitude_[]    = "CalibrationAmplitude";
  static const char calibrationBaseline_[]     = "CalibrationBaseline";
  static const char calibrationTurnOn_[]       = "CalibrationTurnOn";
  static const char calibrationRiseTime_[]     = "CalibrationRiseTime";
  static const char calibrationDecayTime_[]    = "CalibrationDecayTime";
  static const char calibrationPeakTime_[]     = "CalibrationPeakTime";
  static const char calibrationUndershoot_[]   = "CalibrationUndershoot";
  static const char calibrationTail_[]         = "CalibrationTail";
  static const char calibrationSmearing_[]     = "CalibrationSmearing";
  static const char calibrationChi2_[]         = "CalibrationChi2";

  static const char calibrationAmplitudeMean_[]    = "MeanCalibrationAmplitude";
  static const char calibrationTurnOnMean_[]       = "MeanCalibrationTurnOn";
  static const char calibrationRiseTimeMean_[]     = "MeanCalibrationRiseTime";
  static const char calibrationDecayTimeMean_[]    = "MeanCalibrationDecayTime";
  static const char calibrationPeakTimeMean_[]     = "MeanCalibrationPeakTime";
  static const char calibrationBaselineMean_[]     = "MeanCalibrationBaseline";
  static const char calibrationUndershootMean_[]   = "MeanCalibrationUndershoot";
  static const char calibrationTailMean_[]         = "MeanCalibrationTail";
  static const char calibrationSmearingMean_[]     = "MeanCalibrationSmearing";
  static const char calibrationChi2Mean_[]         = "MeanCalibrationChi2";

  static const char calibrationAmplitudeMin_[]    = "MinCalibrationAmplitude";
  static const char calibrationTailMin_[]         = "MinCalibrationTail";
  static const char calibrationRiseTimeMin_[]     = "MinCalibrationRiseTime";
  static const char calibrationDecayTimeMin_[]    = "MinCalibrationDecayTime";
  static const char calibrationPeakTimeMin_[]     = "MinCalibrationPeakTime";
  static const char calibrationSmearingMin_[]     = "MinCalibrationSmearing";
  static const char calibrationTurnOnMin_[]       = "MinCalibrationTurnOn";
  static const char calibrationUndershootMin_[]   = "MinCalibrationUndershoot";
  static const char calibrationChi2Min_[]         = "MinCalibrationChi2";
  static const char calibrationBaselineMin_[]     = "MinCalibrationBaseline";

  static const char calibrationAmplitudeMax_[]    = "MaxCalibrationAmplitude";
  static const char calibrationTailMax_[]         = "MaxCalibrationTail";
  static const char calibrationRiseTimeMax_[]     = "MaxCalibrationRiseTime";
  static const char calibrationDecayTimeMax_[]    = "MaxCalibrationDecayTime";
  static const char calibrationPeakTimeMax_[]     = "MaxCalibrationPeakTime";
  static const char calibrationSmearingMax_[]     = "MaxCalibrationSmearing";
  static const char calibrationTurnOnMax_[]       = "MaxCalibrationTurnOn";
  static const char calibrationUndershootMax_[]   = "MaxCalibrationUndershoot";
  static const char calibrationChi2Max_[]         = "MaxCalibrationChi2";
  static const char calibrationBaselineMax_[]     = "MaxCalibrationBaseline";

  static const char calibrationAmplitudeSpread_[]    = "SpreadCalibrationAmplitude";
  static const char calibrationTailSpread_[]         = "SpreadCalibrationTail";
  static const char calibrationRiseTimeSpread_[]     = "SpreadCalibrationRiseTime";
  static const char calibrationDecayTimeSpread_[]    = "SpreadCalibrationDecayTime";
  static const char calibrationPeakTimeSpread_[]     = "SpreadCalibrationPeakTime";
  static const char calibrationSmearingSpread_[]     = "SpreadCalibrationSmearing";
  static const char calibrationTurnOnSpread_[]       = "SpreadCalibrationTurnOn";
  static const char calibrationUndershootSpread_[]   = "SpreadCalibrationUndershoot";
  static const char calibrationChi2Spread_[]         = "SpreadCalibrationChi2";
  static const char calibrationBaselineSpread_[]     = "SpreadCalibrationBaseline";

  static const char calibrationAmplitudeTuned_[]    = "TunedCalibrationAmplitude";
  static const char calibrationTailTuned_[]         = "TunedCalibrationTail";
  static const char calibrationRiseTimeTuned_[]     = "TunedCalibrationRiseTime";
  static const char calibrationDecayTimeTuned_[]    = "TunedCalibrationDecayTime";
  static const char calibrationPeakTimeTuned_[]     = "TunedCalibrationPeakTime";
  static const char calibrationSmearingTuned_[]     = "TunedCalibrationSmearing";
  static const char calibrationTurnOnTuned_[]       = "TunedCalibrationTurnOn";
  static const char calibrationUndershootTuned_[]   = "TunedCalibrationUndershoot";
  static const char calibrationChi2Tuned_[]         = "TunedCalibrationChi2";
  static const char calibrationBaselineTuned_[]     = "TunedCalibrationBaseline";
  static const char calibrationISHATuned_[]      = "TunedCalibrationISHA";
  static const char calibrationVFSTuned_[]       = "TunedCalibrationVFS";
  static const char calibrationISHABest_[]      = "BestCalibrationISHA";
  static const char calibrationVFSBest_[]       = "BestCalibrationVFS";

  
  // daq scope mode
  static const char daqScopeModeMeanSignal_[] = "DaqScopeMode_MeanSignal";

  // ---------- Enumerated type ---------- 

  /** Defines the monitorable for the summary histogram. */
  enum Monitorable { UNKNOWN_MONITORABLE   = sistrip::unknown_, 
		     UNDEFINED_MONITORABLE = sistrip::invalid_, 

		     FED_CABLING_FED_ID    = 1301, 
		     FED_CABLING_FED_CH    = 1302, 
		     FED_CABLING_ADC_LEVEL = 1303, 

		     FAST_CABLING_DCU_ID        = 2101, 
		     FAST_CABLING_LLD_CH        = 2102, 
		     FAST_CABLING_HIGH_LEVEL    = 2103, 
		     FAST_CABLING_LOW_LEVEL     = 2104, 
		     FAST_CABLING_HIGH_RMS      = 2105, 
		     FAST_CABLING_LOW_RMS       = 2106, 
		     FAST_CABLING_MAX           = 2107, 
		     FAST_CABLING_MIN           = 2108, 
		     FAST_CABLING_CONNS_PER_FED = 2109, 

		     APV_TIMING_TIME     = 501, 
		     APV_TIMING_MAX_TIME = 502, 
		     APV_TIMING_DELAY    = 503, 
		     APV_TIMING_ERROR    = 504, 
		     APV_TIMING_BASE     = 505, 
		     APV_TIMING_PEAK     = 506, 
		     APV_TIMING_HEIGHT   = 507,

		     FED_TIMING_TIME     = 1201, 
		     FED_TIMING_MAX_TIME = 1202, 
		     FED_TIMING_DELAY    = 1203, 
		     FED_TIMING_ERROR    = 1204, 
		     FED_TIMING_BASE     = 1205, 
		     FED_TIMING_PEAK     = 1206, 
		     FED_TIMING_HEIGHT   = 1207,
		     OPTO_SCAN_LLD_GAIN_SETTING  = 401,
		     OPTO_SCAN_LLD_BIAS_SETTING  = 402,
		     OPTO_SCAN_MEASURED_GAIN     = 403, 
		     OPTO_SCAN_ZERO_LIGHT_LEVEL  = 404, 
		     OPTO_SCAN_LINK_NOISE        = 405,
		     OPTO_SCAN_BASELINE_LIFT_OFF = 406,
		     OPTO_SCAN_LASER_THRESHOLD   = 407,  
		     OPTO_SCAN_TICK_HEIGHT       = 408,

		     VPSP_SCAN_APV_SETTINGS = 1401, 
		     VPSP_SCAN_APV0_SETTING = 1402, 
		     VPSP_SCAN_APV1_SETTING = 1403, 
		     VPSP_SCAN_ADC_LEVEL    = 1404, 
		     VPSP_SCAN_DIGITAL_HIGH = 1405, 
		     VPSP_SCAN_DIGITAL_LOW  = 1406, 

		     PEDESTALS_ALL_STRIPS = 201, 
		     PEDESTALS_MEAN       = 202, 
		     PEDESTALS_SPREAD     = 203, 
		     PEDESTALS_MAX        = 204, 
		     PEDESTALS_MIN        = 205, 

		     NOISE_ALL_STRIPS = 206, 
		     NOISE_MEAN       = 207, 
		     NOISE_SPREAD     = 208, 
		     NOISE_MAX        = 209, 
		     NOISE_MIN        = 210, 
		     NUM_OF_DEAD      = 211, 
		     NUM_OF_NOISY     = 212,
		     NOISE_KS_ALL_STRIPS 	= 215,
		     NOISE_GAUS_ALL_STRIPS  = 216,
		     NOISE_BIN_84_ALL_STRIPS= 217,
		     NOISE_CHI2_ALL_STRIPS 	= 218,
		     NOISE_SIGNIF_ALL_STRIPS= 219,
		     NOISE_RMS_ALL_STRIPS 	= 220,
		     FINE_DELAY_POS 		= 601,
		     FINE_DELAY_ERROR 		= 602,

		     CALIBRATION_AMPLITUDE_MEAN    = 701,
		     CALIBRATION_BASELINE_MEAN     = 702,
		     CALIBRATION_TURNON_MEAN       = 703,
		     CALIBRATION_RISETIME_MEAN     = 704,
		     CALIBRATION_DECAYTIME_MEAN    = 705,
		     CALIBRATION_PEAKTIME_MEAN     = 706,
		     CALIBRATION_UNDERSHOOT_MEAN   = 707,
		     CALIBRATION_TAIL_MEAN         = 708,
		     CALIBRATION_SMEARING_MEAN     = 709,
		     CALIBRATION_CHI2_MEAN         = 710,
		     
		     CALIBRATION_AMPLITUDE_ALL_STRIPS    = 711,
		     CALIBRATION_BASELINE_ALL_STRIPS     = 712,
		     CALIBRATION_TURNON_ALL_STRIPS       = 713,
		     CALIBRATION_RISETIME_ALL_STRIPS     = 714,
		     CALIBRATION_DECAYTIME_ALL_STRIPS    = 715,
		     CALIBRATION_PEAKTIME_ALL_STRIPS     = 716,
		     CALIBRATION_UNDERSHOOT_ALL_STRIPS   = 717,
		     CALIBRATION_TAIL_ALL_STRIPS         = 718,
		     CALIBRATION_SMEARING_ALL_STRIPS     = 719,
		     CALIBRATION_CHI2_ALL_STRIPS         = 720,
  
		     CALIBRATION_AMPLITUDE_MIN    = 721,
		     CALIBRATION_BASELINE_MIN     = 722,
		     CALIBRATION_TURNON_MIN       = 723,
		     CALIBRATION_RISETIME_MIN     = 724,
		     CALIBRATION_DECAYTIME_MIN    = 725,
		     CALIBRATION_PEAKTIME_MIN     = 726,
		     CALIBRATION_UNDERSHOOT_MIN   = 727,
		     CALIBRATION_TAIL_MIN         = 728,
		     CALIBRATION_SMEARING_MIN     = 729,
		     CALIBRATION_CHI2_MIN         = 730,
  
		     CALIBRATION_AMPLITUDE_MAX    = 731,
		     CALIBRATION_BASELINE_MAX     = 732,
		     CALIBRATION_TURNON_MAX       = 733,
		     CALIBRATION_RISETIME_MAX     = 734,
		     CALIBRATION_DECAYTIME_MAX    = 735,
		     CALIBRATION_PEAKTIME_MAX     = 736,
		     CALIBRATION_UNDERSHOOT_MAX   = 737,
		     CALIBRATION_TAIL_MAX         = 738,
		     CALIBRATION_SMEARING_MAX     = 739,
		     CALIBRATION_CHI2_MAX         = 740,

		     CALIBRATION_AMPLITUDE_SPREAD    = 741,
		     CALIBRATION_BASELINE_SPREAD     = 742,
		     CALIBRATION_TURNON_SPREAD       = 743,
		     CALIBRATION_RISETIME_SPREAD     = 744,
		     CALIBRATION_DECAYTIME_SPREAD    = 745,
		     CALIBRATION_PEAKTIME_SPREAD     = 746,
		     CALIBRATION_UNDERSHOOT_SPREAD   = 747,
		     CALIBRATION_TAIL_SPREAD         = 748,
		     CALIBRATION_SMEARING_SPREAD     = 749,
		     CALIBRATION_CHI2_SPREAD         = 750,

		     CALIBRATION_AMPLITUDE_TUNED    = 751,
		     CALIBRATION_BASELINE_TUNED     = 752,
		     CALIBRATION_TURNON_TUNED       = 753,
		     CALIBRATION_RISETIME_TUNED     = 754,
		     CALIBRATION_DECAYTIME_TUNED    = 755,
		     CALIBRATION_PEAKTIME_TUNED     = 756,
		     CALIBRATION_UNDERSHOOT_TUNED   = 757,
		     CALIBRATION_TAIL_TUNED         = 758,
		     CALIBRATION_SMEARING_TUNED     = 759,
		     CALIBRATION_CHI2_TUNED         = 760,
		     CALIBRATION_ISHA_TUNED         = 761,
		     CALIBRATION_VFS_TUNED          = 762,
		     CALIBRATION_ISHA_BEST          = 763,
		     CALIBRATION_VFS_BEST           = 764,

  
		     DAQ_SCOPE_MODE_MEAN_SIGNAL = 1501
  };

}
  
#endif // ConstantsForMonitorable_H
