#ifndef TREEBUILDER_H
#define TREEBUILDER_H

#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <sstream>
#include "BaseTypes.h"

// copying enum from CMSSW in order to not have any specific
// dependency. 
namespace sistrip {
    enum RunType { 
        PHYSICS               = 1,
        PEDESTALS             = 2,
        CALIBRATION           = 3,
        OPTO_SCAN             = 4,
        APV_TIMING            = 5,
        APV_LATENCY           = 6,
        FINE_DELAY_PLL        = 7,
        FINE_DELAY_TTC        = 8,
        MULTI_MODE            = 10,
        FED_TIMING            = 12,
        FED_CABLING           = 13,
        VPSP_SCAN             = 14,
        DAQ_SCOPE_MODE        = 15,
        QUITE_FAST_CABLING    = 16,
        FINE_DELAY            = 17,
        PHYSICS_ZS            = 18,
        CALIBRATION_SCAN      = 19,
        CALIBRATION_SCAN_DECO = 20,
        FAST_CABLING          = 21,
        PEDS_ONLY             = 22,
        NOISE                 = 23,
        PEDS_FULL_NOISE       = 24,
        CALIBRATION_DECO      = 33,
        UNKNOWN_RUN_TYPE      = 99,
        CURRENTSTATE          = 137, // fake run mode added for current state retrieval 
        LASTO2O               = 138, // fake run mode added for current state retrieval 
        UNDEFINED_RUN_TYPE    = 65535
    };
}


/** \Class TreeBuilder 
 * 
 * Singleton class to provide single source to access trees to
 * visualize commissioning data
 *
 */ 
class TreeBuilder {
    public:
        typedef QPair<QString,QString> QRunId; /**< unique ID of a run consisting of partition name and run number */
        
        /**
         * return instance of #TreeBuilder
         */
        static TreeBuilder* Inst();
        ~TreeBuilder();
        
        /**
         * transform a run type given as string into an integer as defined
         * in sistrip::RunType
         */
        int     iRunType(const std::string &runType);
        /**
         * method to resolve ambiguities in run type naming in different
         * sources
         */ 
        QString sRunType(const QString & analysisType);
        /**
         * try to add a file to the map of files associated with a given run
         * ID. Reports the success/non success of this operation
         */ 
        bool    buildTree(const QString& filename, const QString &analysisType, const QString &analysisId, const QRunId& runId, bool useCache=false);
        /**
         * try to add a file to the map of files associated with a given run
         * ID. Reports the success/non success of this operation. Calls 
         * buildTree(const QString &analysisType, const QString &analysisId, const QRunId& runId)
         */ 
        bool    buildTree(const QString& filename, const QString &analysisType, const QString &analysisId, const QString &partitionName, const QString &runNumber, bool useCache=false);
        /**
         * load analysis for a given run number and partition.
         */
        QString loadAnalysis(const QRunId &runId, bool useCache=false);
        /**
         * load analysis for a given run number and partition.
         * Calls loadAnalysis(const QRunId &runId );
         */ 
        QString loadAnalysis(const QString& partitionName, const QString& runNumber, bool useCache=false);
        
        /**
         * retrieve the current state FED values for the indicated partition
         */ 
        bool getState(const QString &partitionName, int state);

        
    protected:
        TreeBuilder();
  
    private:
        static TreeBuilder* pInstance;
       
        /* 
        std::map< QRunId, TFile* > fileMap;
        std::map< QRunId, TTree* > treeMap;
        std::map< QRunId, bool >   treeInUse;
        */        

        /**
         * Create and fill a tree for a given run number and run type. The
         * query used to retrieve the data is passed as argument.
         */
        void fillTree(TTree* tree, std::string runType, const std::string& theQuery,int analysisId);
        /**
         * get the query to retrieve information for a given run type and a
         * given analysis id
         */
        std::string getQuery(const QString& runType);
  
};
#endif
