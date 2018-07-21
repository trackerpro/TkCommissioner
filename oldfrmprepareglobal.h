/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor
 *****************************************************************************/


#include <iostream>
#include <occi.h>
#include <map>

#include "frmpartitions.h"
#include "frmterminal.h"
#include "frmterminaldialog.h"
#include "Debug.h"

#include <q3process.h>
#include <qprocess.h>
#include <qstatusbar.h>
#include <q3table.h> 
#include <qmessagebox.h>
#include <q3stylesheet.h> 
#include <qcolordialog.h> 
#include <qlabel.h>
#include <qtimer.h>
#include <q3progressdialog.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <q3mimefactory.h>
#include <Q3VBoxLayout>

#define TIB_ID "TIB/TID"
#define TOB_ID "TOB"
#define TECP_ID "TEC+"
#define TECM_ID "TEC-"
#define O2O_ID "O2O"


#define PREPAREGLOBAL_SCRIPT "/nfshome0/trackerpro/o2o/scripts/prepareGlobal_slc5.sh"


#define SELECTPARTNAMES "select partitionname, max(o2oid) as o2oid from partition, StateHistory, CurrentState, O2OPartition where StateHistory.partitionid=Partition.partitionId and StateHistory.stateHistoryId=CurrentState.stateHistoryId and Partition.partitionId = O2OPartition.partitionid and SUBDETECTOR = '%1' group by partitionname order by O2OID asc"

// Actual version is ok? These two checks should be made:
// For real partitions: (should be 1, checks on partitionName)
#define SELECTXCHECK "select PkgO2OPartition.getO2OXChecked('%1') from dual"
// For (none) partitions: (should be 0, checks on subDetector) Also used to know if a partition was used or not
#define SELECTXCHECKNONE "select count(runnumber) from o2opartition where runnumber=(select max(runnumber) from o2opartition) and subdetector='%1'"
// For (none) partitions: (should be 1, checks on subDetector)
#define SELECTXCHECKO2O "select count(runnumber) from o2opartition where runnumber=(select max(runnumber) from o2opartition) and subdetector='%1'"

// Constraint check to be done prior to the upload
// If these fail, then you need to inform the user
// This sould say zero
#define SELECTCHECKDUPLICATE "select count(runnumber) from partition, o2opartition where partition.partitionid = o2opartition.partitionid and partition.partitionname = '%1' and o2opartition.runnumber = %2"
// This also should say zero
#define SELECTCHECKDUPLICATESUB "select count(runnumber) from o2opartition where runnumber=%1 and subdetector='%2'"

// Get the next available run number and the last saved IOV start
//#define SELECTNEXTRUNNUMBER "select max(runnumbertbl.runnumber+1), max(o2opartition.runnumber) from CMS_RUNINFO.runnumbertbl, o2opartition"
#define SELECTNEXTRUNNUMBER "with nextglobalrun as (select max(runnumbertbl.runnumber+1) runnumber from CMS_RUNINFO.runnumbertbl), lasto2o as (select max(o2opartition.runnumber) runnumber from o2opartition) select nextglobalrun.runnumber, lasto2o.runnumber from nextglobalrun, lasto2o"

// The actual insert operation
#define EXECINSERTOPERATION "BEGIN PkgO2OPartition.insertO2OOperation('%1', '%2', %3); END;"
// The exec operation confirming the succcessfull o2o
#define EXECCONFIRMO2O "BEGIN PkgO2OPartition.insertO2OConfirmation(%1); END;"

// The values to be passed to the O2O
#define SELECTLATESTVERSION "select RUNNUMBER, PARTITIONNAME, FECVERSIONMAJORID, FECVERSIONMINORID, FEDVERSIONMAJORID, FEDVERSIONMINORID, CONNECTIONVERSIONMAJORID, CONNECTIONVERSIONMINORID, DCUINFOVERSIONMAJORID, DCUINFOVERSIONMINORID, DCUPSUMAPVERSIONMAJORID, DCUPSUMAPVERSIONMINORID from ViewLastO2OPartitions" // unused 
//old query
//#define SELECTLATESTVERSIONS "select FECVERSIONMAJORID, FECVERSIONMINORID, FEDVERSIONMAJORID, FEDVERSIONMINORID, CONNECTIONVERSIONMAJORID, CONNECTIONVERSIONMINORID, DCUINFOVERSIONMAJORID, DCUINFOVERSIONMINORID, DCUPSUMAPVERSIONMAJORID, DCUPSUMAPVERSIONMINORID from ViewLastO2OPartitions where RUNNUMBER=%1 and PARTITIONNAME='%2'"
#define SELECTLATESTVERSIONS "select FECVERSIONMAJORID, FECVERSIONMINORID, FEDVERSIONMAJORID, FEDVERSIONMINORID, CONNECTIONVERSIONMAJORID, CONNECTIONVERSIONMINORID, DCUINFOVERSIONMAJORID, DCUINFOVERSIONMINORID, DCUPSUMAPVERSIONMAJORID, DCUPSUMAPVERSIONMINORID, MASKVERSIONMAJORID, MASKVERSIONMINORID  from ViewLastO2OPartitions where RUNNUMBER=%1 and PARTITIONNAME='%2'"


// queries for retrieving and changing FEDVALUES
//#define SELECTLATESTFEDVALUES "select distinct versionmajorid,versionminorid,readroute,fedmode,supermode from fedvalues,fed,partition where fedvalues.fedid=fed.fedid and fed.partitionid=partition.partitionid and partitionname='%1' order by versionmajorid,versionminorid"

// #define SELECTLATESTFEDVALUES "select allvalues.versionmajorid, allvalues.versionminorid, allvalues.readroute, allvalues.fedmode, allvalues.supermode from fedvalues allvalues join (select fedid,max(versionminorid) versionminorid, versionmajorid from fedvalues join fed using(fedid) join viewcurrentstate cs on cs.partitionname='%1' and cs.fedversionmajorid=fedvalues.versionmajorid and fedvalues.versionminorid<=cs.fedversionminorid group by fedid, versionmajorid) goodvalues on allvalues.fedid=goodvalues.fedid and allvalues.versionmajorid=goodvalues.versionmajorid and allvalues.versionminorid=goodvalues.versionminorid"

#define SELECTLATESTFEDVALUES "select distinct allvalues.readroute, allvalues.fedmode, allvalues.supermode from fedvalues allvalues join (select fedid,max(versionminorid) versionminorid, versionmajorid from fedvalues join fed using(fedid) join viewcurrentstate cs on cs.partitionname='%1' and cs.fedversionmajorid=fedvalues.versionmajorid and fedvalues.versionminorid<=cs.fedversionminorid group by fedid, versionmajorid) goodvalues on allvalues.fedid=goodvalues.fedid and allvalues.versionmajorid=goodvalues.versionmajorid and allvalues.versionminorid=goodvalues.versionminorid"


//#define EXECCHANGEREADROUTE   "exec TestPackages.changeFedParameter('%1','FEDVALUES','READROUTE','%2',0)"
#define EXECCHANGEREADROUTE   "BEGIN TestPackages.changeFedParameter('%1','FEDVALUES','READROUTE','%2',0); END;"

//#define EXECCHANGEMODE        "exec TestPackages.changeFedParameter('%1','FEDVALUES','FEDMODE',  '%2',0)"
#define EXECCHANGEMODE        "BEGIN TestPackages.changeFedParameter('%1','FEDVALUES','FEDMODE',  '%2',0); END;"

//#define EXECCHANGESUPERMODE   "exec TestPackages.changeFedParameter('%1','FEDVALUES','SUPERMODE','%2',0)"
#define EXECCHANGESUPERMODE   "BEGIN TestPackages.changeFedParameter('%1','FEDVALUES','SUPERMODE','%2',0); END;"

//#define EXECREFRESHCACHE      "exec TestPackages.TestPkgFedDownload('%1')"
#define EXECREFRESHCACHE      "BEGIN TestPackages.TestPkgFedDownload('%1'); END;"


// define read out routes
enum {SLINK64, VME};
// define read out modes
enum {VR = 100, ZS_NORMAL = 201, ZS_LITE = 202, ZS_FAKE_NORMAL = 203, ZS_FAKE_LITE = 204, SCOPE = 300};
// define return codes
//enum {RESULT_OK = 0, RESULT_UNKNOWN = 1, RESULT_ERROR = -1, RESULT_ALMOST_OK = 2, RESULT_WARNING = 100};
enum {RESULT_OK = 3, RESULT_ALMOST_OK = 2, RESULT_UNKNOWN = 1, RESULT_WARNING = 0, RESULT_ERROR = -1};


enum {MIN = 0, 
      TIBPART, TOBPART, TECPPART, TECMPART, 
      TIBRR, TOBRR, TECPRR, TECMRR, 
      TIBMSM, TOBMSM, TECPMSM, TECMMSM, 
      CONFTIB, CONFTOB, CONFTECP, CONFTECM, MAX
};

std::map<int, QComboBox*> configuration;

#define NONE_STRING "(none)"

//#define RESULT_OK 0
//#define RESULT_UNKNOWN 1
//#define RESULT_ERROR -1 // Should be negative

Q3StyleSheet* sheet;

using namespace oracle::occi;

void frmPrepareGlobal::init() {	
    addReadRoutes();
    addModesAndSuperModes();
    sheet = new Q3StyleSheet(this, "Style");
    textLabel1->setText("");
    latencyTib->setText("--");
    latencyTib->setEnabled(false);
    latencyTob->setText("--");
    latencyTob->setEnabled(false);
    latencyTecp->setText("--");
    latencyTecp->setEnabled(false);
    latencyTecm->setText("--");
    latencyTecm->setEnabled(false);

    configuration[TIBPART]  = cmbTib;
    configuration[TOBPART]  = cmbTob;
    configuration[TECPPART] = cmbTecp;
    configuration[TECMPART] = cmbTecm;
    
    configuration[TIBRR]    = comboBoxReadRouteTib;
    configuration[TOBRR]    = comboBoxReadRouteTob;
    configuration[TECPRR]   = comboBoxReadRouteTecp;
    configuration[TECMRR]   = comboBoxReadRouteTecm;

    configuration[TIBMSM]   = comboBoxMSMTib;
    configuration[TOBMSM]   = comboBoxMSMTob;
    configuration[TECPMSM]  = comboBoxMSMTecp;
    configuration[TECMMSM]  = comboBoxMSMTecm;


}


void frmPrepareGlobal::initializeGui()
{
    // 
    populatePartitions();
    checkVersions();

    setPartitions();    
    getCurrentConfiguration();
    cacheOldConfiguration();
    readoutChanged();

    //checkReadoutConfiguration();
    //btnApplyChanges->setEnabled(false);
    //btnRevertConfiguration->setEnabled(false);
    
}

void frmPrepareGlobal::addReadRoutes()
{
    addReadRouteTo(comboBoxReadRouteTib);	
    addReadRouteTo(comboBoxReadRouteTob);	
    addReadRouteTo(comboBoxReadRouteTecp);	
    addReadRouteTo(comboBoxReadRouteTecm);

}

void frmPrepareGlobal::addReadRouteTo(QComboBox* readRouteList)
{
    QString sLink = "SLINK64";
    QString vme  = "VME";
    readRouteList->insertItem(sLink);
    readRouteList->insertItem(vme);
}

void frmPrepareGlobal::addModesAndSuperModes()
{    
  readoutModes[100] = 0;//VR            ;
  readoutModes[201] = 1;//ZS_NORMAL	;
  readoutModes[202] = 2;//ZS_LITE	;
  readoutModes[203] = 3;//ZS_FAKE_NORMAL;
  readoutModes[204] = 4;//ZS_FAKE_LITE  ;
  readoutModes[300] = 5;//SCOPE         ;

  addModeAndSuperModeTo(comboBoxMSMTib);
  addModeAndSuperModeTo(comboBoxMSMTob);
  addModeAndSuperModeTo(comboBoxMSMTecp);
  addModeAndSuperModeTo(comboBoxMSMTecm);

}

void frmPrepareGlobal::addModeAndSuperModeTo(QComboBox* modeList)
{
    std::vector<QString> modesAndSuperModes;
    modesAndSuperModes.push_back("VIRGIN_RAW/NORMAL");
    modesAndSuperModes.push_back("ZERO_SUPPRESSION/NORMAL");
    modesAndSuperModes.push_back("ZERO_SUPPRESSION/ZERO_LITE");
    modesAndSuperModes.push_back("ZERO_SUPPRESSION/FAKE");
    modesAndSuperModes.push_back("ZERO_SUPPRESSION/FAKE_ZERO_LITE");
    modesAndSuperModes.push_back("SCOPE");    
    std::vector<QString>::const_iterator it = modesAndSuperModes.begin();    
    std::vector<QString>::const_iterator itEnd = modesAndSuperModes.end();
    for(; it != itEnd; ++it) {
	modeList->insertItem(*it);
    }
    
}

void frmPrepareGlobal::setPartitions()
{
    partitionForConfiguration(txtTib_2 ,/*cmbTib */ CONFTIB  );
    partitionForConfiguration(txtTob_2 ,/*cmbTob */ CONFTOB  );
    partitionForConfiguration(txtTecp_2,/*cmbTecp*/ CONFTECP );
    partitionForConfiguration(txtTecm_2,/*cmbTecm*/ CONFTECM );
}

void frmPrepareGlobal::addChoosePartitionName( QComboBox * myPartList )
{
    QString selectedItem;
    frmPartitions w;
    w.setModal(true);
    w.setDbConnection(dbConnection);
    w.populatePartitions();
    if (w.exec()==QDialog::Accepted) {
	selectedItem = w.selectedPartition();
	if (selectedItem!=""){
	    myPartList->insertItem(selectedItem);
	    myPartList->setCurrentItem(myPartList->count()-1);
	    checkVersions();
	}
    }
}

void frmPrepareGlobal::btnTibMore_clicked()
{ 
    addChoosePartitionName(cmbTib); 
    partitionForConfiguration(txtTib_2,/*cmbTib*/ CONFTIB );
    readoutChanged();
}

void frmPrepareGlobal::btnTobMore_clicked() 
{ 
    addChoosePartitionName(cmbTob); 
    partitionForConfiguration(txtTob_2,/*cmbTob*/ CONFTOB );	
    readoutChanged();
}

void frmPrepareGlobal::btnTecpMore_clicked() 
{ 
    addChoosePartitionName(cmbTecp); 
    partitionForConfiguration(txtTecp_2,/*cmbTecp*/ CONFTECP );    
    readoutChanged();
}

void frmPrepareGlobal::btnTecmMore_clicked() 
{ 
    addChoosePartitionName(cmbTecm); 
    partitionForConfiguration(txtTecm_2,/*cmbTecm*/ CONFTECM );
    readoutChanged();
}

QStringList frmPrepareGlobal::getUsedPartitionNames(QString subDetector, bool& used) {
    
    // In case of error it's better to display the partition than not
    used = true;
    
    QStringList partitionNames;
    if (dbConnection) {
	try {
	    QString myQuery;
	    myQuery = QString(SELECTPARTNAMES).arg(subDetector);
	    // std::cerr << myQuery.latin1() << std::endl; // debug
	    Statement* const s = dbConnection->createStatement( myQuery.latin1() );
	    ResultSet* const rset = s->executeQuery();	
	    int resultCounter = 0;
	    if (rset) {
		while (rset->next()) {
		    std::string partition = rset->getString(1);
		    // std::cerr << partition << std::endl; // debug
		    QString aPartitionName = QString(partition.c_str());
		    //std::cout << subDetector << " - " << aPartitionName.latin1() << std::endl; // debug
		    partitionNames.append(aPartitionName);
		    resultCounter++;
		}
	    }
	} catch (SQLException &e) {
	    std::cerr << "Unable to perform the query: " << e.what() << std::endl ;
	    return partitionNames;
	}
	
	try {
	    QString myQuery;
	    myQuery = QString(SELECTXCHECKNONE).arg(subDetector);
	    Statement* const s = dbConnection->createStatement( myQuery.latin1() );
	    ResultSet* const rset = s->executeQuery();	
	    //std::cout << myQuery.latin1() << std::endl;
	    int resultCounter = 0;
	    if (rset) {
		while (rset->next()) {
		    int partition = rset->getInt(1);
		    if (partition==1) {
			used = true;
		    } else if (partition==0) {
			used = false;
		    } else {
			// In case of error it's better to display the partition than not
			used = true;
			std::cerr << "ERROR: in frmPrepareGlobal::getUsedPartitionNames"
				<< "I found more that one partition for the same subdetector in the latest version set"
				<< std::endl;
		    }
		    resultCounter++;
		    // std::cout << subDetector << " - partition = " << partition << "; used = " << used << ";\n" ; // debug
		}
	    }
	    if (resultCounter!=1) {
		std::cerr << "ERROR: in frmPrepareGlobal::getUsedPartitionNames "
			<< "I found more that one answer to the SELECT query"
			<< std::endl;
		// In case of error it's better to display the partition than not
		used = true;
	    }
	} catch (SQLException &e) {
	    std::cerr << "Unable to perform the query: " << e.what() << std::endl ;
	    return partitionNames;
	} 
	
    } else {
	std::cerr << "ERROR: dbConnection id NULL in "
		<< "frmPrepareGlobal::getUsedPartitionNames(QString subDetector)"
		<< std::endl;
    } 
    return partitionNames;
}

void frmPrepareGlobal::populatePartition(QStringList partitionNames, QComboBox* cmbPart, bool usedPart) {
    for (QStringList::iterator it = partitionNames.begin(); it!=partitionNames.end(); ++it) {
	cmbPart->insertItem(*it);
    }
    cmbPart->setCurrentItem(cmbPart->count()-1);
    //  std::cout << "subdet " << usedPart << std::endl; // debug
    if (!usedPart) cmbPart->setCurrentText(NONE_STRING);
}

void frmPrepareGlobal::populatePartitions() {
    QStringList partitionNames;
    bool usedPart;
    
    for(size_t partition = 1; partition <= 4; ++partition) {
      configuration[partition]->clear();
      configuration[partition]->insertItem(NONE_STRING);
    }
    
    partitionNames = getUsedPartitionNames(TIB_ID, usedPart);
    populatePartition(partitionNames, cmbTib, usedPart);
    partitionNames = getUsedPartitionNames(TOB_ID, usedPart);
    populatePartition(partitionNames, cmbTob, usedPart);
    partitionNames = getUsedPartitionNames(TECP_ID, usedPart);
    populatePartition(partitionNames, cmbTecp, usedPart);
    partitionNames = getUsedPartitionNames(TECM_ID, usedPart);
    populatePartition(partitionNames, cmbTecm, usedPart);
}

void frmPrepareGlobal::setDbConnection( oracle::occi::Connection * newDbConnection )
{
    dbConnection=newDbConnection;
}


int frmPrepareGlobal::xCheckPartition( QString partitionName , QString subDetector)
{
    int result=RESULT_UNKNOWN;
    
    if (dbConnection!=0) {
	if (partitionName==NONE_STRING) {
	    try {
		QString myQuery;
		myQuery = QString(SELECTXCHECKNONE).arg(subDetector);
		//std::cerr << myQuery.latin1() << std::endl; // debug
		Statement* const s = dbConnection->createStatement( myQuery.latin1() );
		ResultSet* const rset = s->executeQuery();	
		int resultCounter = 0;
		if (rset) {
		    while (rset->next()) {
			int partition = rset->getInt(1);
			if (partition==0) {
			    result=RESULT_OK;
			} else {
			    result=RESULT_ERROR;
			}
			resultCounter++;
		    }
		}
		if (resultCounter!=1) {
		    std::cerr << "ERROR: in frmPrepareGlobal::xCheckPartition "
			    << "I found more that one answer to the SELECT query"
			    << std::endl;
		    result=RESULT_UNKNOWN;
		}
		
	    } catch (SQLException &e) {
		std::cerr << "ERROR: Unable to perform the query: " << e.what() << std::endl ;
		result=RESULT_UNKNOWN;
	    }
	} else if ((partitionName==O2O_ID)&&(subDetector==O2O_ID)) {
	    //std::cout << "Mark 2" << std::endl;
	    try {
		QString myQuery;
		myQuery = QString(SELECTXCHECKO2O).arg(subDetector);
		Statement* const s = dbConnection->createStatement( myQuery.latin1() );
		ResultSet* const rset = s->executeQuery();
		int resultCounter = 0;
		if (rset) {
		    while (rset->next()) {
			int partition = rset->getInt(1);
			if (partition==1) {
			    result=RESULT_OK;
			} else {
			    result=RESULT_ERROR;
			}
			resultCounter++;
		    }
		    
		}
		if (resultCounter!=1) {
		    std::cerr << "ERROR: in frmPrepareGlobal::xCheckPartition "
			    << "I found more that one answer to the SELECT query"
			    << std::endl;
		    result=RESULT_UNKNOWN;
		}
	    } catch (SQLException &e) {
		std::cerr << "ERROR: Unable to perform the query: " << e.what() << std::endl ;
		result=RESULT_UNKNOWN;
	    }
	    
	} else { 
	    //std::cout << "Mark 3" << std::endl;
	    try {
		QString myQuery;
		myQuery = QString(SELECTXCHECK).arg(partitionName);
		// std::cerr << myQuery.latin1() << std::endl; // debug
		Statement* const s = dbConnection->createStatement( myQuery.latin1() );
		ResultSet* const rset = s->executeQuery();	
		int resultCounter = 0;
		if (rset) {
		    while (rset->next()) {
			int partition = rset->getInt(1);
			if (partition==1) {
			    result=RESULT_OK;
			} else {
			    result=RESULT_ERROR;
			}
			resultCounter++;
		    }
		}
		if (resultCounter!=1) {
		    std::cerr << "ERROR: in frmPrepareGlobal::xCheckPartition "
			    << "I found more that one answer to the SELECT query"
			    << std::endl;
		    result=RESULT_UNKNOWN;
		}
		
	    } catch (SQLException &e) {
		std::cerr << "ERROR: Unable to perform the query: " << e.what() << std::endl ;
		result=RESULT_UNKNOWN;
	    }
	}
    } else {
	std::cerr << "ERROR: dbConnection is NULL "
		<< "in frmPrepareGlobal::xCheckPartition"
		<< std::endl;
	result=RESULT_UNKNOWN;
    }
    
    return result;
}

bool frmPrepareGlobal::preparePartitionState(QString partitionName, QString subDetector, int nextRunNumber) {
    bool result = false;
    if (dbConnection!=0) {
	try {
	    int existingEntries=99;
	    QString myQuery;
	    myQuery = QString(SELECTCHECKDUPLICATE)
		      .arg(partitionName)
		      .arg(nextRunNumber);
	    Statement* const checkExist = dbConnection->createStatement( myQuery.latin1() );
	    ResultSet* const rset = checkExist->executeQuery();
	    if (rset) {
		rset->next();
		existingEntries = rset->getInt(1);
		if (existingEntries>0) {
		    // std::cerr << "There is already " << existingEntries << " entry with the same properties. Skipping the insertion" << std::endl; // debug
		    result = true;
		}
		if (existingEntries>1) {
		    std::cerr << "ERROR: There are nore than 1 partition with the same state (" << existingEntries << "): either the check is wrong or the database is corrupted." << std::endl;
		}
	    } else {
		std::cerr << "Could not count existing entries in o2opartition table. Skipping insertion" << std::endl; // error message
		existingEntries = 99;
		result = false;
	    }
	    
	    if (existingEntries==0) {
		myQuery = QString(EXECINSERTOPERATION)
			  .arg(partitionName)
			  .arg(subDetector)
			  .arg(nextRunNumber);
		// std::cerr << myQuery.latin1() << std::endl; // debug
		Statement* const s = dbConnection->createStatement( myQuery.latin1() );
		s->execute();
		dbConnection->commit();
		dbConnection->terminateStatement(s);
		result=true;
	    }
	} catch (SQLException &e) {
	    std::cerr << "ERROR: Unable to perform the execute: " << e.what() << std::endl ;
	}
    } else {
	std::cerr << "ERROR dbConnection is NULL "
		<< "in frmPrepareGlobal::preparePartitionState" << std::endl;
    }
    return result;
}

bool frmPrepareGlobal::confirmO2O(int nextRunNumber) {
    bool result = false;
    if (dbConnection!=0) {
	try {
	    QString myQuery;
	    // TODO: check if the o2o was already confirmed
	    myQuery = QString(EXECCONFIRMO2O)
		      .arg(nextRunNumber);
	    // std::cerr << myQuery.latin1() << std::endl; // debug
	    Statement* const s = dbConnection->createStatement( myQuery.latin1() );
	    s->execute();
	    dbConnection->commit();
	    dbConnection->terminateStatement(s);
	    result=true;
	} catch (SQLException &e) {
	    std::cerr << "ERROR: Unable to perform the execute: " << e.what() << std::endl ;
	}
    } else {
	std::cerr << "ERROR dbConnection is NULL "
		<< "in frmPrepareGlobal::confirmO2O" << std::endl;
    }
    return result;
}


int frmPrepareGlobal::getRunNumbers ( int &nextRunNumber, int &lastIovRunNumber ) {
    int result=RESULT_UNKNOWN;
    
    nextRunNumber = -1;
    lastIovRunNumber = -1;
    
    
    if (dbConnection!=0) {
	try {
	    QString myQuery;
	    myQuery = QString(SELECTNEXTRUNNUMBER);
	    // std::cerr << myQuery.latin1() << std::endl; // debug
	    Statement* const s = dbConnection->createStatement( myQuery.latin1() );
	    ResultSet* const rset = s->executeQuery();	
	    int resultCounter = 0;
	    if (rset) {
		while (rset->next()) {
		    nextRunNumber = rset->getInt(1);
		    lastIovRunNumber = rset->getInt(2);
		    resultCounter++;
		}
	    }
	    if (resultCounter==1) {
		result=RESULT_OK;
	    } else {
		std::cerr << "ERROR: in frmPrepareGlobal::getRunNumbers "
			<< "I found more that one answer to the SELECT query"
			<< std::endl;
		result=RESULT_UNKNOWN;
	    }
	    
	} catch (SQLException &e) {
	    std::cerr << "ERROR: Unable to perform the query: " << e.what() << std::endl ;
	    result=RESULT_UNKNOWN;
	}
    } else {
	std::cerr << "ERROR dbConnection is NULL "
		<< "in frmPrepareGlobal::getRunNumbers" << std::endl;
    }
    return result; 
    
    // DEBUG 
    //return RESULT_OK;
    // END DEBUG
    
    
}

QString frmPrepareGlobal::createCfgLines(QString subDetectorShort, QString partitionName,
					 int fecMajor, int fecMinor,
					 int fedMajor, int fedMinor,
					 int cablingMajor, int cablingMinor,
					 int dcuMajor, int dcuMinor,
					 int maskMajor, int maskMinor,
					 int dcuPsuMajor, int dcuPsuMinor){
    
    QString cfgLines;
    
    cfgLines  = QString("\tPart%1= cms.untracked.PSet(\\\n").arg(subDetectorShort);
    cfgLines += QString("\t\tPartitionName = cms.untracked.string(\"%1\"),\\\n").arg(partitionName);
    cfgLines += QString("\t\tForceCurrentState = cms.untracked.bool(False),\\\n");
    cfgLines += QString("\t\tForceVersions = cms.untracked.bool(True), \\\n");
    cfgLines += QString("\t\tCablingVersion = cms.untracked.vuint32(%1,%2),\\\n").arg(cablingMajor).arg(cablingMinor);
    cfgLines += QString("\t\tFecVersion = cms.untracked.vuint32(%1,%2),\\\n").arg(fecMajor).arg(fecMinor);
    cfgLines += QString("\t\tFedVersion = cms.untracked.vuint32(%1,%2),\\\n").arg(fedMajor).arg(fedMinor);
    cfgLines += QString("\t\tDcuDetIdsVersion = cms.untracked.vuint32(%1,%2),\\\n").arg(dcuMajor).arg(dcuMinor);
    cfgLines += QString("\t\tMaskVersion = cms.untracked.vuint32(%1,%2),\\\n").arg(maskMajor).arg(maskMinor);
    cfgLines += QString("\t\tDcuPsuMapVersion = cms.untracked.vuint32(%1,%2)\\\n").arg(dcuPsuMajor).arg(dcuPsuMinor);
    cfgLines += QString("\t\t\\\n\t)\\\n");
    
    return cfgLines;
    
}

int frmPrepareGlobal::getVersions(QString partitionName, int runNumber,
				  int& fecMajor, int&  fecMinor,
				  int& fedMajor, int&  fedMinor,
				  int& cablingMajor, int& cablingMinor,
				  int& dcuMajor, int& dcuMinor,
				  int& maskMajor, int& maskMinor,
				  int& dcuPsuMajor, int& dcuPsuMinor){
    
    int result = RESULT_UNKNOWN;
    
    if (dbConnection!=0) {
	try {
	    QString myQuery;
	    myQuery = QString(SELECTLATESTVERSIONS).arg(runNumber).arg(partitionName);
	    // std::cerr << myQuery.latin1() << std::endl; // debug
	    Statement* const s = dbConnection->createStatement( myQuery.latin1() );
	    ResultSet* const rset = s->executeQuery();	
	    int resultCounter = 0;
	    if (rset) {
		while (rset->next()) {
		    fecMajor = rset->getInt(1);
		    fecMinor= rset->getInt(2);
		    fedMajor= rset->getInt(3);
		    fedMinor= rset->getInt(4);
		    cablingMajor= rset->getInt(5);
		    cablingMinor= rset->getInt(6);
		    dcuMajor= rset->getInt(7);
		    dcuMinor= rset->getInt(8);
		    dcuPsuMajor= rset->getInt(9);
		    dcuPsuMinor= rset->getInt(10);
		    maskMajor= rset->getInt(11);
		    maskMinor= rset->getInt(12);
		    
		    resultCounter++;
		}
	    }
	    if (resultCounter==1) {
		result=RESULT_OK;
	    } else {
		std::cerr << "ERROR: in frmPrepareGlobal::getVersions "
			<< "I found more that one answer to the SELECT query"
			<< std::endl;
		result=RESULT_UNKNOWN;
	    }
	    
	} catch (SQLException &e) {
	    std::cerr << "ERROR: Unable to perform the query: " << e.what() << std::endl ;
	    result=RESULT_UNKNOWN;
	}
    } else {
	std::cerr << "ERROR dbConnection is NULL "
		<< "in frmPrepareGlobal::getVersions" << std::endl;
    }
    
    return result;
    
}


QString frmPrepareGlobal::createCfgLines(QString subDetectorShort, QString partitionName, 
					 int runNumber, bool& isValid, bool &isFirst) {
    int fecMajor=0;
    int fecMinor=0;
    int fedMajor=0;
    int fedMinor=0;
    int cablingMajor=0;
    int cablingMinor=0;
    int dcuMajor=0;
    int dcuMinor=0;
    int dcuPsuMajor=0;
    int dcuPsuMinor=0;
    int maskMajor=0;
    int maskMinor=0;
    int result = RESULT_UNKNOWN;
    QString cfgLines=QString("");
    
    
    if (dbConnection!=0) {
	try {
	    QString myQuery;
	    myQuery = QString(SELECTLATESTVERSIONS).arg(runNumber).arg(partitionName);
	    // std::cerr << myQuery.latin1() << std::endl; // debug
	    Statement* const s = dbConnection->createStatement( myQuery.latin1() );
	    ResultSet* const rset = s->executeQuery();	
	    int resultCounter = 0;
	    if (rset) {
		while (rset->next()) {
		    fecMajor = rset->getInt(1);
		    fecMinor = rset->getInt(2);
		    fedMajor = rset->getInt(3);
		    fedMinor = rset->getInt(4);
		    cablingMajor = rset->getInt(5);
		    cablingMinor = rset->getInt(6);
		    dcuMajor = rset->getInt(7);
		    dcuMinor = rset->getInt(8);
		    dcuPsuMajor = rset->getInt(9);
		    dcuPsuMinor = rset->getInt(10);
		    maskMajor= rset->getInt(11);
		    maskMinor= rset->getInt(12);
		    resultCounter++;
		}
	    }
	    if (resultCounter==1) {
		result=RESULT_OK;
	    } else {
		std::cerr << "ERROR: in frmPrepareGlobal::getVersions "
			<< "I found more that one answer to the SELECT query"
			<< std::endl;
		result=RESULT_UNKNOWN;
	    }
	    
	} catch (SQLException &e) {
	    std::cerr << "ERROR: Unable to perform the query: " << e.what() << std::endl ;
	    result=RESULT_UNKNOWN;
	}
    } else {
	std::cerr << "ERROR dbConnection is NULL "
		<< "in frmPrepareGlobal::getVersions" << std::endl;
    }
    
    if (result==RESULT_OK) {
	
	//cfgLines  = QString::QString(Form("%s",(isFirst ? "\\\n" : ",\\\n") )); 
	cfgLines  = QString("%1").arg( (isFirst ? "\\\n" : ",\\\n")); 
	cfgLines += QString("\tPart%1= cms.untracked.PSet(\\\n").arg(subDetectorShort);
	cfgLines += QString("\t\tPartitionName = cms.untracked.string(\"%1\"),\\\n").arg(partitionName);
	cfgLines += QString("\t\tForceCurrentState = cms.untracked.bool(False),\\\n");
	cfgLines += QString("\t\tForceVersions = cms.untracked.bool(True), \\\n");
	cfgLines += QString("\t\tCablingVersion = cms.untracked.vuint32(%1,%2),\\\n").arg(cablingMajor).arg(cablingMinor);
	cfgLines += QString("\t\tFecVersion = cms.untracked.vuint32(%1,%2),\\\n").arg(fecMajor).arg(fecMinor);
	cfgLines += QString("\t\tFedVersion = cms.untracked.vuint32(%1,%2),\\\n").arg(fedMajor).arg(fedMinor);
	cfgLines += QString("\t\tDcuDetIdsVersion = cms.untracked.vuint32(%1,%2),\\\n").arg(dcuMajor).arg(dcuMinor);
	cfgLines += QString("\t\tMaskVersion = cms.untracked.vuint32(%1,%2),\\\n").arg(maskMajor).arg(maskMinor);
	cfgLines += QString("\t\tDcuPsuMapVersion = cms.untracked.vuint32(%1,%2)\\\n").arg(dcuPsuMajor).arg(dcuPsuMinor);
	cfgLines += QString("\t\t\\\n\t)");
	
	if(isFirst == true) isFirst = false;
	
    } else {
	isValid = false;
    }
    
    return cfgLines;
    
}


void frmPrepareGlobal::btnSetConf_clicked()
{    
    int nextRun, lastIovRun, result;
    
    QString partitionName;
    /*   int fecMajor; int fecMinor; */
    /*   int fedMajor; int fedMinor; */
    /*   int cablingMajor; int cablingMinor; */
    /*   int dcuMajor; int dcuMinor; */
    /*   int dcuPsuMajor; int dcuPsuMinor; */
    
    result = getRunNumbers(nextRun, lastIovRun);
    QString cfgLines=QString("");
    
    if (result == RESULT_UNKNOWN) {
	std::cerr << "ERROR in frmPrepareGlobal::getRunNumbers()." 
		<< "Could not retreive the next available global run number" << std::endl;
    } else {
	
	// Prepare the version control here
	if (cmbTib->currentText()!=NONE_STRING) {
	    partitionName=cmbTib->currentText();
	    preparePartitionState(partitionName, TIB_ID, nextRun);
	}
	if (cmbTob->currentText()!=NONE_STRING) {
	    partitionName=cmbTob->currentText();
	    preparePartitionState(partitionName, TOB_ID, nextRun);
	}
	if (cmbTecp->currentText()!=NONE_STRING) {
	    partitionName=cmbTecp->currentText();
	    preparePartitionState(partitionName, TECP_ID, nextRun);
	}
	if (cmbTecm->currentText()!=NONE_STRING) {
	    partitionName=cmbTecm->currentText();
	    preparePartitionState(partitionName, TECM_ID, nextRun);
	}
	
	// Retreive the versions to prepare the cfg file
	bool versionsOk = true;
	bool isFirst = true;
	if (cmbTib->currentText()!=NONE_STRING) {
	    partitionName=cmbTib->currentText();
	    cfgLines += createCfgLines ("TIBD", partitionName, nextRun, versionsOk, isFirst);
	}
	if (cmbTob->currentText()!=NONE_STRING) {
	    partitionName=cmbTob->currentText();
	    cfgLines += createCfgLines ("TOB", partitionName, nextRun, versionsOk, isFirst);
	}
	if (cmbTecp->currentText()!=NONE_STRING) {
	    partitionName=cmbTecp->currentText();
	    cfgLines += createCfgLines ("TECP", partitionName, nextRun, versionsOk, isFirst);
	}
	if (cmbTecm->currentText()!=NONE_STRING) {
	    partitionName=cmbTecm->currentText();
	    cfgLines += createCfgLines ("TECM", partitionName, nextRun, versionsOk, isFirst);
	}
	
	
	if (!versionsOk) {
	    statusBar()->message("ERROR: Unable to retreive the version I just wrote to DB");
	    return;
	}
	
	int checkVer = checkVersions(false);
	
	//std::cout << checkVer << std::endl;
	
	if (checkVer!=RESULT_OK && checkVer != RESULT_ALMOST_OK) {
	    statusBar()->message("Error in checking versions");
	    std::cerr << "Error checking versions" << std::endl;
	    return;
	}
	
	// Everything is fine: start the O2O
	if ( (versionsOk)&&(checkVer==RESULT_OK || checkVer == RESULT_ALMOST_OK ) ) {
	  //QStringList commandArgs20X;
	  QStringList commandArgs21X;
	  QStringList commandArgs22X;
	  QStringList commandArgs31X;
	  QString runNumber;
	  //QString cmsswVersion20X;
	  QString cmsswVersion21X;
	  QString cmsswVersion22X;
	  QString cmsswVersion31X;
	  
	  runNumber = QString("%1").arg(nextRun);
	  //cmsswVersion20X = "20x";
	  cmsswVersion21X = "21x";
	  cmsswVersion22X = "22x";
	  cmsswVersion31X = "31x";      
	  
	  commandArgs21X << PREPAREGLOBAL_SCRIPT
			 << runNumber << cfgLines << cmsswVersion21X;
	  
	  commandArgs31X << PREPAREGLOBAL_SCRIPT
			 << runNumber << cfgLines << cmsswVersion31X;
	  
	  // blindly launching 31X O2O, terminal will be kept open until the process
	  // is finished, but no return value is obtained
	  // -> kept for future usage, now in disuse
	  //launchTerminal(commandArgs31X, false);
	  
	  
	  // launch 31X O2O, wait for return value
	  if (launchTerminal(commandArgs31X, true) ) {

	    confirmO2O(nextRun);
	    checkVersions();
	    
	    // put back this  message if there are two versions of O2O running in parallel
	    //
	    //QMessageBox::information( this, "Prepare Global"
	    //			  "Information",	
	    //			  "The 31X O2O is sucessfully finished\n"
	    //			  "This typically means that the XXX O2O has also been successful\n"
	    //			  "If you are unsure, look at the log files in \n"
	    //			  "/opt/cmssw/shifter/o2o_2009/log_GR09_XXX_v1_hlt"
	    //			  , "OK", 0,
	    //			  0, 1 ) ;                                                            
	    
 
	  } else {
	    checkVersions();
	    statusBar()->message("O2O process failed");
	  }
	  
	}
    }
}

bool frmPrepareGlobal::launchTerminal( QStringList & commandList, bool modal )
{
    bool result = false;
    QProcess* proc = new QProcess( this );
    frmTerminalDialog* myTerminal = new frmTerminalDialog( this );
    myTerminal->setProcessPtr(proc);
    
    //proc->setArguments( commandList );

    connect( proc, SIGNAL(readyReadStdout()),
	     myTerminal, SLOT(readFromStdout()) );
    connect( proc, SIGNAL(processExited()),
	     myTerminal, SLOT(processFinished()) );


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), myTerminal, SLOT(executeWaitForReadyRead()));
    timer->start(100);

    proc->start( commandList.join(" ") );
    if ( !proc->waitForStarted() ) {
	// TODO: error handling
	// at least a message
	statusBar()->message("Could not start analysis");
	delete myTerminal;
	result = false;
    } else {
	if(modal) {
	    if (myTerminal->exec()==QDialog::Accepted) {
		result = true;
	    } else {
		result = false;
	    }
	} else {
	    myTerminal->show();
	    if (myTerminal->result()==QDialog::Accepted) {
		result = true;
	    } else {
		result = false;
	    }
	}

	// Open the fake terminal window and wait for return	
	//if (myTerminal->exec()==QDialog::Accepted) {
	//  result = true;
	//} else {
	//  result = false;
	//}

    }
    
    return result;
    
}

void frmPrepareGlobal::displayStatus(int newStatus ) {
    QString icon_name;
    QString statusMessage = "";
    
    switch (newStatus) {
    case RESULT_ERROR:
	icon_name = "round_error.png";
	//statusMessage = "Last O2O upload does not correspond to this configuration";
	break;
    case RESULT_UNKNOWN:
	icon_name = "round_question.png";
	//statusMessage = "ERROR: I encountered an unexpected problem. Please check the command line for possible detailed error messages";
	break;
    case RESULT_OK:
	icon_name = "round_ok.png";
	// statusMessage = "Last O2O upload corresponds to this configuration";
	// statusMessage = "Readout configuration appears to be ok";
	break;
    case RESULT_ALMOST_OK:
	icon_name = "round_almost_ok.png";
	//statusMessage = "Partitions are in correct state, waiting for O2O confirmation";
	break;
    case RESULT_WARNING:
      icon_name = "triangle_attention.png";
      //statusMessage = "This combination of Mode/Supermode and Readroute is NOT recommended, be sure that you really want this configuration!";
      break;
    default:
	icon_name = "round_question.png";
	std::cerr << "ERROR in frmPrepareGlobal::displayStatus unexpected status" << std::endl;
	break;
    }
    
    if(statusMessage != "")
      statusBar()->message(statusMessage);
    validReadOut->setPixmap(qPixmapFromMimeSource(icon_name));    
}

void frmPrepareGlobal::displayStatus(int newStatus, const int& nextRunNumber, const int& lastIovRunNumber, bool allowO2O ) {
    QString icon_name;
    QString statusMessage;
    
    switch (newStatus) {
    case RESULT_ERROR:
	icon_name = "round_error.png";
	statusMessage = "Last O2O upload does not correspond to this configuration";
	break;
    case RESULT_UNKNOWN:
	icon_name = "round_question.png";
	statusMessage = "ERROR: I encountered an unexpected problem. Please check the command line for possible detailed error messages";
	break;
    case RESULT_OK:
	icon_name = "round_ok.png";
	statusMessage = "Last O2O upload corresponds to this configuration";
	allowO2O = false;
	break;
    case RESULT_ALMOST_OK:
	icon_name = "round_almost_ok.png";
	statusMessage = "Partition(s) are in correct state, waiting for O2O confirmation";
	allowO2O = false;
	break;
    default:
	icon_name = "round_question.png";
	std::cerr << "ERROR in frmPrepareGlobal::displayStatus unexpected status" << std::endl;
	break;
    }
    
    statusBar()->message(statusMessage);
    linLastIov->setText(QString("%1").arg(lastIovRunNumber));
    linNextRun->setText(QString("%1").arg(nextRunNumber));
    lblUpdate->setPixmap(qPixmapFromMimeSource(icon_name));
    validReadOut->setPixmap(qPixmapFromMimeSource(icon_name));
    btnSetConf->setEnabled(allowO2O);
}

// If you just have to check that the previous version saving to the db was good
// then you use checkVersions( false ). If you want to know whether the O2O is to be 
// repeated or you can just run, then you call checkVersions () 
int frmPrepareGlobal::checkVersions( ) {
    return checkVersions(true);
}

int frmPrepareGlobal::checkVersions( bool checkO2O ){
    QString icon_name;
    int tibr, tobr, tecpr, tecmr, runnr, o2or;
    int nextRunNumber;
    int lastIovRunNumber;
    int resultState=RESULT_UNKNOWN;
    bool allowO2O = true;
    
    tibr = xCheckPartition(cmbTib->currentText(), TIB_ID);
    //std::cout << "tibr: " << tibr << std::endl; // debug
    tobr = xCheckPartition(cmbTob->currentText(), TOB_ID);
    //std::cout << "tobr: " << tobr << std::endl; // debug
    tecpr = xCheckPartition(cmbTecp->currentText(), TECP_ID);
    //std::cout << "tecpr: " << tecpr << std::endl; // debug   
    tecmr = xCheckPartition(cmbTecm->currentText(), TECM_ID);
    //std::cout << "tecmr: " << tecmr << std::endl; // debug   
    runnr=getRunNumbers(nextRunNumber, lastIovRunNumber);
    //std::cout << "runnr: " << runnr << std::endl; // debug 
    if (checkO2O) {
	o2or = xCheckPartition(O2O_ID, O2O_ID);
	if ((o2or==RESULT_OK)&&(nextRunNumber==lastIovRunNumber)) {
	    allowO2O = false;
	}
    } else {
	o2or = RESULT_UNKNOWN;
    }
    
    // DEBUG
    //o2or = RESULT_OK;
    // END DEBUG
        
    //std::cout << "o2or: " << o2or << std::endl; // debug
    
    if ((tibr==RESULT_OK)&&
	(tobr==RESULT_OK)&&
	(tecpr==RESULT_OK)&&
	(tecmr==RESULT_OK)&&
	(o2or==RESULT_OK)) {
	resultState=RESULT_OK;
    }
    
    if ((tibr==RESULT_ERROR)||
	(tobr==RESULT_ERROR)||
	(tecpr==RESULT_ERROR)||
	(tecmr==RESULT_ERROR)||
	(o2or==RESULT_ERROR)){
	resultState=RESULT_ERROR;
    }
    
    if ((tibr==RESULT_UNKNOWN) ||
	(tobr==RESULT_UNKNOWN) ||
	(tecpr==RESULT_UNKNOWN)||
	(tecmr==RESULT_UNKNOWN)||
	(runnr==RESULT_UNKNOWN)||
	(o2or==RESULT_UNKNOWN)){
	resultState=RESULT_UNKNOWN;
    }
    
    if ((tibr==RESULT_OK)&&
	(tobr==RESULT_OK)&&
	(tecpr==RESULT_OK)&&
	(tecmr==RESULT_OK)&&
	(o2or==RESULT_UNKNOWN)) {
      resultState=RESULT_ALMOST_OK;
    }

    // TODO: update the partition names if resultState==RESULT_OK
    displayStatus(resultState, nextRunNumber, lastIovRunNumber, allowO2O);
    
    return resultState;
}



int frmPrepareGlobal::getCurrentConfiguration()
{
  std::vector<QLabel*> labels;
  labels.push_back(txtTib_2);labels.push_back(txtTob_2);labels.push_back(txtTecp_2);labels.push_back(txtTecm_2);
  for(size_t i = 1; i<=4; ++i ) {
    iOldConfiguration[i+12] = getCurrentConfigurationFor(labels[i-1],configuration[i+4],configuration[i+8]);
  }

  return 1;

}


int frmPrepareGlobal::getCurrentConfigurationFor(QLabel *label, QComboBox* comboReadRoute, QComboBox* comboMSM )
{
  int returnValue = RESULT_UNKNOWN;

  QString lblText = label->text();

  QString subDetector = lblText.section( '(',1,1);
  subDetector.truncate((subDetector.length() - 1));
  
  std::string readroute, fedmode, supermode;

  if(subDetector == NONE_STRING || subDetector == "") 
    return RESULT_OK;

  if (dbConnection) {
    try {
      QString myQuery;
      myQuery = QString(SELECTLATESTFEDVALUES).arg(subDetector);
      // std::cerr << myQuery.latin1() << std::endl; // debug
      Statement* const s = dbConnection->createStatement( myQuery.latin1() );
      ResultSet* const rset = s->executeQuery();	
      //ResultSet* const rset = NULL;
      int resultCounter = 0;
      if (rset) {
	while (rset->next()) {

	  readroute      = rset->getString(1);
	  fedmode        = rset->getString(2);
	  supermode      = rset->getString(3);
	  resultCounter++;
	}
      }

      if(resultCounter == 1) {
	returnValue = RESULT_OK;
	label->setPaletteForegroundColor(Qt::black);
      } else {
	statusBar()->message("Partition is in a mixed state. Enter global running like this only if you know what you are doing");
	returnValue = RESULT_WARNING;
	label->setPaletteForegroundColor(Qt::red);
      }
      
      if(Debug::Inst()->getEnabled()) { 
	std::cout << "Found partition: "<< subDetector.ascii() << " with state " 
		  << readroute << ' ' << fedmode << ' ' << supermode << std::endl;
      }

      if(readroute == "VME") comboReadRoute->setCurrentItem(VME);
      else                   comboReadRoute->setCurrentItem(SLINK64); 
      
      updateMSM(comboMSM,fedmode.c_str(), supermode.c_str());
      

    } catch (SQLException &e) {
      std::cerr << "Unable to perform the query: " << e.what() << std::endl ;
      return RESULT_ERROR;
    }
  }
  
  return returnValue;
}

bool frmPrepareGlobal::updateMSM(QComboBox* combo, QString fedmode, QString supermode)
{
  int mode = 0;
  
  if(fedmode == "VIRGIN_RAW") {
    mode = 100;    
  } else if(fedmode == "ZERO_SUPPRESSION") {
    mode = 200;
    if(supermode == "NORMAL")         mode += 1;
    if(supermode == "ZERO_LITE")      mode += 2;
    if(supermode == "FAKE")           mode += 3;
    if(supermode == "FAKE_ZERO_LITE") mode += 4;
  } else if(fedmode == "SCOPE") {
    mode = 300;
  } else {
    return false;
  }
  
  if(readoutModes.find(mode) == readoutModes.end() ) 
    std::cerr << "OBS, did not find this mode/supermode combination" << std::endl;
  else 
    combo->setCurrentItem(readoutModes.find(mode)->second );

  return true;
}


void frmPrepareGlobal::checkReadoutConfiguration()
{
  std::vector<int> status;
  std::vector<int> partitionStatus;
  int valid = RESULT_OK;
  int partitionValid = RESULT_OK;
  
  status.clear();
  partitionStatus.clear();

  for(size_t partition = 1; partition <= 4; ++partition) {
    if(configuration[partition]->currentText() != NONE_STRING) {
      status.push_back( validCombination( configuration[partition+4], configuration[partition+8] ) );
      partitionStatus.push_back(iOldConfiguration[partition+12]);
    }
  }

  for(size_t stat = 0; stat < status.size(); ++stat) {
    // check for warning and error states, keep ''higher'' of the two
    if(status[stat] == RESULT_ERROR) {
      valid = RESULT_ERROR; 
    }
    if(status[stat] == RESULT_WARNING && valid != RESULT_ERROR) {
      valid = RESULT_WARNING; 
    }
  }

  for(size_t stat = 0; stat < partitionStatus.size(); ++stat) {

    // check for warning and error states, keep ''higher'' of the two
    if(partitionStatus[stat] == RESULT_ERROR) {
      partitionValid = RESULT_ERROR; 
    }
    if(partitionStatus[stat] == RESULT_WARNING && partitionValid != RESULT_ERROR) {
      partitionValid = RESULT_WARNING; 
    }
  }
  
  displayStatus( (valid < partitionValid ? valid : partitionValid) );
  if(partitionValid == RESULT_ERROR && valid == RESULT_ERROR ) {
    statusBar()->message("Both partition state and readout are problematic for global running");
  } else if(partitionValid == RESULT_WARNING && valid == RESULT_ERROR ) {
    statusBar()->message("Please make sure you really want to use this readout configuration");
  } else if(partitionValid == RESULT_WARNING && valid == RESULT_WARNING ) {
    statusBar()->message("Partition state and readout are not a priori suitable for global running, please check");
  } else if(partitionValid == RESULT_OK && valid == RESULT_WARNING ) {
    statusBar()->message("Partition state is OK but the readout is not the default");
  } else if(partitionValid == RESULT_OK && valid == RESULT_OK ) {
    statusBar()->message("Partition state and readout are ready for global running");
  } 

}

int frmPrepareGlobal::validCombination(QComboBox* comboReadRoute, QComboBox* comboMSM)
{
  int route = comboReadRoute->currentItem();
  int mode  = comboMSM      ->currentItem();
  
  if(route == SLINK64) {
    if(mode == readoutModes[ZS_NORMAL]      || 
       mode == readoutModes[ZS_LITE]        || 
       mode == readoutModes[ZS_FAKE_NORMAL] || 
       mode == readoutModes[ZS_FAKE_LITE]) {
      return RESULT_OK;
    } else {
      return RESULT_WARNING;
    }  
  } 
  if(route == VME) {
    return RESULT_WARNING;
    statusBar()->message("A partition which is potentially included in global running is in VME read route");
  }

  std::cerr << "OBS, you got an unknown readout route, this should never happen!" << std::endl;
  return RESULT_UNKNOWN; 
 
}


void frmPrepareGlobal::cacheOldConfiguration()
{
  for(int i = TIBRR; i <= TECMMSM; ++i) {
      iOldConfiguration[i] = configuration[i]->currentItem();
  }
  
}


void frmPrepareGlobal::btnAllToGlobal_clicked()
{
    // set route to SLINK64 
    setAllToReadout(SLINK64);
    // set Mode/SuperMode to ZS Normal
    setAllToModeSuperMode(readoutModes[ZS_NORMAL]);
    readoutChanged();
}


void frmPrepareGlobal::btnAllToLocal_clicked()
{
    // set route to VME
    //setAllToReadout(VME);
    setAllToModeSuperMode(readoutModes[VR]);
    readoutChanged();	
    //displayStatus(RESULT_WARNING);
}

void frmPrepareGlobal::setAllToModeSuperMode(int modeSuperMode)
{
  if(cmbTib->currentText()  != NONE_STRING) comboBoxMSMTib ->setCurrentItem(modeSuperMode);
  if(cmbTob->currentText()  != NONE_STRING) comboBoxMSMTob ->setCurrentItem(modeSuperMode);
  if(cmbTecp->currentText() != NONE_STRING) comboBoxMSMTecp->setCurrentItem(modeSuperMode);
  if(cmbTecm->currentText() != NONE_STRING) comboBoxMSMTecm->setCurrentItem(modeSuperMode);
}

void frmPrepareGlobal::setAllToReadout(int readoutMode)
{
  if(cmbTib->currentText()  != NONE_STRING) comboBoxReadRouteTib ->setCurrentItem(readoutMode);
  if(cmbTob->currentText()  != NONE_STRING) comboBoxReadRouteTob ->setCurrentItem(readoutMode);
  if(cmbTecp->currentText() != NONE_STRING) comboBoxReadRouteTecp->setCurrentItem(readoutMode);	
  if(cmbTecm->currentText() != NONE_STRING) comboBoxReadRouteTecm->setCurrentItem(readoutMode);
}

void frmPrepareGlobal::partitionForConfiguration(QLabel* label, /*QComboBox *cmb*/ int partitionLabel)
{
  //QString partition = cmb->currentText(); 
  QString partition = configuration[partitionLabel - 12]->currentText();
  if(partition != NONE_STRING) {
    QString text = label->text();
    text.truncate(text.find("  "));
    text = text + "  (" + partition + ")";
    // OBS!!: if map entry is 0, this will correspond to warning automatically
    // Does not have to correspond to partition state!!
    //if(oldConfiguration[(cmb->name())] == RESULT_WARNING )
    if(iOldConfiguration[partitionLabel] == RESULT_WARNING )
      label->setPaletteForegroundColor(Qt::red);
    label->setText(text);
  } else {
    QString text = label->text();
    text.truncate(text.find("  "));
    //text = text + "  (" + partition + ")";
    label->setText(text);
    label->setPaletteForegroundColor(Qt::black);
    // disable partition from editing
  }
}

int frmPrepareGlobal::showCurrentState()
{

  QDialog *dialog = new QDialog(this, "Current State after Upload",true);
  
  Q3VBoxLayout *layout = new Q3VBoxLayout(dialog);

  QLabel *dialogLabel = new QLabel(dialog);
  layout->addWidget(dialogLabel);
  Q3HBoxLayout *hLayout = new Q3HBoxLayout(layout);
  
  dialog->setMinimumSize(860,210);
  QPushButton* buttonOk     = new QPushButton( "&OK"     ,dialog, "buttonOk" );
  QPushButton* buttonCancel = new QPushButton( "&Cancel" ,dialog, "buttonCancel" );
  hLayout->addWidget(buttonOk);
  hLayout->addWidget(buttonCancel);

  connect( buttonOk, SIGNAL( clicked() ), dialog, SLOT( accept() ) );
  connect( buttonCancel, SIGNAL( clicked() ), dialog, SLOT( reject() ) );

  dialogLabel->setMinimumSize(850,200);
  dialogLabel->setPaletteBackgroundColor(Qt::white);
  dialogLabel->setScaledContents ( true );
  QString stringBEGIN = QString::QString("<qt>"
					 "<center><font color=\"red\", size=+2><b>CHANGE TO READOUT CONFIGURATION</b></font></center>"
					 "<center><font color=\"red\", size=+2><b>(PLEASE CHECK CAREFULLY!)</b></font></center>"
					 "<hr>"
					 "<table border=1>"
					 "<tr><th></th><th>READROUTE&nbsp;(old)</th><th>READROUTE&nbsp;(new)</th><th></th>"
					 "<th>MODE/SUPERMODE&nbsp;(old)</th><th>MODE/SUPERMODE&nbsp;(new) </th></tr>");
  std::vector<QString> stringPart;
  for(size_t i = 0; i < 4; ++i ) {
    stringPart.push_back(QString::QString("<td>%1</td><td>%2</td><td bgcolor=%4>%3</td>" ) );
  }

  QString stringEND  = QString::QString("</table></qt>");
				      
  QString string = stringBEGIN;
  for(size_t i = 1; i <=4; ++i ) {
    string += QString::QString("<tr>");
    QString partition  = configuration[i]->currentText(), 
      readRoute        = configuration[i+4]->currentText(), 
      oldReadRoute     = getReadRoute(iOldConfiguration[i+4]), 
      modeSuperMode    = configuration[i+8]->currentText(),
      oldModeSuperMode = configuration[i+8]->text(iOldConfiguration[i+8] );
    if(partition != NONE_STRING) {
      string += stringPart[i-1].arg(partition).arg(oldReadRoute).arg(readRoute).arg(getColor(readRoute, oldReadRoute));	
      string += stringPart[i-1].arg("").arg(oldModeSuperMode).arg(modeSuperMode).arg(getColor(modeSuperMode, oldModeSuperMode));
    } else {
      //std::cout << "Partition inactive, not displaying" << std::endl;
    }
    string += QString::QString("</tr><hr>");
  }
      
  string += stringEND;

  dialogLabel->setText(string);
    
  return dialog->exec();
  
}

QString frmPrepareGlobal::getColor(const QString &string1, const QString &string2) 
{
  return (string1 == string2 ? "#FFFFFF" : "#FF0000");
}


void frmPrepareGlobal::btnApplyChanges_clicked()
{

  if( showCurrentState() == QDialog::Accepted ) {
    if(Debug::Inst()->getEnabled()) { 
      std::cout << "Acknowledged" << std::endl;
    }
    submitChanges();
    
    cacheOldConfiguration();
    
    btnApplyChanges->setEnabled(false);
    btnRevertConfiguration->setEnabled(false);
    
    // remember to refresh DB cache for all configuration which have been updated one way or the other
    // does occi allow for multiple queries at the same time?
    
  } else {
    if(Debug::Inst()->getEnabled()) { 
      std::cerr << "Rejected" << std::endl;
    }
    return;
  }

}

void frmPrepareGlobal::submitChanges()
{
  int numPart = 0;
  for(size_t i = 1; i <= 4; ++i) {
    if(configuration[i]->currentText()     != NONE_STRING) {

      if(configuration[i+4]->currentItem() != iOldConfiguration[i+4] ) {
	setNewReadRoute(configuration[i+4],configuration[i]->currentText() );
      }
      if(configuration[i+8]->currentItem() != iOldConfiguration[i+8] ) {
	setNewModeSuperMode(configuration[i+8], configuration[i]->currentText() );
      }
      
      if( configuration[i+4]->currentItem() != iOldConfiguration[i+4] ||
	  configuration[i+8]->currentItem() != iOldConfiguration[i+8] ) {
	++numPart;      	
      }
      

    } else {
      //std::cout << "Partition inactive, not changing anything" << std::endl;
    }
  }
  // now refresh the DB cache for the partitions in question
  
  //QString message = "Refreshing DB Cache for %1 Partitions\nThis will take a while\n";
  //QMessageBox::information( this, "Prepare Run State"					      
  //			    "Information",						      
  //			    message.arg(numPart)
  //			    , "OK", 0,							        
  //			  0, 1 ) ;                                                            
  //QProgressDialog progress( this, "Refreshing...", true );
  //progress.setTotalSteps( numPart );
  //progress.show();
  //int step = 0;
  //for(size_t i = 1; i <= 4; ++i) {
  //  if(configuration[i]->currentText()     != NONE_STRING) {
  //    if( configuration[i+4]->currentItem() != iOldConfiguration[i+4] ||
  //	  configuration[i+8]->currentItem() != iOldConfiguration[i+8] ) {
  //	refreshDBCache(configuration[i]->currentText());
  //	//system("sleep 2");
  //	progress.setProgress(step);
  //	++step;
  //    }
  //  }
  //}
}



bool frmPrepareGlobal::setNewReadRoute(QComboBox* cmbBox, QString partition) 
{
  bool result = false;
  int readRoute = cmbBox->currentItem();
  QString sReadRoute = getReadRoute(readRoute);
  //if(Debug::Inst()->getEnabled()) { 
  //std::cout << "I will change the readroute of " << partition.ascii() << " to " << sReadRoute.ascii() << std::endl;
  //}
  QString myQuery;
  if (dbConnection!=0) {
    try {
      myQuery = QString(EXECCHANGEREADROUTE)
	.arg(partition)
	.arg(sReadRoute);
      if(Debug::Inst()->getEnabled()) { 
	std::cout << myQuery.latin1() << std::endl; // debug
      }
      //Statement* const s = dbConnection->createStatement( myQuery.latin1() );
      //s->execute();
      //dbConnection->commit();
      //dbConnection->terminateStatement(s);
      result=true;
      
    } catch (SQLException &e) {
      std::cerr << "ERROR: Unable to perform the execute: " << e.what() << std::endl ;
    }
  } else {
    std::cerr << "ERROR dbConnection is NULL "
	      << "in frmPrepareGlobal::preparePartitionState" << std::endl;
  }


  return result;
}

QString frmPrepareGlobal::getReadRoute(int readRoute)
{
  return (readRoute == SLINK64 ? "SLINK64" : "VME");
}

bool frmPrepareGlobal::setNewModeSuperMode(QComboBox* cmbBox, QString partition) 
{
  bool result = false;
  QString string = cmbBox->currentText();
  QString mode = string.section("/",0,0);
  QString supermode = string.section("/",1,1);
  if(Debug::Inst()->getEnabled()) { 
  //std::cout << "I will change the mode of " << partition.ascii() << ' ' 
  //<< "to " << mode.ascii() 
  //<< " and the supermode to " << supermode.ascii() << std::endl;
    
  }
  QString myQuery;
  if (dbConnection!=0) {
    try {
      myQuery = QString(EXECCHANGEMODE)
	.arg(partition)
	.arg(mode);
      if(Debug::Inst()->getEnabled()) { 
	std::cout << myQuery.latin1() << std::endl; // debug
      }
      //Statement* const s = dbConnection->createStatement( myQuery.latin1() );
      //s->execute();
      //dbConnection->commit();
      //dbConnection->terminateStatement(s);
      result=true;
      
    } catch (SQLException &e) {
      std::cerr << "ERROR: Unable to perform the execute: " << e.what() << std::endl ;
    }
    //
    // make separate statement of this
    try {
      myQuery = QString(EXECCHANGESUPERMODE)
	.arg(partition)
	.arg(supermode);
      if(Debug::Inst()->getEnabled()) { 
	std::cout << myQuery.latin1() << std::endl; // debug
      }
      //Statement* const s = dbConnection->createStatement( myQuery.latin1() );
      //s->execute();
      //dbConnection->commit();
      //dbConnection->terminateStatement(s);
      result=true;
      
    } catch (SQLException &e) {
      std::cerr << "ERROR: Unable to perform the execute: " << e.what() << std::endl ;
    }

  } else {
    std::cerr << "ERROR dbConnection is NULL "
	      << "in frmPrepareGlobal::preparePartitionState" << std::endl;
  }

  return result;
}


bool frmPrepareGlobal::refreshDBCache(const QString &partition)
{
  bool result = false;
  QString myQuery;

  if (dbConnection!=0) {
    try {
      myQuery = QString(EXECREFRESHCACHE)
	.arg(partition);
      //Statement* const s = dbConnection->createStatement( myQuery.latin1() );
      //s->execute();
      //dbConnection->commit();
      //dbConnection->terminateStatement(s);
      if(Debug::Inst()->getEnabled()) { 
	std::cout << myQuery.latin1() << std::endl;
      }
      
      result=true;
      
    } catch (SQLException &e) {
      std::cerr << "ERROR: Unable to perform the execute: " << e.what() << std::endl ;
    }
  } else {
    std::cerr << "ERROR dbConnection is NULL "
	      << "in frmPrepareGlobal::preparePartitionState" << std::endl;
  }
  
  return result;

}


void frmPrepareGlobal::readoutChanged()
{
  activatePartition(cmbTib, comboBoxReadRouteTib, comboBoxMSMTib);
  activatePartition(cmbTob, comboBoxReadRouteTob, comboBoxMSMTob);
  activatePartition(cmbTecp, comboBoxReadRouteTecp, comboBoxMSMTecp);
  activatePartition(cmbTecm, comboBoxReadRouteTecm, comboBoxMSMTecm);

  bool isChanged = false;
  for(size_t i = TIBRR; i <= TECMMSM; ++i) {
    if(iOldConfiguration[i] != configuration[i]->currentItem()) isChanged = true;
  }

  if(isChanged) {
    QMessageBox::warning( this, "Prepare Running State"					      
    			  "Warning",						      
			  "This feature is not yet connected to the DB\n"
			  "Changes made here are NOT propagated to the tracker"
    			  , "OK", 0,							      
    			  0, 1 ) ;                                                            

    btnApplyChanges->setEnabled(true);
    btnRevertConfiguration->setEnabled(true);
  } else {
    btnApplyChanges->setEnabled(false);
    btnRevertConfiguration->setEnabled(false);	
  }

  checkReadoutConfiguration();

}

void frmPrepareGlobal::activatePartition(QComboBox* subDet, QComboBox* readRoute, QComboBox* modeSuperMode)
{
  if(subDet->currentText() == NONE_STRING) {
    readRoute->setEnabled(false);
    modeSuperMode->setEnabled(false);
  } else {
    readRoute->setEnabled(true);
    modeSuperMode->setEnabled(true);
  }
  
}


void frmPrepareGlobal::cmbTib_activated( int )  
{ 
    checkVersions();
    partitionForConfiguration(txtTib_2,/*cmbTib*/ CONFTIB );	    
    revertConfiguration();
}

void frmPrepareGlobal::cmbTob_activated( int )  
{ 
    checkVersions(); 
    partitionForConfiguration(txtTob_2,/*cmbTob*/ CONFTOB );    
    revertConfiguration();
}

void frmPrepareGlobal::cmbTecp_activated( int ) 
{
    checkVersions(); 
    partitionForConfiguration(txtTecp_2,/*cmbTecp*/ CONFTECP );    
    revertConfiguration();
}

void frmPrepareGlobal::cmbTecm_activated( int ) 
{ 
    checkVersions(); 
    partitionForConfiguration(txtTecm_2,/*cmbTecm*/ CONFTECM );   
    revertConfiguration();
}

void frmPrepareGlobal::comboBoxReadRouteTib_activated( int )  { readoutChanged(); }
void frmPrepareGlobal::comboBoxReadRouteTob_activated( int )  { readoutChanged(); }
void frmPrepareGlobal::comboBoxReadRouteTecp_activated( int ) { readoutChanged(); }
void frmPrepareGlobal::comboBoxReadRouteTecm_activated( int ) { readoutChanged(); }

void frmPrepareGlobal::comboBoxMSMTib_activated( int )  { readoutChanged(); }
void frmPrepareGlobal::comboBoxMSMTob_activated( int )  { readoutChanged(); }
void frmPrepareGlobal::comboBoxMSMTecp_activated( int ) { readoutChanged(); }
void frmPrepareGlobal::comboBoxMSMTecm_activated( int ) { readoutChanged(); }


void frmPrepareGlobal::btnRevertConfiguration_clicked()
{
  revertConfiguration();
}

void frmPrepareGlobal::revertConfiguration()
{
  
  for(size_t i = TIBRR; i <= TECMMSM; ++i) {
    configuration[i]->setCurrentItem(iOldConfiguration[i]);
  }

  readoutChanged();

}
