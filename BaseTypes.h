#ifndef BASETYPES_H
#define BASETYPES_H

// There is no good implementation of std::make_pair in Qt. So I am sticking with the standard C++ container here
#include <vector>
#include <string>

// Qt includes
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QVector>
#include <QRegExp>
#include <QStringList>

// ROOT includes
#include <TObjString.h>

// Debugging output
#include "Debug.h"

/** \Struct Base_Type
 * 
 * abstract base struct for TTree branch handling and filling
 */
struct Base_Type {
    virtual ~Base_Type() {
    }

    virtual void setFromResultset(const QSqlQuery& rs, int field_no) = 0;
};

/** \Struct String
 * 
 * struct to handle TObjString branches 
 */
struct String : public Base_Type {
    /**
     * Default constructor. Initialize to 0
     */
    String(): 
        Base_Type(), 
        value(0) 
    { 
    }

    /**
     * Initialize from std::string
     */ 

    String(std::string v): 
        Base_Type() 
    {
        value = new TObjString(v.c_str());
    }

    /**
     * Initialize from char*
     */ 
    String(char* v): 
        Base_Type() 
    {
        value = new TObjString(v);
    }

    ~String() {
    }
    
    virtual void setFromResultset(const QSqlQuery& rs, int field_no) { 
        value = new TObjString(Form("%s",rs.value(field_no).toString().toStdString().c_str() ) );
    }
    
    TObjString* value;
};

/** \Struct Double
 *
 * struct to handle double branches
 */ 
struct Double : public Base_Type {
    Double() {
    }

    Double(double v): 
        Base_Type(), 
        value(v) 
    {
    }
    
    virtual void setFromResultset(const QSqlQuery& rs, int field_no) { 
        value = rs.value(field_no).toDouble();
    }
    
    double value;
};

/** \Struct Integer
 *
 * struct to handle integer branches
 */ 
struct Integer : public Base_Type {
    Integer() {
    }

    Integer(int v): 
        Base_Type(), 
        value(v) 
    {
    }
    
    virtual void setFromResultset(const QSqlQuery& rs, int field_no) { 
        value = rs.value(field_no).toInt();
    }
    
    unsigned int value;
};

struct IntFromStringMap : public Base_Type {
    IntFromStringMap() {
        svalue = "";
        value = 0;
    }

    IntFromStringMap(QString v):
        Base_Type(),
        svalue(v)
    {
        value = getIntFromStringMap(svalue);
    }

    virtual void setFromResultset(const QSqlQuery& rs, int field_no) {
        svalue = rs.value(field_no).toString();
        value  = getIntFromStringMap(svalue);
    }

    int getIntFromStringMap(QString s) {
        QRegExp rx("(\\|)");
        QStringList query = s.split(rx);
        bool has_only_digits = false;
        int val = 0;
        foreach(QString str, query) {
            std::string is = str.toStdString();
            has_only_digits = (is.find_first_not_of( "0123456789" ) == std::string::npos);
            if(has_only_digits){
                val += str.toInt();
            }
        }
        return val;
    }

    QString svalue;
    int value;
};


/** \Struct BaseQuery
 *
 * struct to store the branch structure of a database query for a
 * given run type
 */
struct BaseQuery {
    
    QVector<std::pair<std::string, Base_Type* > > query;
    
    BaseQuery() {
        query.push_back(std::make_pair("Detector"       , new String() ) );
        query.push_back(std::make_pair("Side"	        , new Double() ) );
        query.push_back(std::make_pair("Layer"  	    , new Double() ) );
        query.push_back(std::make_pair("Cl"	            , new Double() ) );
        query.push_back(std::make_pair("Cr"	            , new Double() ) );
        query.push_back(std::make_pair("Power"  	    , new Double() ) );
        query.push_back(std::make_pair("Mod"    	    , new Double() ) );
        query.push_back(std::make_pair("Rack"   	    , new String() ) );
        query.push_back(std::make_pair("Crate"  	    , new Double() ) );
        query.push_back(std::make_pair("Slot"   	    , new Double() ) );
        query.push_back(std::make_pair("PP1"    	    , new String() ) );
        query.push_back(std::make_pair("Stack"  	    , new Double() ) );
        query.push_back(std::make_pair("Place"  	    , new Double() ) );
        query.push_back(std::make_pair("Detid"  	    , new Double() ) );
        query.push_back(std::make_pair("Dcu"    	    , new Double() ) );
        query.push_back(std::make_pair("FecCrate"       , new Double() ) );
        query.push_back(std::make_pair("Fec"    	    , new Double() ) );
        query.push_back(std::make_pair("Ring"   	    , new Double() ) );
        query.push_back(std::make_pair("Ccu"    	    , new Double() ) );
        query.push_back(std::make_pair("CcuArrangement" , new Double() ) );
        query.push_back(std::make_pair("I2CChannel"     , new Double() ) );
        query.push_back(std::make_pair("FecKey"         , new Integer()) );
        query.push_back(std::make_pair("I2CAddress"     , new Double() ) );
        query.push_back(std::make_pair("lasChan"        , new Double() ) );  
    }
    
    void setExtendedQuery(const std::string& runType) {
        if(runType == "TIMING") {
            query.push_back(std::make_pair("DeviceId"   , new Double() ) );
            query.push_back(std::make_pair("FedId"      , new Double() ) );
            query.push_back(std::make_pair("FeUnit"     , new Double() ) );
            query.push_back(std::make_pair("FeChan"     , new Double() ) );
            query.push_back(std::make_pair("FeApv"      , new Double() ) );
            query.push_back(std::make_pair("TickHeight" , new Double() ) );
            query.push_back(std::make_pair("Delay"      , new Double() ) );
            query.push_back(std::make_pair("Base"       , new Double() ) );  
            query.push_back(std::make_pair("Peak"       , new Double() ) );  
            query.push_back(std::make_pair("Kind"       , new Double() ) );  
            query.push_back(std::make_pair("IsValid"    , new Double() ) );
        } 
        else if (runType == "GAINSCAN" || runType == "OPTOSCAN") { // use both notations
            query.push_back(std::make_pair("DeviceId",            new Double() ) );
            query.push_back(std::make_pair("FedId",               new Double() ) );
            query.push_back(std::make_pair("FeUnit",              new Double() ) );
            query.push_back(std::make_pair("FeChan",              new Double() ) );
            query.push_back(std::make_pair("FeApv",               new Double() ) );
            query.push_back(std::make_pair("Gain",                new Double() ) );
            query.push_back(std::make_pair("Bias0",               new Double() ) );
            query.push_back(std::make_pair("Bias1",               new Double() ) );
            query.push_back(std::make_pair("Bias2",               new Double() ) );
            query.push_back(std::make_pair("Bias3",               new Double() ) );
            query.push_back(std::make_pair("SelectedBias",        new Double() ) );
            query.push_back(std::make_pair("Measgain0",           new Double() ) );
            query.push_back(std::make_pair("Measgain1",           new Double() ) );
            query.push_back(std::make_pair("Measgain2",           new Double() ) );
            query.push_back(std::make_pair("Measgain3",           new Double() ) );
            query.push_back(std::make_pair("SelectedMeasgain",    new Double() ) );
            query.push_back(std::make_pair("Zerolight0",          new Double() ) );
            query.push_back(std::make_pair("Zerolight1",          new Double() ) );
            query.push_back(std::make_pair("Zerolight2",          new Double() ) );
            query.push_back(std::make_pair("Zerolight3",          new Double() ) );
            query.push_back(std::make_pair("SelectedZerolight",   new Double() ) );
            query.push_back(std::make_pair("Linknoise0",          new Double() ) );
            query.push_back(std::make_pair("Linknoise1",          new Double() ) );
            query.push_back(std::make_pair("Linknoise2",          new Double() ) );
            query.push_back(std::make_pair("Linknoise3",          new Double() ) );
            query.push_back(std::make_pair("SelectedLinknoise",   new Double() ) );
            query.push_back(std::make_pair("Liftoff0",            new Double() ) );
            query.push_back(std::make_pair("Liftoff1",            new Double() ) );
            query.push_back(std::make_pair("Liftoff2",            new Double() ) );
            query.push_back(std::make_pair("Liftoff3",            new Double() ) );
            query.push_back(std::make_pair("SelectedLiftoff",     new Double() ) );
            query.push_back(std::make_pair("Threshold0",          new Double() ) );
            query.push_back(std::make_pair("Threshold1",          new Double() ) );
            query.push_back(std::make_pair("Threshold2",          new Double() ) );
            query.push_back(std::make_pair("Threshold3",          new Double() ) );
            query.push_back(std::make_pair("SelectedThreshold",   new Double() ) );
            query.push_back(std::make_pair("Tickheight0",         new Double() ) );
            query.push_back(std::make_pair("Tickheight1",         new Double() ) );
            query.push_back(std::make_pair("Tickheight2",         new Double() ) );
            query.push_back(std::make_pair("Tickheight3",         new Double() ) );
            query.push_back(std::make_pair("SelectedTickheight",  new Double() ) );
            query.push_back(std::make_pair("Isvalid",             new Double() ) );
            query.push_back(std::make_pair("Baselineslop0",       new Double() ) );
            query.push_back(std::make_pair("Baselineslop1",       new Double() ) );
            query.push_back(std::make_pair("Baselineslop2",       new Double() ) );
            query.push_back(std::make_pair("Baselineslop3",       new Double() ) );
            query.push_back(std::make_pair("SelectedBaselineslop",new Double() ) );
            query.push_back(std::make_pair("NormTick0",           new Double() ) );
            query.push_back(std::make_pair("NormTick1",           new Double() ) );
            query.push_back(std::make_pair("NormTick2",           new Double() ) );
            query.push_back(std::make_pair("NormTick3",           new Double() ) );
        } 
        else if(runType == "VPSPSCAN") {
            query.push_back(std::make_pair("DeviceId",      new Double() ) );
            query.push_back(std::make_pair("FedId",         new Double() ) );
            query.push_back(std::make_pair("FeUnit",        new Double() ) );
            query.push_back(std::make_pair("FeChan",        new Double() ) );
            query.push_back(std::make_pair("FeApv",         new Double() ) );
            query.push_back(std::make_pair("Vpsp",          new Double() ) );
            query.push_back(std::make_pair("Adclevel",      new Double() ) );
            query.push_back(std::make_pair("Fraction",      new Double() ) );
            query.push_back(std::make_pair("Topedge",       new Double() ) );
            query.push_back(std::make_pair("Bottomedge",    new Double() ) );
            query.push_back(std::make_pair("Toplevel",      new Double() ) );
            query.push_back(std::make_pair("Bottomlevel",   new Double() ) );
            query.push_back(std::make_pair("Isvalid",       new Double() ) );
        } 
        else if(runType == "VERY_FAST_CONNECTION" || runType == "FASTFEDCABLING") {
            query.push_back(std::make_pair("DeviceId"  ,    new Double() ) );
            query.push_back(std::make_pair("FedId"     ,    new Double() ) );
            query.push_back(std::make_pair("FeUnit"    ,    new Double() ) );
            query.push_back(std::make_pair("FeChan"    ,    new Double() ) );
            query.push_back(std::make_pair("FeApv"     ,    new Double() ) );
            query.push_back(std::make_pair("Highlevel" ,    new Double() ) );
            query.push_back(std::make_pair("Highrms"   ,    new Double() ) );
            query.push_back(std::make_pair("Lowlevel"  ,    new Double() ) );
            query.push_back(std::make_pair("Lowrms"    ,    new Double() ) );
            query.push_back(std::make_pair("Maxll"     ,    new Double() ) );
            query.push_back(std::make_pair("Minll"     ,    new Double() ) );
            query.push_back(std::make_pair("Dcuid"     ,    new Double() ) );
            query.push_back(std::make_pair("Lldch"     ,    new Double() ) );
            query.push_back(std::make_pair("Isvalid"   ,    new Double() ) );
            query.push_back(std::make_pair("Isdirty"   ,    new Double() ) );
        } 
        else if(runType == "PEDESTALS" || runType == "PEDESTAL") {
            query.push_back(std::make_pair("DeviceId",      new Double() ) );
            query.push_back(std::make_pair("FedId",         new Double() ) );
            query.push_back(std::make_pair("FeUnit",        new Double() ) );
            query.push_back(std::make_pair("FeChan",        new Double() ) );
            query.push_back(std::make_pair("FeApv",         new Double() ) );
            query.push_back(std::make_pair("PedsMean",      new Double() ) );
            query.push_back(std::make_pair("PedsSpread",    new Double() ) );
            query.push_back(std::make_pair("NoiseMean",     new Double() ) );
            query.push_back(std::make_pair("NoiseSpread",   new Double() ) );
            query.push_back(std::make_pair("RawMean",       new Double() ) );
            query.push_back(std::make_pair("RawSpread",     new Double() ) );
            query.push_back(std::make_pair("PedsMax",       new Double() ) );
            query.push_back(std::make_pair("PedsMin",       new Double() ) );
            query.push_back(std::make_pair("NoiseMax",      new Double() ) );
            query.push_back(std::make_pair("NoiseMin",      new Double() ) );
            query.push_back(std::make_pair("RawMax",        new Double() ) );
            query.push_back(std::make_pair("RawMin",        new Double() ) );
            query.push_back(std::make_pair("IsValid",       new Double() ) );
            query.push_back(std::make_pair("Dead"   ,       new IntFromStringMap() ) );
            query.push_back(std::make_pair("Noisy",         new IntFromStringMap() ) );
        } 
        else if(runType == "CALIBRATION" || runType == "CALIBRATION_DECO" || runType == "CALIBRATION_SCAN_DECO" || runType == "CALIBRATION_SCAN") {
            query.push_back(std::make_pair("DeviceId",      new Double() ) );
            query.push_back(std::make_pair("FedId",         new Double() ) );
            query.push_back(std::make_pair("FeUnit",        new Double() ) );
            query.push_back(std::make_pair("FeChan",        new Double() ) );
            query.push_back(std::make_pair("FeApv",         new Double() ) );
            query.push_back(std::make_pair("Amplitude",     new Double() ) );
            query.push_back(std::make_pair("Tail",          new Double() ) );
            query.push_back(std::make_pair("RiseTime",      new Double() ) );
            query.push_back(std::make_pair("TimeConstant",  new Double() ) );
            query.push_back(std::make_pair("Smearing",      new Double() ) );
            query.push_back(std::make_pair("Chi2",          new Double() ) );
            query.push_back(std::make_pair("DeconvMode",    new Double() ) );
            query.push_back(std::make_pair("IsValid",       new Double() ) );
        } 
        else if(runType == "SCOPE") {
            query.push_back(std::make_pair("DeviceId"   , new Double() ) );
            query.push_back(std::make_pair("FedId"      , new Double() ) );
            query.push_back(std::make_pair("FeUnit"     , new Double() ) );
            query.push_back(std::make_pair("FeChan"     , new Double() ) );
            query.push_back(std::make_pair("FeApv"      , new Double() ) );
            query.push_back(std::make_pair("TickHeight" , new Double() ) );
            query.push_back(std::make_pair("Delay"      , new Double() ) );
            query.push_back(std::make_pair("Base"       , new Double() ) );  
            query.push_back(std::make_pair("Peak"       , new Double() ) );  
            query.push_back(std::make_pair("Kind"       , new Double() ) );  
            query.push_back(std::make_pair("IsValid"    , new Double() ) );
            query.push_back(std::make_pair("PedsMean",      new Double() ) );
            query.push_back(std::make_pair("PedsSpread",    new Double() ) );
            query.push_back(std::make_pair("NoiseMean",     new Double() ) );
            query.push_back(std::make_pair("NoiseSpread",   new Double() ) );
            query.push_back(std::make_pair("RawMean",       new Double() ) );
            query.push_back(std::make_pair("RawSpread",     new Double() ) );
            query.push_back(std::make_pair("PedsMax",       new Double() ) );
            query.push_back(std::make_pair("PedsMin",       new Double() ) );
            query.push_back(std::make_pair("NoiseMax",      new Double() ) );
            query.push_back(std::make_pair("NoiseMin",      new Double() ) );
            query.push_back(std::make_pair("RawMax",        new Double() ) );
            query.push_back(std::make_pair("RawMin",        new Double() ) );
            query.push_back(std::make_pair("Dead"   ,       new IntFromStringMap() ) );
            query.push_back(std::make_pair("Noisy",         new IntFromStringMap() ) );
        } 
        else if(runType == "ENC_PEDESTAL") {
            query.pop_back(); // remove IsValid from the end
            query.push_back(std::make_pair("PedsMeanENC",      new Double() ) );
            query.push_back(std::make_pair("PedsSpreadENC",    new Double() ) );
            query.push_back(std::make_pair("NoiseMeanENC",     new Double() ) );
            query.push_back(std::make_pair("NoiseSpreadENC",   new Double() ) );
            query.push_back(std::make_pair("RawMeanENC",       new Double() ) );
            query.push_back(std::make_pair("RawSpreadENC",     new Double() ) );
            query.push_back(std::make_pair("PedsMaxENC",       new Double() ) );
            query.push_back(std::make_pair("PedsMinENC",       new Double() ) );
            query.push_back(std::make_pair("NoiseMaxENC",      new Double() ) );
            query.push_back(std::make_pair("NoiseMinENC",      new Double() ) );
            query.push_back(std::make_pair("RawMaxENC",        new Double() ) );
            query.push_back(std::make_pair("RawMinENC",        new Double() ) );
            query.push_back(std::make_pair("IsValid",          new Double() ) );
        } 
    }
};
#endif
