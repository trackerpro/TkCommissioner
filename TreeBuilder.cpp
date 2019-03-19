// project includes
#include "TreeBuilder.h"
#include "Debug.h"
#include "DbConnection.h"
#include <stdint.h>

#include <QApplication>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QProgressDialog>
#include <QThread>
#include <QFile>
#include <QMap>
#include <QVector>
#include <QPair>
#include <QString>
#include <QtSql>

TreeBuilder* TreeBuilder::pInstance = 0;

TreeBuilder* TreeBuilder::Inst() {
    if(pInstance == 0) pInstance = new TreeBuilder();
    return pInstance;
}


TreeBuilder::TreeBuilder() {
}

TreeBuilder::~TreeBuilder() {
    if(pInstance != 0) delete pInstance;
}

int TreeBuilder::iRunType(const std::string &analysisType) {
  if (analysisType      == "TIMING") return sistrip::APV_TIMING;
  else if (analysisType == "OPTOSCAN" || analysisType == "GAINSCAN") return sistrip::OPTO_SCAN;
  else if(analysisType  == "VPSPSCAN") return sistrip::VPSP_SCAN;
  else if(analysisType  == "VERY_FAST_CONNECTION" || analysisType == "FASTFEDCABLING" ) return sistrip::FAST_CABLING;
  else if(analysisType  == "PEDESTALS" || analysisType == "PEDESTAL") return  sistrip::PEDESTALS;    
  else if(analysisType  == "CALIBRATION") return  sistrip::CALIBRATION;    
  else if(analysisType  == "CALIBRATION_DECO") return  sistrip::CALIBRATION_DECO;    
  else if(analysisType  == "CALIBRATION_SCAN") return  sistrip::CALIBRATION_SCAN;    
  else if(analysisType  == "CALIBRATION_SCAN_DECO") return  sistrip::CALIBRATION_SCAN_DECO;    
  else if(analysisType  == "CURRENT" || analysisType == "CURRENTSTATE" ) return sistrip::CURRENTSTATE;
  else {
    if(Debug::Inst()->getEnabled()) qDebug() << "Unknown Run Type: " << analysisType.c_str() << "!";
    return sistrip::UNKNOWN_RUN_TYPE;
  }
}

QString TreeBuilder::sRunType(const QString & analysisType) {
  if (analysisType      == "TIMING") return QString("TIMING");
  else if (analysisType == "OPTOSCAN" || analysisType == "GAINSCAN") return QString("OPTOSCAN");
  else if(analysisType  == "VPSPSCAN") return QString("VPSPSCAN");
  else if(analysisType  == "VERY_FAST_CONNECTION" || analysisType == "FASTFEDCABLING" ) return QString("FASTFEDCABLING");
  else if(analysisType  == "PEDESTALS" || analysisType == "PEDESTAL") return QString("PEDESTALS");
  else if(analysisType  == "CALIBRATION") return  QString("CALIBRATION");    
  else if(analysisType  == "CALIBRATION_DECO") return  QString("CALIBRATION_DECO");    
  else if(analysisType  == "CALIBRATION_SCAN") return  QString("CALIBRATION_SCAN");    
  else if(analysisType  == "CALIBRATION_SCAN_DECO") return  QString("CALIBRATION_SCAN_DECO");    
  else if(analysisType  == "CURRENT" || analysisType == "CURRENTSTATE" ) return QString("CURRENT");
  else {
    if(Debug::Inst()->getEnabled()) qDebug() << "Unknown Run Type: " << qPrintable(analysisType) << "!";
    return QString("UNKNOWN");
  }    
}

bool TreeBuilder::buildTree(const QString& filename, const QString &analysisType, const QString &analysisId, const QString &partitionName, const QString &runNumber, bool useCache) {
  QRunId runId(partitionName, runNumber); 
  return buildTree(filename, analysisType, analysisId, runId, useCache);
}

bool TreeBuilder::buildMultiAnalysisTree(const QString & filename, const QVector<QString> & analysisType, const QVector<QString> & analysisIds, const QString & partitionName, const QString & runNumber, bool useCache) {
  QRunId runId(partitionName, runNumber); 
  return buildMultiAnalysisTree(filename, analysisType, analysisIds, runId, useCache);
}

bool TreeBuilder::buildTree(const QString& filename, const QString &analysisType, const QString &analysisId, const QRunId& /*runId*/, bool useCache) {

  if(Debug::Inst()->getEnabled()) qDebug() << "Getting DB tree from file " << qPrintable(filename);    
  QFile qf(filename);
  TFile* file = NULL;
  if(qf.exists()) file = TFile::Open(qPrintable(filename));
  
  TTree* tree = NULL;
  if (file && file->GetListOfKeys()->GetEntries() > 0 ) {
    TString treeName((file->GetListOfKeys()->At(0))->GetName()) ;
    tree = static_cast<TTree*>(file->Get(treeName.Data()));
  }
  
  if (file && tree && tree->GetEntries() && useCache) {
    if(Debug::Inst()->getEnabled()) qDebug() << "Tree found to be sane";
    return true;
  }
  else {

    if(analysisId == QString::number(sistrip::CURRENTSTATE) || analysisId == QString(sistrip::LASTO2O)) return false;    
    if(Debug::Inst()->getEnabled()) qDebug() << "Attempting to recreate the file"; 
    if (file) file->Close();
    
    file = new TFile(qPrintable(filename),"RECREATE");
    if (!file) {
      if(Debug::Inst()->getEnabled()) qDebug() << "Unable to recreate file: " << qPrintable(filename);
      return false;
    }
    
    QVector<QString> analysisIds;
    analysisIds.push_back(analysisId);
    std::stringstream myQuery;
    myQuery << getQuery( qPrintable(analysisType) );
    tree = new TTree("DBTree","DBTree");      
    fillTree(tree, qPrintable(analysisType), myQuery.str(), analysisIds);
    tree->BuildIndex("DeviceId");
    tree->Write();
    file->Close();
    if(Debug::Inst()->getEnabled()) qDebug() << "File recreated";
    return true;
  }
}


bool TreeBuilder::buildMultiPartTree(const QString& filename, QVector<QRunId> runIds) {

    if (!DbConnection::Inst()->dbConnected()) {
        if(Debug::Inst()->getEnabled()) qDebug() << "DB connection not found ... unable to make the Timing O2O tree ";
        return false;
    }

    if (runIds.size() != 4) {
        if(Debug::Inst()->getEnabled()) qDebug() << "4 runIds needed for the four partitions ... unable to make the Timing O2O tree ";
        return false;
    }

    bool result=false;
    QVector<QString> analysisIds; 
    QVector<QString> analysisTypes; 
    for (int i = 0; i < runIds.size(); i++) {
        QString myQuery("select max(analysisid), ANALYSISTYPE, RUNNUMBER, PARTITIONNAME");
        myQuery += " from analysis a join partition b on a.PARTITIONID = b.PARTITIONID";
        myQuery += " where PARTITIONNAME = ? ";
        myQuery += " and RUNNUMBER= ?"; 
        myQuery += " group by ANALYSISTYPE, RUNNUMBER, PARTITIONNAME";                 
        
        if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(myQuery);
        
        QSqlQuery query;
        query.prepare(myQuery);
        query.addBindValue(runIds[i].first);
        query.addBindValue(runIds[i].second);
        query.exec();
        int resultCounter = 0;

        QString analysisId, analysisType;

        while (query.next()) {
            analysisId    = query.value(0).toString();
            analysisType  = query.value(1).toString() ;
            resultCounter++;
        }
        if( query.lastError().isValid() ) {
            if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(query.lastError().text());
        }
        if (resultCounter==1) result = true;
        else if (resultCounter>1) {
            if(Debug::Inst()->getEnabled()) qDebug() << "More than one analysis type on the same run";
            result =  false;
        }            
        else {
            if(Debug::Inst()->getEnabled()) qDebug()  << "No analysis found for the given run number and partition";
            result = false;
        } 
        if (!result) return false;

        analysisIds  .push_back(analysisId);
        analysisTypes.push_back(analysisType);
    }

    if (analysisIds.size() != 4) {
        if(Debug::Inst()->getEnabled()) qDebug() << "Unable to find analysis IDs for the four partitions ... unable to make the Timing O2O tree ";
        return false;
    }

    if (analysisTypes.size() != 4) {
        if(Debug::Inst()->getEnabled()) qDebug() << "Unable to parse run type for all the partitions";
        return false;
    }

    if(Debug::Inst()->getEnabled()) qDebug() << "Creating the file for the Timing O2O tree for all four partitions"; 
    
    TFile* file = new TFile(qPrintable(filename),"RECREATE");
    if (!file) {
        if(Debug::Inst()->getEnabled()) qDebug() << "Unable to create the Timing O2O file: " << qPrintable(filename);
        return false;
    }
   
    std::stringstream myQuery;
    myQuery << getQuery( qPrintable(analysisTypes[0]) );
    TTree* tree = new TTree("DBTree","DBTree");      
    fillTree(tree, qPrintable(analysisTypes[0]), myQuery.str(), analysisIds);
    tree->BuildIndex("DeviceId");
    tree->Write();
    file->Close();
    if(Debug::Inst()->getEnabled()) qDebug() << "File recreated";
    return true;

}

bool TreeBuilder::buildMultiAnalysisTree(const QString & filename, const QVector<QString> & analysisType, const QVector<QString> & analysisIds, const QRunId& /*runId*/, bool useCache) {

  if(Debug::Inst()->getEnabled()) qDebug() << "Getting DB tree from file " << qPrintable(filename);    
  QFile qf(filename);
  TFile* file = NULL;
  if(qf.exists()) file = TFile::Open(qPrintable(filename));
  
  TTree* tree = NULL;
  if (file && file->GetListOfKeys()->GetEntries() > 0 ) {
    TString treeName((file->GetListOfKeys()->At(0))->GetName()) ;
    tree = static_cast<TTree*>(file->Get(treeName.Data()));
  }
  
  if (file && tree && tree->GetEntries() && useCache) {
    if(Debug::Inst()->getEnabled()) qDebug() << "Tree found to be sane";
    return true;
  }
  else {
    
    if(Debug::Inst()->getEnabled()) qDebug() << "Attempting to recreate the file"; 
    if (file) file->Close();
    
    file = new TFile(qPrintable(filename),"RECREATE");
    if (!file) {
      if(Debug::Inst()->getEnabled()) qDebug() << "Unable to recreate file: " << qPrintable(filename);
      return false;
    }
    
    QVector<std::string> myQuery;
    QVector<std::string> myType;
    for(int itype = 0; itype < analysisType.size() ; itype++){
      std::stringstream tmp;
      tmp << getQuery( qPrintable(analysisType.at(itype)) ) ;
      myQuery.push_back(tmp.str());
      myType.push_back(qPrintable(analysisType.at(itype)) ) ;
    }

    QVector<TTree*> tree_vec ; // one tree for each query
    //// create one tree for each analysis
    for(int itype = 0; itype < myType.size(); itype++){
      if(itype == 0)
	tree_vec.push_back(new TTree("DBTree","DBTree"));      
      else
	tree_vec.push_back(new TTree(Form("DBTree_friend_%d",itype),Form("DBTree_friend_%d",itype)));      
      QVector<QString> analysisId;
      analysisId.push_back(analysisIds.at(itype));
      fillTree(tree_vec.back(),myType.at(itype),myQuery.at(itype),analysisId);
      tree_vec.back()->BuildIndex("DeviceId");
    }
    
    for(int itree = 0; itree < tree_vec.size(); itree++)
      tree_vec.at(itree)->Write();

    //// Merge the trees
    file->Close();
    if(Debug::Inst()->getEnabled()) qDebug() << "File recreated";
    return true;
  }
}


QString TreeBuilder::loadAnalysis(const QRunId& pair, bool useCache) { // load analysis results from the DB

  if (pair.second == QString::number(sistrip::CURRENTSTATE)) { // current-state download of FED parameters
    std::stringstream filename;
    filename << "/opt/cmssw/shifter/avartak/data/" << (QString("CURRENTSTATE_")+pair.first+QString(".root")).toStdString();    
    bool res = buildTree(filename.str().c_str(), QString::number(sistrip::CURRENTSTATE),QString::number(sistrip::CURRENTSTATE),QRunId(pair.first,QString::number(sistrip::CURRENTSTATE)),true);

    if (Debug::Inst()->getEnabled()) {
      if (res) {
	if(Debug::Inst()->getEnabled()) qDebug() << "Tree build successful for CURRENT STATE\n";
      }
      else {
	if(Debug::Inst()->getEnabled()) qDebug() << "Tree build failed for CURRENT STATE\n";
      }
    }
    if (res) return QString(filename.str().c_str());
    else return "";
  }

  else if (pair.second == QString::number(sistrip::LASTO2O)) {
    std::stringstream filename;
    filename << "/opt/cmssw/shifter/avartak/data/" << (QString("LASTO2O_")+pair.first+QString(".root")).toStdString();

    bool res = buildTree(filename.str().c_str(), QString::number(sistrip::LASTO2O),QString::number(sistrip::LASTO2O),QRunId(pair.first,QString::number(sistrip::LASTO2O)),true);
    if (Debug::Inst()->getEnabled()) {
      if (res) {
	if(Debug::Inst()->getEnabled()) qDebug() << "Tree build successful for LAST O2O STATE\n";
	  }
      else {
	if(Debug::Inst()->getEnabled()) qDebug() << "Tree build failed for LAST O2O STATE\n";
      }
    }
    if (res) return QString(filename.str().c_str());
    else return "";
  }

  else if (pair.second == QString::number(sistrip::MULTIPART)) { // multi-partition tree

    std::stringstream filename;
    QVector<QRunId> runIds;
    QStringList parts = pair.first.split("*");
    
    if (parts.size() != 5) {
      if(Debug::Inst()->getEnabled()) qDebug() << "Unable to deconstruct 4 partition names for the multi-partition view\n";
      return "";
    }
    
    QString filenamestart = parts.at(0);	
    for (int i = 1; i < parts.size(); i++) {
      QString part = parts.at(i);
      QStringList subparts = part.split("#");
      if (subparts.size() != 2) {
	if(Debug::Inst()->getEnabled()) qDebug() << "Unable to deconstruct 4 partition names and run numbers for multi-partition view\n";
	return "";
      }
      runIds.push_back(QRunId(subparts[0], subparts[1]));
    }
    
    filename << "/opt/cmssw/shifter/avartak/data/" << filenamestart.toStdString() << (QString("_FOURPARTS.root")).toStdString();      

    bool res = buildMultiPartTree(filename.str().c_str(), runIds);

    if (Debug::Inst()->getEnabled()) {
      if (res) {
	if(Debug::Inst()->getEnabled()) qDebug() << "Tree build successful for multi-partition view\n";
      }
      else {
	if(Debug::Inst()->getEnabled()) qDebug() << "Tree build failed for multi-partition view\n";
      }
    }
    if (res) return QString(filename.str().c_str());
    else return "";
  }

  // standard tree for one partition, no current-state, no last o2o
  bool result = false;  
  QVector<QString> analysisType ;
  QVector<QString> analysisId   ;    
  int resultCounter = 0;

  if (DbConnection::Inst()->dbConnected()) {

    QString myQuery("select max(analysisid), ANALYSISTYPE, RUNNUMBER, PARTITIONNAME");
    myQuery += " from analysis a join partition b on a.PARTITIONID = b.PARTITIONID";
    myQuery += " where PARTITIONNAME = ? ";
    myQuery += " and RUNNUMBER= ?"; 
    myQuery += " group by ANALYSISTYPE, RUNNUMBER, PARTITIONNAME order by max(analysisid)";                 

    if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(myQuery);
        
    QSqlQuery query;
    query.prepare(myQuery);
    query.addBindValue(pair.first);
    query.addBindValue(pair.second); 
    query.exec();
    
    while (query.next()) {
      analysisId    .push_back(query.value(0).toString());
      analysisType  .push_back(query.value(1).toString());
      resultCounter++;
    }
    
    if( query.lastError().isValid() ) {
      if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(query.lastError().text());
    }
    if(resultCounter == 0){
      if(Debug::Inst()->getEnabled()) qDebug()  << "No analysis found for the given run number and partition";
      result = false;
    } 
    else
      result = true;
  }
  
  if(resultCounter == 1){ // single analysis type
    std::stringstream filename;
    filename << "/opt/cmssw/shifter/avartak/data/" << analysisType.front().toStdString() << "_" << pair.first.toStdString() << "_" <<  pair.second.toInt() << "_new.root";
    if(result) result = buildTree(filename.str().c_str(), analysisType.front(), analysisId.front(), pair, useCache);  
    if (result) return QString(filename.str().c_str());
    else return "";
  }
  else {
    std::stringstream filename;    
    filename << "/opt/cmssw/shifter/avartak/data/" ;
    for(int itype = 0 ; itype < analysisType.size(); itype++) filename << analysisType.at(itype).toStdString() << "_" ;
    filename << pair.first.toStdString() << "_" <<  pair.second.toInt() << "_new.root";
    if (result) result = buildMultiAnalysisTree(filename.str().c_str(), analysisType, analysisId, pair, useCache);  
    if (result) return QString(filename.str().c_str());
    else return "";    
  }
}

QString TreeBuilder::loadAnalysis(const QString& partitionName, const QString& runNumber, bool useCache) {
    QRunId runId(partitionName, runNumber);
    return loadAnalysis(runId, useCache);
}

void TreeBuilder::fillTree(TTree* tree, std::string runType, const std::string& theQuery, QVector<QString> analysisIds) {
    if( !DbConnection::Inst()->dbConnected() ) {
        if(Debug::Inst()->getEnabled()) qDebug() << "Unable to find a valid DB connection";
        return;
    }
   
    if (analysisIds.size() == 0) {
        if(Debug::Inst()->getEnabled()) qDebug() << "No analysis IDs found";
        return;
    }
 
    BaseQuery myQueryStruct2;
    myQueryStruct2.setExtendedQuery(runType);
    
    QVector<std::pair<std::string, Base_Type*> >::const_iterator it = myQueryStruct2.query.begin(), itEnd = myQueryStruct2.query.end();          
    for(; it != itEnd; ++it) {
        const char* branchstr = it->first.c_str();
        QString bookingstr = QString("Booking branch ") + QString(branchstr) + QString(" of type ");
        
        Double*           d = dynamic_cast<Double*>(it->second);
        Integer*          i = dynamic_cast<Integer*>(it->second);
        String*           s = dynamic_cast<String*>(it->second);
        IntFromStringMap* m = dynamic_cast<IntFromStringMap*>(it->second);
        if(d != NULL) {
            if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(bookingstr) << "double";
            tree->Branch(branchstr, &(d->value),Form("%s/%s", branchstr, "D"));
        } 
        else if(i != NULL) {
            if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(bookingstr) << "integer";
            tree->Branch(branchstr, &(i->value),Form("%s/%s", branchstr, "i"));
        } 
        else if(s != NULL) {
            if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(bookingstr) << "string";
            tree->Branch(branchstr, (&(s->value)),8000,0);
        } 
        else if(m != NULL) {
            if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(bookingstr) << "integer";
            tree->Branch(branchstr, &(m->value),Form("%s/%s", branchstr, "i"));
        } 
        else {
            if(Debug::Inst()->getEnabled()) qDebug() << "Unknown branch type";
        }
    }

    for (int k = 0; k < analysisIds.size(); k++) {
        QSqlQuery query;
        query.prepare(theQuery.c_str());
        query.addBindValue(analysisIds[k].toInt());
        query.exec();
    
        while (query.next()) {
	  int i = 0;
	  for(it = myQueryStruct2.query.begin(); it != itEnd; ++it,++i) it->second->setFromResultset(query,i);
	  tree->Fill();
        }
        if( query.lastError().isValid() ) {
	  if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(query.lastError().text());
        }
    }
}

std::string TreeBuilder::getQuery(const QString& analysisType) {
    std::stringstream myBasicQuery;
    myBasicQuery << "select distinct "
                 << "TKF.DETECTOR      Detector,"
                 << "TKF.SIDE          Side,"
                 << "TKF.LAYER         Layer,"
                 << "TKF.CL            Cl,"
                 << "TKF.CR            Cr,"
                 << "TKF.POWER         Power,"
                 << "TKF.MOD           Mod,"
                 << "TKF.RACK          Rack,"
                 << "TKF.CRATE         Crate,"
                 << "TKF.CONNECTOR     Slot,"
                 << "TKF.SECTOR        PP1,"
                 << "TKF.STACK         Stack,"
                 << "TKF.PLACE         Place,"
                 << "TKF.DETID         Detid,"
                 << "DCU.DCUHARDID           Dcu,"
                 << "FEC.CRATESLOT           Crate,"
                 << "FEC.FECSLOT             Fec,"
                 << "RING.RINGSLOT           Ring,"
                 << "CCU.CCUADDRESS          Ccu,"
                 << "CCU.ARRANGEMENT         CcuArrangement,"
                 << "HYBRID.I2CCHANNEL       I2CChannel,"
                 << "FEC.CRATESLOT*power(2,27)+FEC.FECSLOT*power(2,22)+RING.RINGSLOT*power(2,18)+CCU.CCUADDRESS*power(2,10)+HYBRID.I2CCHANNEL*power(2,5)+((ROUND((DEVICE.I2CADDRESS-.5)/2)-16)+1)*power(2,2)+(case when Mod(DEVICE.I2CADDRESS,2) = 0 then 1 else 2 end) FecKey,"
                << "DEVICE.I2CADDRESS       I2CAddress,"
                << "ROUND((DEVICE.I2CADDRESS-.5)/2)-16 lasChan,";

    std::stringstream myQuery;

    if (analysisType=="TIMING") {
        myQuery << myBasicQuery.str()
                << "ANALYSISTIMING.DEVICEID DeviceId,"
                << "ANALYSISTIMING.FEDID    FedId,"
                << "ANALYSISTIMING.FEUNIT   FeUnit,"
                << "ANALYSISTIMING.FECHAN   FeChan,"
                << "ANALYSISTIMING.FEDAPV   FeApv,"
                << "case "
                << " when ANALYSISTIMING.HEIGHT = -131070 "
                << " then 65535"
                << " else ANALYSISTIMING.HEIGHT "
                << " end TickHeight,"
                << "ABS(ANALYSISTIMING.DELAY)    Delay,"
                << "ABS(ANALYSISTIMING.BASE)     Base,"
                << "ABS(ANALYSISTIMING.PEAK)     Peak,"
                << "ANALYSISTIMING.KIND     Kind,"
                << "ANALYSISTIMING.ISVALID  IsValid "
                << "from "
                << "ANALYSISTIMING join "
                << "ANALYSIS on ANALYSISTIMING.ANALYSISID = ANALYSIS.ANALYSISID join "
                << "RUN      on RUN.RUNNUMBER             = ANALYSIS.RUNNUMBER  join "
                << "STATEHISTORY on STATEHISTORY.STATEHISTORYID = RUN.STATEHISTORYID join "
                << "DEVICE on ANALYSISTIMING.ANALYSISID=? and "
                << "ANALYSISTIMING.DEVICEID=DEVICE.DEVICEID join "
                << "HYBRID on DEVICE.HYBRIDID=HYBRID.HYBRIDID         join "
                << "CCU    on HYBRID.CCUID=CCU.CCUID                  join "
                << "RING   on CCU.RINGID=RING.RINGID                  join "
                << "FEC    on RING.FECID=FEC.FECID                    join "
                << "DEVICE b on b.HYBRIDID = HYBRID.HYBRIDID          join "
                << "DCU      on b.DEVICEID = DCU.DEVICEID             and  "
                << "            DCU.VERSIONMAJORID = STATEHISTORY.FECVERSIONMAJORID and "
                << "            DCU.VERSIONMINORID = STATEHISTORY.FECVERSIONMINORID left outer join "
                << "tk_fibers tkf    on DCU.DCUHARDID = tkf.dcuid and "
                << "mod( ANALYSISTIMING.FECHAN,3) = mod(fiber,3) order by DeviceId";
    } 

    else if (analysisType == "OPTOSCAN" || analysisType == "GAINSCAN") {
        myQuery << myBasicQuery.str()
                << " AOS.DEVICEID DeviceId,"
                << " AOS.FEDID    FedId,"
                << " AOS.FEUNIT   FeUnit,"
                << " AOS.FECHAN   FeChan,"
                << " AOS.FEDAPV   FeApv,"
                << " AOS.GAIN,"
                << " AOS.BIAS0,"
                << " AOS.BIAS1,"
                << " AOS.BIAS2,"
                << " AOS.BIAS3,"
                << " CASE"
                << "     WHEN GAIN=0"
                << "       THEN BIAS0"
                << "     WHEN GAIN=1"
                << "       THEN BIAS1"
                << "     WHEN GAIN=2"
                << "       THEN BIAS2"
                << "     WHEN GAIN=3"
                << "       THEN BIAS3"
                << " END SELECTEDBIAS,"
                << " AOS.MEASGAIN0,"
                << " AOS.MEASGAIN1,"
                << " AOS.MEASGAIN2,"
                << " AOS.MEASGAIN3,"
                << " CASE"
                << "     WHEN GAIN=0"
                << "       THEN MEASGAIN0"
                << "     WHEN GAIN=1"
                << "       THEN MEASGAIN1"
                << "     WHEN GAIN=2"
                << "       THEN MEASGAIN2"
                << "     WHEN GAIN=3"
                << "       THEN MEASGAIN3"
                << " END SELECTEDMEASGAIN,"
                << " AOS.ZEROLIGHT0,"
                << " AOS.ZEROLIGHT1,"
                << " AOS.ZEROLIGHT2,"
                << " AOS.ZEROLIGHT3,"
                << " CASE"
                << "     WHEN GAIN=0"
                << "       THEN ZEROLIGHT0"
                << "     WHEN GAIN=1"
                << "       THEN ZEROLIGHT1"
                << "     WHEN GAIN=2"
                << "       THEN ZEROLIGHT2"
                << "     WHEN GAIN=3"
                << "       THEN ZEROLIGHT3"
                << " END SELECTEDZEROLIGHT,"
                << " AOS.LINKNOISE0,"
                << " AOS.LINKNOISE1,"
                << " AOS.LINKNOISE2,"
                << " AOS.LINKNOISE3,"
                << " CASE"
                << "     WHEN GAIN=0"
                << "       THEN LINKNOISE0"
                << "     WHEN GAIN=1"
                << "       THEN LINKNOISE1"
                << "     WHEN GAIN=2"
                << "       THEN LINKNOISE2"
                << "     WHEN GAIN=3"
                << "       THEN LINKNOISE3"
                << " END SELECTEDLINKNOISE,"
                << " AOS.LIFTOFF0,"
                << " AOS.LIFTOFF1,"
                << " AOS.LIFTOFF2,"
                << " AOS.LIFTOFF3,"
                << " CASE"
                << "     WHEN GAIN=0"
                << "       THEN LIFTOFF0"
                << "     WHEN GAIN=1"
                << "       THEN LIFTOFF1"
                << "     WHEN GAIN=2"
                << "       THEN LIFTOFF2"
                << "     WHEN GAIN=3"
                << "       THEN LIFTOFF3"
                << " END SELECTEDLIFTOFF,"
                << " AOS.THRESHOLD0,"
                << " AOS.THRESHOLD1,"
                << " AOS.THRESHOLD2,"
                << " AOS.THRESHOLD3,"
                << " CASE"
                << "     WHEN GAIN=0"
                << "       THEN THRESHOLD0"
                << "     WHEN GAIN=1"
                << "       THEN THRESHOLD1"
                << "     WHEN GAIN=2"
                << "       THEN THRESHOLD2"
                << "     WHEN GAIN=3"
                << "       THEN THRESHOLD3"
                << " END SELECTEDTHRESHOLD,"
                << " AOS.TICKHEIGHT0,"
                << " AOS.TICKHEIGHT1,"
                << " AOS.TICKHEIGHT2,"
                << " AOS.TICKHEIGHT3,"
                << " CASE"
                << "     WHEN GAIN=0"
                << "       THEN TICKHEIGHT0"
                << "     WHEN GAIN=1"
                << "       THEN TICKHEIGHT1"
                << "     WHEN GAIN=2"
                << "       THEN TICKHEIGHT2"
                << "     WHEN GAIN=3"
                << "       THEN TICKHEIGHT3"
                << " END SELECTEDTICKHEIGHT,"
                << " AOS.ISVALID,"
                << " AOS.BASELINESLOP0,"
                << " AOS.BASELINESLOP1,"
                << " AOS.BASELINESLOP2,"
                << " AOS.BASELINESLOP3, "
                << " CASE"
                << "     WHEN GAIN=0"
                << "       THEN BASELINESLOP0"
                << "     WHEN GAIN=1"
                << "       THEN BASELINESLOP1"
                << "     WHEN GAIN=2"
                << "       THEN BASELINESLOP2"
                << "     WHEN GAIN=3"
                << "       THEN BASELINESLOP3"
                << " END SELECTEDBASELINESLOP,"
                << " CASE"
                << "     WHEN BASELINESLOP0<0.1"
                << "       THEN -1"
                << "     WHEN TICKHEIGHT0=65535"
                << "       THEN -1"
                << "     ELSE TICKHEIGHT0/BASELINESLOP0"
                << " END NORMTICK0,"
                << " CASE"
                << "     WHEN BASELINESLOP1<0.1"
                << "       THEN -1"
                << "     WHEN TICKHEIGHT1=65535"
                << "       THEN -1"
                << "     ELSE TICKHEIGHT1/BASELINESLOP1"
                << " END NORMTICK1,"
                << " CASE"
                << "     WHEN BASELINESLOP2<0.1"
                << "       THEN -1"
                << "     WHEN TICKHEIGHT2=65535"
                << "       THEN -1"
                << "     ELSE TICKHEIGHT2/BASELINESLOP2"
                << " END NORMTICK2,"
                << " CASE"
                << "     WHEN BASELINESLOP3<0.1"
                << "       THEN -1"
                << "     WHEN TICKHEIGHT3=65535"
                << "       THEN -1"
                << "     ELSE TICKHEIGHT3/BASELINESLOP3"
                << " END NORMTICK3"
                << " from"
                << " ANALYSISOPTOSCAN AOS join"
                << " ANALYSIS on AOS.ANALYSISID = ANALYSIS.ANALYSISID join"
                << " RUN      on RUN.RUNNUMBER  = ANALYSIS.RUNNUMBER  join"
                << " STATEHISTORY on STATEHISTORY.STATEHISTORYID = RUN.STATEHISTORYID join"
                << " DEVICE on AOS.DEVICEID=DEVICE.DEVICEID join"
                << " HYBRID on DEVICE.HYBRIDID=HYBRID.HYBRIDID join"
                << " CCU    on HYBRID.CCUID=CCU.CCUID join"
                << " RING   on CCU.RINGID=RING.RINGID join"
                << " FEC    on RING.FECID=FEC.FECID   join"
                << " DEVICE b on b.HYBRIDID = HYBRID.HYBRIDID          join"
                << " DCU      on b.DEVICEID = DCU.DEVICEID   and"
                << "             DCU.VERSIONMAJORID = STATEHISTORY.FECVERSIONMAJORID and"
                << "             DCU.VERSIONMINORID = STATEHISTORY.FECVERSIONMINORID left outer join"
                << " tk_fibers tkf on DCU.DCUHARDID = tkf.dcuid and "
                << " mod( AOS.FECHAN,3) = mod(fiber,3) "
                << " where "
                << " AOS.ANALYSISID=?";
    
    } 

    else if(analysisType == "VPSPSCAN") {
        myQuery << myBasicQuery.str()
                << " ANALYSISVPSPSCAN.DEVICEID DeviceId,"
                << " ANALYSISVPSPSCAN.FEDID    FedId,"
                << " ANALYSISVPSPSCAN.FEUNIT   FeUnit,"
                << " ANALYSISVPSPSCAN.FECHAN   FeChan,"
                << " ANALYSISVPSPSCAN.FEDAPV   FeApv,"
                << " ANALYSISVPSPSCAN.VPSP,"
                << " ANALYSISVPSPSCAN.ADCLEVEL,"
                << " ANALYSISVPSPSCAN.FRACTION,"
                << " ANALYSISVPSPSCAN.TOPEDGE,"
                << " ANALYSISVPSPSCAN.BOTTOMEDGE,"
                << " ANALYSISVPSPSCAN.TOPLEVEL,"
                << " ANALYSISVPSPSCAN.BOTTOMLEVEL,"
                << " ANALYSISVPSPSCAN.ISVALID "
                << " from"
                << " ANALYSISVPSPSCAN join"
                << " ANALYSIS on ANALYSISVPSPSCAN.ANALYSISID = ANALYSIS.ANALYSISID join"
                << " RUN      on RUN.RUNNUMBER             = ANALYSIS.RUNNUMBER  join"
                << " STATEHISTORY on STATEHISTORY.STATEHISTORYID = RUN.STATEHISTORYID and"
                << "                 STATEHISTORY.PARTITIONID    = ANALYSIS.PARTITIONID    join"
                << " DEVICE on ANALYSISVPSPSCAN.DEVICEID=DEVICE.DEVICEID join"
                << " HYBRID on DEVICE.HYBRIDID=HYBRID.HYBRIDID join"
                << " CCU    on HYBRID.CCUID=CCU.CCUID join"
                << " RING   on CCU.RINGID=RING.RINGID join"
                << " FEC    on RING.FECID=FEC.FECID   join"
                << " DEVICE b on b.HYBRIDID = HYBRID.HYBRIDID          join"
                << " DCU      on b.DEVICEID = DCU.DEVICEID             and"
                << "              DCU.VERSIONMAJORID=STATEHISTORY.FECVERSIONMAJORID        and"
                << "              DCU.VERSIONMINORID=STATEHISTORY.FECVERSIONMINORID        left outer join"
                << " tk_fibers tkf on DCU.DCUHARDID = tkf.dcuid      and"
                << "              mod( ANALYSISVPSPSCAN.FECHAN,3) = mod(fiber,3) "
                << " where"
                << " ANALYSISVPSPSCAN.ANALYSISID=?"; 

    }

    else if(analysisType == "VERY_FAST_CONNECTION" || analysisType == "FASTFEDCABLING" ) {
        myQuery << myBasicQuery.str()
                << " ANALYSISFASTFEDCABLING.DEVICEID DeviceId,"
                << " ANALYSISFASTFEDCABLING.FEDID    FedId,"
                << " ANALYSISFASTFEDCABLING.FEUNIT   FeUnit,"
                << " ANALYSISFASTFEDCABLING.FECHAN   FeChan,"
                << " ANALYSISFASTFEDCABLING.FEDAPV   FeApv,"
                << " ANALYSISFASTFEDCABLING.HIGHLEVEL,"
                << " ANALYSISFASTFEDCABLING.HIGHRMS,"
                << " ANALYSISFASTFEDCABLING.LOWLEVEL,"
                << " ANALYSISFASTFEDCABLING.LOWRMS,"
                << " ANALYSISFASTFEDCABLING.MAXLL,"
                << " ANALYSISFASTFEDCABLING.MINLL,"
                << " ANALYSISFASTFEDCABLING.DCUID,"
                << " ANALYSISFASTFEDCABLING.LLDCH,"
                << " ANALYSISFASTFEDCABLING.ISVALID,"
                << " ANALYSISFASTFEDCABLING.ISDIRTY "
                << " from"
                << " ANALYSISFASTFEDCABLING join"
                << " ANALYSIS  on ANALYSISFASTFEDCABLING.ANALYSISID = ANALYSIS.ANALYSISID  join"
                << " RUN       on RUN.RUNNUMBER             = ANALYSIS.RUNNUMBER           join"
                << " STATEHISTORY on STATEHISTORY.STATEHISTORYID = RUN.STATEHISTORYID      and"
                << "                 STATEHISTORY.PARTITIONID    = ANALYSIS.PARTITIONID    join"
                << " DEVICE    on ANALYSISFASTFEDCABLING.DEVICEID=DEVICE.DEVICEID          join"
                << " HYBRID    on DEVICE.HYBRIDID=HYBRID.HYBRIDID                          join"
                << " CCU       on HYBRID.CCUID=CCU.CCUID                                   join"
                << " RING      on CCU.RINGID=RING.RINGID                                   join"
                << " FEC       on RING.FECID=FEC.FECID                                     join"
                << " DEVICE b  on b.HYBRIDID=HYBRID.HYBRIDID                               join"
                << " DCU       on b.DEVICEID = DCU.DEVICEID                                and"
                << "              DCU.VERSIONMAJORID=STATEHISTORY.FECVERSIONMAJORID        and"
                << "              DCU.VERSIONMINORID=STATEHISTORY.FECVERSIONMINORID        left outer join"
                << " tk_fibers tkf on DCU.DCUHARDID = tkf.dcuid                          and"
                << "              mod( ANALYSISFASTFEDCABLING.FECHAN,3) = mod(fiber,3)"
                << " where ANALYSISFASTFEDCABLING.ANALYSISID=?";
    
    }

    else if(analysisType == "PEDESTALS" || analysisType == "PEDESTAL") {
        myQuery << myBasicQuery.str()
                << " ANALYSISPEDESTALS.DEVICEID     DeviceId,"
                << " ANALYSISPEDESTALS.FEDID        FedId,"
                << " ANALYSISPEDESTALS.FEUNIT       FeUnit,"
                << " ANALYSISPEDESTALS.FECHAN       FeChan,"
                << " ANALYSISPEDESTALS.FEDAPV       FeApv,"
                << " ANALYSISPEDESTALS.PEDSMEAN     PedsMean,"
                << " ANALYSISPEDESTALS.PEDSSPREAD   PedsSpread,"
                << " ANALYSISPEDESTALS.NOISEMEAN    NoiseMean,"
                << " ANALYSISPEDESTALS.NOISESPREAD  NoiseSpread,"
                << " ANALYSISPEDESTALS.RAWMEAN      RawMean,"
                << " ANALYSISPEDESTALS.RAWSPREAD    RawSpread,"
                << " ANALYSISPEDESTALS.PEDSMAX      PedsMax,"
                << " ANALYSISPEDESTALS.PEDSMIN      PedsMin,"
                << " ANALYSISPEDESTALS.NOISEMAX     NoiseMax,"
                << " ANALYSISPEDESTALS.NOISEMIN     NoiseMin,"
                << " ANALYSISPEDESTALS.RAWMAX       RawMax,"
                << " ANALYSISPEDESTALS.RAWMIN       RawMin,"
                << " ANALYSISPEDESTALS.ISVALID      IsValid, "
                << " ANALYSISPEDESTALS.DEAD         Dead, "
                << " ANALYSISPEDESTALS.NOISY        Noisy "
                << " from"
                << " ANALYSISPEDESTALS join"
                << " ANALYSIS on ANALYSISPEDESTALS.ANALYSISID = ANALYSIS.ANALYSISID join"
                << " DEVICE on ANALYSISPEDESTALS.ANALYSISID=? and"
                << " ANALYSISPEDESTALS.DEVICEID=DEVICE.DEVICEID join"
                << " RUN on RUN.RUNNUMBER   = ANALYSIS.RUNNUMBER  join"
                << " STATEHISTORY on STATEHISTORY.STATEHISTORYID = RUN.STATEHISTORYID join"
                << " HYBRID on DEVICE.HYBRIDID=HYBRID.HYBRIDID join"
                << " CCU    on HYBRID.CCUID=CCU.CCUID join"
                << " RING   on CCU.RINGID=RING.RINGID join"
                << " FEC    on RING.FECID=FEC.FECID   join"
                << " DEVICE b on b.HYBRIDID = HYBRID.HYBRIDID          join"
                << " DCU      on b.DEVICEID = DCU.DEVICEID             left outer join"
                << " tk_fibers tkf on DCU.DCUHARDID = tkf.dcuid      and"
                << " mod( ANALYSISPEDESTALS.FECHAN,3) = mod(fiber,3) order by DeviceId";
    } 


    else if(analysisType == "CALIBRATION" || analysisType == "CALIBRATION_DECO" || analysisType == "CALIBRATION_SCAN" || analysisType == "CALIBRATION_SCAN_DECO") {
        myQuery << myBasicQuery.str()
                << " ANALYSISCALIBRATION.DEVICEID     DeviceId,"
                << " ANALYSISCALIBRATION.FEDID        FedId,"
                << " ANALYSISCALIBRATION.FEUNIT       FeUnit,"
                << " ANALYSISCALIBRATION.FECHAN       FeChan,"
                << " ANALYSISCALIBRATION.FEDAPV       FeApv,"
                << " ANALYSISCALIBRATION.AMPLITUDE    Amplitude,"
                << " ANALYSISCALIBRATION.TAIL         Tail,"
                << " ANALYSISCALIBRATION.RISETIME     RiseTime,"
                << " ANALYSISCALIBRATION.TIMECONSTANT TimeConstant,"
                << " ANALYSISCALIBRATION.SMEARING     Smearing,"
                << " ANALYSISCALIBRATION.CHI2         Chi2,"
                << " ANALYSISCALIBRATION.DECONVMODE   DeconvMode,"
                << " ANALYSISCALIBRATION.ISVALID      IsValid "
                << " from"
                << " ANALYSISCALIBRATION join"
                << " ANALYSIS on ANALYSISCALIBRATION.ANALYSISID = ANALYSIS.ANALYSISID join"
                << " DEVICE on ANALYSISCALIBRATION.ANALYSISID=? and"
                << " ANALYSISCALIBRATION.DEVICEID=DEVICE.DEVICEID join"
                << " RUN on RUN.RUNNUMBER   = ANALYSIS.RUNNUMBER  join"
                << " STATEHISTORY on STATEHISTORY.STATEHISTORYID = RUN.STATEHISTORYID join"
                << " HYBRID on DEVICE.HYBRIDID=HYBRID.HYBRIDID join"
                << " CCU    on HYBRID.CCUID=CCU.CCUID join"
                << " RING   on CCU.RINGID=RING.RINGID join"
                << " FEC    on RING.FECID=FEC.FECID   join"
                << " DEVICE b on b.HYBRIDID = HYBRID.HYBRIDID          join"
                << " DCU      on b.DEVICEID = DCU.DEVICEID             left outer join"
                << " tk_fibers tkf on DCU.DCUHARDID = tkf.dcuid      and"
                << " mod(ANALYSISCALIBRATION.FECHAN,3) = mod(fiber,3) order by DeviceId";
    } 

    else {
        if(Debug::Inst()->getEnabled()) qDebug() << "Unknown analysistype " << analysisType;
    }

    if(Debug::Inst()->getEnabled()) qDebug() << "\nTreeBuilder Query : \n" << myQuery.str().c_str() << "\n";
    return myQuery.str();
}


bool TreeBuilder::getState(const QString &partitionName, int state) {

    if ( state == sistrip::CURRENTSTATE ) {
        if(Debug::Inst()->getEnabled()) qDebug() << "Creating tree from current state";
    }            
    else if ( state == sistrip::LASTO2O ) {
        if(Debug::Inst()->getEnabled()) qDebug() << "Creating tree from last o2o'ed state";
    }
    else {
        if(Debug::Inst()->getEnabled()) qDebug() << "Unknown state type";
        return false; 
    }
    
    QString statestr = "viewcurrentstate";
    if (state == sistrip::LASTO2O) statestr = "VIEWLASTO2OPARTITIONS";

    QString devmapstr(
        QString("select distinct a.deviceid, detid, a.i2caddress from device a join hybrid b on a.hybridid=b.hybridid join device c on b.hybridid=c.hybridid join dcu on c.deviceid=dcu.deviceid join ") + 
        statestr +
        QString(" d on partitionname = \'") +
        partitionName +
        QString("\' and dcu.versionmajorid=d.fecversionmajorid and dcu.versionminorid=d.fecversionminorid join dcuinfo e on e.versionmajorid = d.dcuinfoversionmajorid and e.versionminorid= d.dcuinfoversionminorid and e.dcuhardid=dcu.dcuhardid and a.i2caddress in ( 32,33,34,35,36,37 ) order by detid, i2caddress")
    );

    QSqlQuery devquery;
    devquery.prepare(devmapstr);
    devquery.exec();
   
    QMap<unsigned int, QPair<unsigned int, int> > devmap;
 
    while (devquery.next()) {
        unsigned int devid = devquery.value(0).toUInt();
        unsigned int detid = devquery.value(1).toUInt();
        int          i2cad = devquery.value(2).toInt();
    
        devmap[devid] = QPair<unsigned int, int>(detid, i2cad);
    }

    QString currentStateFED("with mypartition as ( select ? name from dual), myvalues as ( select fed.id fedid, fefpga.id feunit, channel.id fechan,apvfed.id apvfed,channelvalues.coarsedelay coarsedelay,channelvalues.finedelay finedelay ,channelvalues.threshold threshold, VALUE  from strip join apvfed on apvid=deviceid join channel using(channelid) join channelpair using(channelpairid) join channelvalues using(channelid) join fefpga using(fefpgaid) join fed using(fedid) join viewcurrentstate a on a.partitionname=( select name from mypartition) and a.partitionid=fed.partitionid and strip.versionmajorid=a.fedversionmajorid and channelvalues.versionmajorid=a.fedversionmajorid and apvid not in ( select deviceid from fedmaskdevice mask join viewcurrentstate a on mask.VERSIONMAJORID=a.MASKVERSIONMAJORID and mask.VERSIONMINORID=a.MASKVERSIONMINORID) ), myconnections as ( select distinct FEDID, FEUNIT, FECHAN, DEVICEID, i2caddress, i2cchannel, ccuaddress, ringslot, fecslot, crateslot, CRATESLOT*power(2,27)+FECSLOT*power(2,22)+RINGSLOT*power(2,18)+CCUADDRESS*power(2,10)+I2CCHANNEL*power(2,5)+((ROUND((I2CADDRESS-.5)/2)-16)+1)*power(2,2)+(case when Mod(I2CADDRESS,2) = 0 then 1 else 2 end) FecKey from ANALYSISFASTFEDCABLING join analysis using(analysisid) join viewcurrentstate using(partitionid) join viewdevice using(deviceid) where viewdevice.partitionname=(select name from mypartition)  ) select myvalues.fedid fedid, myvalues.feunit feunit, myvalues.fechan fechan, myvalues.apvfed feapv, myconnections.deviceid, i2caddress,i2cchannel,ccuaddress,ringslot, fecslot, feckey , myvalues.coarsedelay, myvalues.finedelay, myvalues.threshold, value from myvalues inner join myconnections on myvalues.fedid=myconnections.fedid and myvalues.feunit=myconnections.feunit and myvalues.fechan=myconnections.fechan and mod(APVFED,2) <> mod(I2CADDRESS,2) and value is not null order by myvalues.fedid,myvalues.feunit, myvalues.fechan");

    QString currentStateFEC("with mypartition as ( select ? name from dual), myfecvalues as (select viewallapvfec.deviceid deviceid,viewallapvfec.apvMode apvMode,viewallapvfec.isha isha,viewallapvfec.vfs vfs,viewallapvfec.vpsp vpsp,viewallapvfec.vfp vfp from viewallapvfec join viewdevice b on b.deviceid=viewallapvfec.deviceid join viewcurrentstate a on a.partitionname=(select name from mypartition) and a.fecVersionMajorId=viewallapvfec.versionMajorId and a.fecVersionMinorId=viewallapvfec.versionMinorId) select deviceid,apvMode,isha,vfs,vpsp,vfp from myfecvalues");

    QString lastO2OFED("with mypartition as ( select ? name from dual), myvalues as ( select fed.id fedid, fefpga.id feunit, channel.id fechan,apvfed.id apvfed,channelvalues.coarsedelay coarsedelay,channelvalues.finedelay finedelay ,channelvalues.threshold threshold, VALUE  from strip join apvfed on apvid=deviceid join channel using(channelid) join channelpair using(channelpairid) join channelvalues using(channelid) join fefpga using(fefpgaid) join fed using(fedid) join VIEWLASTO2OPARTITIONS a on a.partitionname=( select name from mypartition) and a.partitionid=fed.partitionid and strip.versionmajorid=a.fedversionmajorid and channelvalues.versionmajorid=a.fedversionmajorid and apvid not in ( select deviceid from fedmaskdevice mask join VIEWLASTO2OPARTITIONS a on mask.VERSIONMAJORID=a.MASKVERSIONMAJORID and mask.VERSIONMINORID=a.MASKVERSIONMINORID) ), myconnections as ( select distinct FEDID, FEUNIT, FECHAN, DEVICEID, i2caddress, i2cchannel, ccuaddress, ringslot, fecslot, crateslot, CRATESLOT*power(2,27)+FECSLOT*power(2,22)+RINGSLOT*power(2,18)+CCUADDRESS*power(2,10)+I2CCHANNEL*power(2,5)+((ROUND((I2CADDRESS-.5)/2)-16)+1)*power(2,2)+(case when Mod(I2CADDRESS,2) = 0 then 1 else 2 end) FecKey from ANALYSISFASTFEDCABLING join analysis using(analysisid) join VIEWLASTO2OPARTITIONS using(partitionid) join viewdevice using(deviceid) where viewdevice.partitionname=(select name from mypartition)  ) select myvalues.fedid fedid, myvalues.feunit feunit, myvalues.fechan fechan, myvalues.apvfed feapv, myconnections.deviceid, i2caddress,i2cchannel,ccuaddress,ringslot, fecslot, feckey , myvalues.coarsedelay, myvalues.finedelay, myvalues.threshold, value from myvalues inner join myconnections on myvalues.fedid=myconnections.fedid and myvalues.feunit=myconnections.feunit and myvalues.fechan=myconnections.fechan and mod(APVFED,2) <> mod(I2CADDRESS,2) and value is not null order by myvalues.fedid,myvalues.feunit, myvalues.fechan");

    QString lastO2OFEC("with mypartition as ( select ? name from dual), myfecvalues as (select viewallapvfec.deviceid deviceid,viewallapvfec.apvMode apvMode,viewallapvfec.isha isha,viewallapvfec.vfs vfs,viewallapvfec.vpsp vpsp,viewallapvfec.vfp vfp from viewallapvfec join viewdevice b on b.deviceid=viewallapvfec.deviceid join VIEWLASTO2OPARTITIONS a on a.partitionname=(select name from mypartition) and a.FECVERSIONMAJORID =viewallapvfec.versionMajorId and a.FECVERSIONMINORID=viewallapvfec.versionMinorId) select deviceid,apvMode,isha,vfs,vpsp,vfp from myfecvalues");
    
    
    double FedId, FeUnit, FeChan, FeApv, DeviceId, Fec, Ring, Ccu, I2CChannel,I2CAddress, Detid, PedsMean, NoiseMean, Noisy, CoarseDelay, FineDelay, Threshold;
    uint32_t FecKey;
    Double_t Noise[128], Pedestal[128], lowThreshold[128], highThreshold[128], NoisyStrips[128];
    
    QSqlQuery getClobFED, getClobFEC;
    if ( state == sistrip::CURRENTSTATE ) getClobFED.prepare(currentStateFED);
    else getClobFED.prepare(lastO2OFED);

    if ( state == sistrip::CURRENTSTATE ) getClobFEC.prepare(currentStateFEC);
    else getClobFEC.prepare(lastO2OFEC);

    getClobFED.addBindValue(partitionName);
    getClobFED.exec();
    
    if ( getClobFED.lastError().isValid() ) {
        if(Debug::Inst()->getEnabled()) qDebug() << getClobFED.lastError().text();
        return false;
    }

    getClobFEC.addBindValue(partitionName);
    getClobFEC.exec();
    
    if ( getClobFEC.lastError().isValid() ) {
      if(Debug::Inst()->getEnabled()) qDebug() << getClobFEC.lastError().text();
      return false;
    }
    
    if(Debug::Inst()->getEnabled()) qDebug() << "Query done, now booking tree....";
    
    QString path = "/opt/cmssw/shifter/avartak/data/";
    
    QString name = QString("CURRENTSTATE_")+partitionName;
    if (state == sistrip::LASTO2O) name = QString("LASTO2O_")+partitionName;
    
    TFile *file = new TFile(qPrintable(path+name+QString(".root")),"RECREATE");

    TTree *tree = new TTree("DBTree","DBTree"); // for FED parameters
    tree->Branch("FedId",&FedId,"FedId/D");
    tree->Branch("FeUnit",&FeUnit,"FeUnit/D");
    tree->Branch("FeChan",&FeChan,"FeChan/D");
    tree->Branch("FeApv",&FeApv,"FeApv/D");
    tree->Branch("Fec",&Fec,"Fec/D");
    tree->Branch("Ring",&Ring,"Ring/D");
    tree->Branch("Ccu",&Ccu,"Ccu/D");
    tree->Branch("DeviceId",&DeviceId,"DeviceId/D");
    tree->Branch("I2CChannel",&I2CChannel,"I2CChannel/D");
    tree->Branch("I2CAddress",&I2CAddress,"I2CAddress/D");
    tree->Branch("Detid",&Detid,"Detid/D");
    tree->Branch("FecKey",&FecKey,"FecKey/D");
    tree->Branch("CoarseDelay",&CoarseDelay,"CoarseDelay/D");
    tree->Branch("FineDelay",&FineDelay,"FineDelay/D");
    tree->Branch("Threshold",&Threshold,"Threshold/D");
    tree->Branch("PedsMean",&PedsMean,"PedsMean/D");
    tree->Branch("NoiseMean",&NoiseMean,"NoiseMean/D");
    tree->Branch("Noisy",&Noisy,"Noisy/D");
    tree->Branch("Noise",&Noise,"Noise[128]/D");
    tree->Branch("Pedestal",&Pedestal,"Pedestal[128]/D");
    tree->Branch("lowThreshold",&lowThreshold,"lowThreshold[128]/D");
    tree->Branch("highThreshold",&highThreshold,"highThreshold[128]/D");
    tree->Branch("NoisyStrips",&NoisyStrips,"NoisyStrips[128]/D");
    
    if(Debug::Inst()->getEnabled()) qDebug() << "Tree booked, now retrieving results";

    // FED parameters
    int count = 0;

    while (getClobFED.next()) {
        count++;        
        if ( count % 100 == 0 ) QApplication::processEvents();
        
        FedId      = getClobFED.value(0).toDouble();
        FeUnit     = getClobFED.value(1).toDouble();
        FeChan     = getClobFED.value(2).toDouble();
        FeApv      = getClobFED.value(3).toDouble();
        DeviceId   = getClobFED.value(4).toDouble();
        I2CAddress = getClobFED.value(5).toDouble();
        I2CChannel = getClobFED.value(6).toDouble();
        Ccu        = getClobFED.value(7).toDouble();
        Ring       = getClobFED.value(8).toDouble();
        Fec        = getClobFED.value(9).toDouble();
        FecKey     = getClobFED.value(10).toUInt();
	CoarseDelay = getClobFED.value(11).toDouble();
	FineDelay  = getClobFED.value(12).toDouble();
	Threshold  = getClobFED.value(13).toDouble();
        Detid      = double(devmap[getClobFED.value(4).toUInt()].first);

        QByteArray array = QByteArray::fromBase64 (getClobFED.value(14).toByteArray()).toHex();
        int index = 0;
        for( int i = 0; i < array.size(); i+=8, ++index ) {
            QByteArray mystrip = array.mid(i,8);
            QByteArray mystrip2;
            for( int k = mystrip.size(); k >= 0; k-=2 ) mystrip2 += mystrip.mid(k,2);
            bool ok;
            long strip = mystrip2.toLong(&ok,16);
            float noise   = static_cast<float>    ( ( strip >> 13 ) & 0x000001FF ) / 10.0;
            uint16_t ped  = static_cast<uint16_t> ( ( strip >> 22 ) & 0x000003FF );
            uint16_t noi  = static_cast<uint16_t> ( strip & 0x00000001);
	    float lowThr = 1.;
	    float highThr = 1.;

            if ( index < 128 ) {
                Noise[index] = noise;
                Pedestal[index] = ped;
                NoisyStrips[index] = noi;
		lowThreshold[index] = lowThr;
		highThreshold[index] = highThr;
            } 
            else {
                if(Debug::Inst()->getEnabled()) qDebug() << "Would try to fill strip " << strip << " and will not do it!";
            }
        }
        PedsMean  = 0.0;
        NoiseMean = 0.0;
        Noisy     = 0.0;
        for (int i = 0; i < 128; i++) {
            PedsMean  += Pedestal[i];
            NoiseMean += Noise[i];
            Noisy     += NoisyStrips[i];
        }
        PedsMean /= 128.0;
        NoiseMean /= 128.0;
        tree->Fill();
    }

    tree->Write();
    file->Close();
    if(Debug::Inst()->getEnabled()) qDebug() << "Done filling, writing results";


    // FEC parameters 
    file = new TFile(qPrintable(path+name+QString(".root")),"UPDATE");
    TTree *tree_friend = new TTree("DBTree_friend","DBTree_friend"); // for FEC parameters    
    double device,ApvMode, Isha, Vfs, Vfp, Vpsp;
    tree_friend->Branch("DeviceId",&device,"DeviceId/D");
    tree_friend->Branch("ApvMode",&ApvMode,"ApvMode/D");
    tree_friend->Branch("Isha",&Isha,"Isha/D");
    tree_friend->Branch("Vfs",&Vfs,"Vfs/D");
    tree_friend->Branch("Vfp",&Vfp,"Vfp/D");
    tree_friend->Branch("Vpsp",&Vpsp,"Vpsp/D");
    
    count = 0;
    while (getClobFEC.next()) {
        count++;        
        if ( count % 100 == 0 ) QApplication::processEvents();
        
        device        = getClobFEC.value(0).toDouble();
        ApvMode       = getClobFEC.value(1).toDouble();
        Isha          = getClobFEC.value(2).toDouble();
        Vfs           = getClobFEC.value(3).toDouble();
        Vpsp          = getClobFEC.value(4).toDouble();
        Vfp           = getClobFEC.value(5).toDouble();
        tree_friend->Fill();
    }
    
    // done by hand because this is a special case
    tree_friend->Write();
    file->Close();

    return true;
  
}
