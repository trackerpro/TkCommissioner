// Qt includes
#include <QtGui> 
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QProcess>

// project includes
#include "frmprepareglobal.h"
#include "frmterminaldialog.h"
#include "Debug.h"
#include "DbConnection.h"
#include <fstream>

// Defines

#define TIB_ID "TIB/TID"
#define TOB_ID "TOB"
#define TECP_ID "TEC+"
#define TECM_ID "TEC-"
#define O2O_ID "O2O"

#define PREPAREGLOBAL_SCRIPT "/nfshome0/trackerpro/o2o/scripts/prepareGlobal.sh"
//#define PREPAREGLOBAL_SCRIPT "/nfshome0/trackerpro/o2o/scripts/testDAQO2O.sh"
#define PREPAREO2OCONFIG_SCRIPT "/nfshome0/trackerpro/o2o/scripts/SiSitrpO2OConfig.py"

#define SELECTPARTNAMES "select partitionname, max(o2oid) as o2oid from partition, StateHistory, CurrentState, O2OPartition where StateHistory.partitionid=Partition.partitionId and StateHistory.stateHistoryId=CurrentState.stateHistoryId and Partition.partitionId = O2OPartition.partitionid and SUBDETECTOR = '%1' group by partitionname order by O2OID asc"

#define SELECTXCHECK "select PkgO2OPartition.getO2OXChecked('%1') from dual"
#define SELECTXCHECKNONE "select count(runnumber) from o2opartition where runnumber=(select max(runnumber) from o2opartition) and subdetector='%1'"
#define SELECTXCHECKO2O "select count(runnumber) from o2opartition where runnumber=(select max(runnumber) from o2opartition) and subdetector='%1'"

#define SELECTCHECKDUPLICATE "select count(runnumber) from partition, o2opartition where partition.partitionid = o2opartition.partitionid and partition.partitionname = '%1' and o2opartition.runnumber = %2"
#define SELECTCHECKDUPLICATESUB "select count(runnumber) from o2opartition where runnumber=%1 and subdetector='%2'"

#define SELECTNEXTRUNNUMBER "with nextglobalrun as (select max(runnumbertbl.runnumber+1) runnumber from CMS_RUNINFO.runnumbertbl), lasto2o as (select max(o2opartition.runnumber) runnumber from o2opartition) select nextglobalrun.runnumber, lasto2o.runnumber from nextglobalrun, lasto2o"

#define EXECINSERTOPERATION "BEGIN PkgO2OPartition.insertO2OOperation('%1', '%2', %3); END;"
#define EXECCONFIRMO2O "BEGIN PkgO2OPartition.insertO2OConfirmation(%1); END;"

#define SELECTLATESTVERSION "select RUNNUMBER, PARTITIONNAME, FECVERSIONMAJORID, FECVERSIONMINORID, FEDVERSIONMAJORID, FEDVERSIONMINORID, CONNECTIONVERSIONMAJORID, CONNECTIONVERSIONMINORID, DCUINFOVERSIONMAJORID, DCUINFOVERSIONMINORID, DCUPSUMAPVERSIONMAJORID, DCUPSUMAPVERSIONMINORID from ViewLastO2OPartitions" // unused 
#define SELECTLATESTVERSIONS "select FECVERSIONMAJORID, FECVERSIONMINORID, FEDVERSIONMAJORID, FEDVERSIONMINORID, CONNECTIONVERSIONMAJORID, CONNECTIONVERSIONMINORID, DCUINFOVERSIONMAJORID, DCUINFOVERSIONMINORID, DCUPSUMAPVERSIONMAJORID, DCUPSUMAPVERSIONMINORID, MASKVERSIONMAJORID, MASKVERSIONMINORID  from ViewLastO2OPartitions where RUNNUMBER=%1 and PARTITIONNAME='%2'"

#define SELECTLATESTFEDVALUES "select distinct allvalues.readroute, allvalues.fedmode, allvalues.supermode from fedvalues allvalues join (select fedid,max(versionminorid) versionminorid, versionmajorid from fedvalues join fed using(fedid) join viewcurrentstate cs on cs.partitionname='%1' and cs.fedversionmajorid=fedvalues.versionmajorid and fedvalues.versionminorid<=cs.fedversionminorid group by fedid, versionmajorid) goodvalues on allvalues.fedid=goodvalues.fedid and allvalues.versionmajorid=goodvalues.versionmajorid and allvalues.versionminorid=goodvalues.versionminorid"

#define EXECCHANGEREADROUTE   "BEGIN TestPackages.changeFedParameter('%1','FEDVALUES','READROUTE','%2',0); END;"
#define EXECCHANGEMODE        "BEGIN TestPackages.changeFedParameter('%1','FEDVALUES','FEDMODE',  '%2',0); END;"
#define EXECCHANGESUPERMODE   "BEGIN TestPackages.changeFedParameter('%1','FEDVALUES','SUPERMODE','%2',0); END;"
#define EXECREFRESHCACHE      "BEGIN TestPackages.TestPkgFedDownload('%1'); END;"

#define NONE_STRING "(none)"

enum {SLINK64, VME};
enum {VR = 100, ZS_NORMAL = 201, ZS_LITE = 202, ZS_FAKE_NORMAL = 203, ZS_FAKE_LITE = 204, SCOPE = 300};
enum {RESULT_OK = 3, RESULT_ALMOST_OK = 2, RESULT_UNKNOWN = 1, RESULT_WARNING = 0, RESULT_ERROR = -1};

enum {MIN = 0, 
      TIBPART, TOBPART, TECPPART, TECMPART, 
      TIBRR, TOBRR, TECPRR, TECMRR, 
      TIBMSM, TOBMSM, TECPMSM, TECMMSM, 
      CONFTIB, CONFTOB, CONFTECP, CONFTECM, MAX
};

std::map<int, QComboBox*> configuration;

PrepareGlobal::PrepareGlobal(QWidget * parent): 
    QMainWindow(parent)
{
    setupUi(this); 
    addReadRoutes();
    addModesAndSuperModes();

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

    populatePartitions();
    checkVersions();

    setPartitions();    
    getCurrentConfiguration();
    cacheOldConfiguration();
    readoutChanged();
    
}

PrepareGlobal::~PrepareGlobal() {
}

void PrepareGlobal::addReadRoutes() {
    addReadRouteTo(comboBoxReadRouteTib);	
    addReadRouteTo(comboBoxReadRouteTob);	
    addReadRouteTo(comboBoxReadRouteTecp);	
    addReadRouteTo(comboBoxReadRouteTecm);

}

void PrepareGlobal::addReadRouteTo(QComboBox* readRouteList) {
    QString sLink = "SLINK64";
    QString vme  = "VME";
    readRouteList->insertItem(readRouteList->count(), sLink);
    readRouteList->insertItem(readRouteList->count(), vme);
}

void PrepareGlobal::addModesAndSuperModes() {    
    readoutModes[100] = 0;//VR            ;
    readoutModes[201] = 1;//ZS_NORMAL	  ;
    readoutModes[202] = 2;//ZS_LITE	      ;
    readoutModes[203] = 3;//ZS_FAKE_NORMAL;
    readoutModes[204] = 4;//ZS_FAKE_LITE  ;
    readoutModes[300] = 5;//SCOPE         ;

    addModeAndSuperModeTo(comboBoxMSMTib);
    addModeAndSuperModeTo(comboBoxMSMTob);
    addModeAndSuperModeTo(comboBoxMSMTecp);
    addModeAndSuperModeTo(comboBoxMSMTecm);

}

void PrepareGlobal::addModeAndSuperModeTo(QComboBox* modeList) {
    std::vector<QString> modesAndSuperModes;
    modesAndSuperModes.push_back("VIRGIN_RAW/NORMAL");
    modesAndSuperModes.push_back("ZERO_SUPPRESSION/NORMAL");
    modesAndSuperModes.push_back("ZERO_SUPPRESSION/ZERO_LITE");
    modesAndSuperModes.push_back("ZERO_SUPPRESSION/FAKE");
    modesAndSuperModes.push_back("ZERO_SUPPRESSION/FAKE_ZERO_LITE");
    modesAndSuperModes.push_back("SCOPE");    
    std::vector<QString>::const_iterator it = modesAndSuperModes.begin();    
    std::vector<QString>::const_iterator itEnd = modesAndSuperModes.end();

    for(; it != itEnd; ++it) modeList->insertItem(modeList->count(), *it);
}

void PrepareGlobal::partitionForConfiguration(QLabel* label, int partitionLabel) {
    QString partition = configuration[partitionLabel - 12]->currentText();
    if (partition != NONE_STRING) {
        QString text = label->text();
        text.truncate(text.toStdString().find("  "));
        text = text + "  (" + partition + ")";
        if (iOldConfiguration[partitionLabel] == RESULT_WARNING) {
            QPalette pal = label->palette();
            pal.setColor(QPalette::WindowText, QColor(Qt::red));
            label->setPalette(pal);
            label->setText(text);
        }
        else label->setText(text);
    } 
    else {
        QString text = label->text();
        text.truncate(text.toStdString().find("  "));
        QPalette pal = label->palette();
        pal.setColor(QPalette::WindowText, QColor(Qt::red));
        label->setPalette(pal);
        label->setText(text);
    }
}

void PrepareGlobal::setPartitions() {
    partitionForConfiguration(txtTib_2 , CONFTIB  );
    partitionForConfiguration(txtTob_2 , CONFTOB  );
    partitionForConfiguration(txtTecp_2, CONFTECP );
    partitionForConfiguration(txtTecm_2, CONFTECM );
}

int PrepareGlobal::getCurrentConfiguration() {
    QVector<QLabel*> labels;
    labels.push_back(txtTib_2);
    labels.push_back(txtTob_2);
    labels.push_back(txtTecp_2);
    labels.push_back(txtTecm_2);

    for(size_t i = 1; i<=4; ++i ) iOldConfiguration[i+12] = getCurrentConfigurationFor(labels[i-1],configuration[i+4],configuration[i+8]);

    return 1;

}

int PrepareGlobal::getCurrentConfigurationFor(QLabel *label, QComboBox* comboReadRoute, QComboBox* comboMSM ) {
    int returnValue = RESULT_UNKNOWN;
    
    QString lblText = label->text();
    
    QString subDetector = lblText.section( '(',1,1);
    subDetector.truncate((subDetector.length() - 1));
    
    QString readroute, fedmode, supermode;
    
    if(subDetector == NONE_STRING || subDetector == "") return RESULT_OK;
    
    if (DbConnection::Inst()->dbConnected()) {
        QString myQuery;
        myQuery = QString(SELECTLATESTFEDVALUES).arg(subDetector);
        QSqlQuery query(myQuery);
    
        int resultCounter = 0;
        while (query.next()) {
            readroute      = query.value(0).toString();
            fedmode        = query.value(1).toString();
            supermode      = query.value(2).toString();
            resultCounter++;
        }
        
        if(resultCounter == 1) {
            returnValue = RESULT_OK;
            QPalette pal = label->palette();
            pal.setColor(QPalette::WindowText, QColor(Qt::black));
            label->setPalette(pal);
        } 
        else {
            statusBar()->showMessage("Partition is in a mixed state. Enter global running like this only if you know what you are doing");
            returnValue = RESULT_WARNING;
            QPalette pal = label->palette();
            pal.setColor(QPalette::WindowText, QColor(Qt::red));
            label->setPalette(pal);
        }
        
        if(Debug::Inst()->getEnabled()) {
            qDebug() << qPrintable(readroute) << ' ' << qPrintable(fedmode) << ' ' << qPrintable(supermode) << "\n";
            qDebug() << qPrintable(readroute) << ' ' << qPrintable(fedmode) << ' ' << qPrintable(supermode) << "\n";
        }    

        if(readroute == "VME") comboReadRoute->setCurrentIndex(VME);
        else                   comboReadRoute->setCurrentIndex(SLINK64); 
        
        updateMSM(comboMSM, fedmode.toStdString().c_str(), supermode.toStdString().c_str());
    }
    
    return returnValue;
}

bool PrepareGlobal::updateMSM(QComboBox* combo, QString fedmode, QString supermode) {
    int mode = 0;
  
    if(fedmode == "VIRGIN_RAW") {
        mode = 100;    
    } 
    else if(fedmode == "ZERO_SUPPRESSION") {
        mode = 200;
        if(supermode == "NORMAL")         mode += 1;
        if(supermode == "ZERO_LITE")      mode += 2;
        if(supermode == "FAKE")           mode += 3;
        if(supermode == "FAKE_ZERO_LITE") mode += 4;
    } 
    else if(fedmode == "SCOPE") {
        mode = 300;
    } 
    else {
        return false;
    }
    
    if(readoutModes.find(mode) == readoutModes.end() ) {
        if(Debug::Inst()->getEnabled()) qDebug() << "OBS, did not find this mode/supermode combination\n";
    }
    else combo->setCurrentIndex(readoutModes.find(mode)->second );

  return true;
}

void PrepareGlobal::addChoosePartitionName(QComboBox * myPartList) {
    QString selectedItem;
    Partitions w;
    w.setModal(true);
    w.populatePartitions();

    if (w.exec()==QDialog::Accepted) {
        selectedItem = w.selectedPartition();
        if (selectedItem != "") {
            myPartList->insertItem(myPartList->count(), selectedItem);
            myPartList->setCurrentIndex(myPartList->count()-1);
            checkVersions();
        }
    }
}

void PrepareGlobal::on_btnTibMore_clicked() { 
    addChoosePartitionName(cmbTib); 
    partitionForConfiguration(txtTib_2, CONFTIB );
    readoutChanged();
}

void PrepareGlobal::on_btnTobMore_clicked() { 
    addChoosePartitionName(cmbTob); 
    partitionForConfiguration(txtTob_2, CONFTOB );	
    readoutChanged();
}

void PrepareGlobal::on_btnTecpMore_clicked() { 
    addChoosePartitionName(cmbTecp); 
    partitionForConfiguration(txtTecp_2, CONFTECP );    
    readoutChanged();
}

void PrepareGlobal::on_btnTecmMore_clicked() { 
    addChoosePartitionName(cmbTecm); 
    partitionForConfiguration(txtTecm_2, CONFTECM );
    readoutChanged();
}

void PrepareGlobal::readoutChanged() {
    activatePartition(cmbTib, comboBoxReadRouteTib, comboBoxMSMTib);
    activatePartition(cmbTob, comboBoxReadRouteTob, comboBoxMSMTob);
    activatePartition(cmbTecp, comboBoxReadRouteTecp, comboBoxMSMTecp);
    activatePartition(cmbTecm, comboBoxReadRouteTecm, comboBoxMSMTecm);
    
    bool isChanged = false;
    for(size_t i = TIBRR; i <= TECMMSM; ++i) {
        if(iOldConfiguration[i] != configuration[i]->currentIndex()) isChanged = true;
    }
    
    if(isChanged) {
        QMessageBox::warning( this, "Prepare Running State"					      
                "Warning",						      
                "This feature is not yet connected to the DB\n"
                "Changes made here are NOT propagated to the tracker", 
                "OK", 0, 0, 1) ;                                                            
        
        btnApplyChanges->setEnabled(true);
        btnRevertConfiguration->setEnabled(true);
    } 
    else {
        btnApplyChanges->setEnabled(false);
        btnRevertConfiguration->setEnabled(false);	
    }
    
    checkReadoutConfiguration();

}

void PrepareGlobal::activatePartition(QComboBox* subDet, QComboBox* readRoute, QComboBox* modeSuperMode) {

    if (subDet->currentText() == NONE_STRING) {
        readRoute->setEnabled(false);
        modeSuperMode->setEnabled(false);
    } 
    else {
        readRoute->setEnabled(true);
        modeSuperMode->setEnabled(true);
    }
  
}

void PrepareGlobal::checkReadoutConfiguration() {
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
        if(status[stat] == RESULT_ERROR) valid = RESULT_ERROR; 
        if(status[stat] == RESULT_WARNING && valid != RESULT_ERROR) valid = RESULT_WARNING; 
    }
    
    for(size_t stat = 0; stat < partitionStatus.size(); ++stat) {
        if(partitionStatus[stat] == RESULT_ERROR) partitionValid = RESULT_ERROR; 
        if(partitionStatus[stat] == RESULT_WARNING && partitionValid != RESULT_ERROR) partitionValid = RESULT_WARNING; 
    }
    
    displayStatus( (valid < partitionValid ? valid : partitionValid) );
    if(partitionValid == RESULT_ERROR && valid == RESULT_ERROR )          statusBar()->showMessage("Both partition state and readout are problematic for global running");
    else if(partitionValid == RESULT_WARNING && valid == RESULT_ERROR )   statusBar()->showMessage("Please make sure you really want to use this readout configuration");
    else if(partitionValid == RESULT_WARNING && valid == RESULT_WARNING ) statusBar()->showMessage("Partition state and readout are not a priori suitable for global running, please check");
    else if(partitionValid == RESULT_OK && valid == RESULT_WARNING )      statusBar()->showMessage("Partition state is OK but the readout is not the default");
    else if(partitionValid == RESULT_OK && valid == RESULT_OK )           statusBar()->showMessage("Partition state and readout are ready for global running");

}


void PrepareGlobal::displayStatus(int newStatus ) {
    QString icon_name;
    QString statusMessage = "";
    
    switch (newStatus) {
    case RESULT_ERROR:
	icon_name = "images/round_error.png";
	//statusMessage = "Last O2O upload does not correspond to this configuration";
	break;
    case RESULT_UNKNOWN:
	icon_name = "images/round_question.png";
	//statusMessage = "ERROR: I encountered an unexpected problem. Please check the command line for possible detailed error messages";
	break;
    case RESULT_OK:
	icon_name = "images/round_ok.png";
	// statusMessage = "Last O2O upload corresponds to this configuration";
	// statusMessage = "Readout configuration appears to be ok";
	break;
    case RESULT_ALMOST_OK:
	icon_name = "images/round_almost_ok.png";
	//statusMessage = "Partitions are in correct state, waiting for O2O confirmation";
	break;
    case RESULT_WARNING:
      icon_name = "images/triangle_attention.png";
      //statusMessage = "This combination of Mode/Supermode and Readroute is NOT recommended, be sure that you really want this configuration!";
      break;
    default:
	icon_name = "images/round_question.png";
	if(Debug::Inst()->getEnabled()) qDebug() << "ERROR in PrepareGlobal::displayStatus unexpected status\n";
	break;
    }
    
    if(statusMessage != "")
      statusBar()->showMessage(statusMessage);
    validReadOut->setPixmap(QPixmap(icon_name));    
}

void PrepareGlobal::displayStatus(int newStatus, const int& nextRunNumber, const int& lastIovRunNumber, bool allowO2O ) {
    QString icon_name;
    QString statusMessage;
    
    switch (newStatus) {
    case RESULT_ERROR:
	icon_name = "images/round_error.png";
	statusMessage = "Last O2O upload does not correspond to this configuration";
	break;
    case RESULT_UNKNOWN:
	icon_name = "images/round_question.png";
	statusMessage = "ERROR: I encountered an unexpected problem. Please check the command line for possible detailed error messages";
	break;
    case RESULT_OK:
	icon_name = "images/round_ok.png";
	statusMessage = "Last O2O upload corresponds to this configuration";
	allowO2O = false;
	break;
    case RESULT_ALMOST_OK:
	icon_name = "images/round_almost_ok.png";
	statusMessage = "Partition(s) are in correct state, waiting for O2O confirmation";
	allowO2O = false;
	break;
    default:
	icon_name = "images/round_question.png";
	if(Debug::Inst()->getEnabled()) qDebug() << "ERROR in PrepareGlobal::displayStatus unexpected status\n";
	break;
    }
    
    statusBar()->showMessage(statusMessage);
    linLastIov->setText(QString("%1").arg(lastIovRunNumber));
    linNextRun->setText(QString("%1").arg(nextRunNumber));
    lblUpdate->setPixmap(QPixmap(icon_name));
    validReadOut->setPixmap(QPixmap(icon_name));
    btnSetConf->setEnabled(allowO2O);
}

int PrepareGlobal::validCombination(QComboBox* comboReadRoute, QComboBox* comboMSM) {
  int route = comboReadRoute->currentIndex();
  int mode  = comboMSM      ->currentIndex();
  
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
    statusBar()->showMessage("A partition which is potentially included in global running is in VME read route");
  }

  if(Debug::Inst()->getEnabled()) qDebug() << "OBS, you got an unknown readout route, this should never happen!\n";
  return RESULT_UNKNOWN; 
 
}


void PrepareGlobal::populatePartition(QStringList partitionNames, QComboBox* cmbPart, bool usedPart) {
    for (QStringList::iterator it = partitionNames.begin(); it!=partitionNames.end(); ++it) {
	cmbPart->insertItem(cmbPart->count(), *it);
    }
    cmbPart->setCurrentIndex(cmbPart->count()-1);
    //  std::cout << "subdet " << usedPart << std::endl; // debug
    if (!usedPart) cmbPart->setItemText(cmbPart->currentIndex(), NONE_STRING);
}

void PrepareGlobal::populatePartitions() {
    QStringList partitionNames;
    bool usedPart;
    
    for(size_t partition = 1; partition <= 4; ++partition) {
      configuration[partition]->clear();
      configuration[partition]->insertItem(configuration[partition]->count(), NONE_STRING);
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


QStringList PrepareGlobal::getUsedPartitionNames(QString subDetector, bool& used) {
    
    used = true;
    
    QStringList partitionNames;
    if (DbConnection::Inst()->dbConnected()) {
	    QString myQuery;
	    myQuery = QString(SELECTPARTNAMES).arg(subDetector);
        QSqlQuery query(myQuery);

		while (query.next()) {
		    QString aPartitionName = query.value(0).toString();
		    partitionNames.append(aPartitionName);
		}
	
	    myQuery = QString(SELECTXCHECKNONE).arg(subDetector);
        QSqlQuery query2(myQuery);
	    int resultCounter = 0;
		while (query2.next()) {
		    int partition = query2.value(0).toInt();
		    if (partition==1) used = true;
            else if (partition==0) used = false;
            else {
			    used = true;
			    if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: in PrepareGlobal::getUsedPartitionNames" << "I found more that one partition for the same subdetector in the latest version set\n";
		    }
		    resultCounter++;
		}
	    if (resultCounter!=1) {
		    if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: in PrepareGlobal::getUsedPartitionNames " << "I found more that one answer to the SELECT query\n";
		    used = true;
	    }
	
    } 

    else {
	    if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: dbConnection id NULL in " << "PrepareGlobal::getUsedPartitionNames(QString subDetector)\n";
    } 
    return partitionNames;
}



int PrepareGlobal::xCheckPartition( QString partitionName , QString subDetector) {

  int result=RESULT_UNKNOWN;  
  if (DbConnection::Inst()->dbConnected()) {
    if (partitionName==NONE_STRING) {
      QString myQuery;
      myQuery = QString(SELECTXCHECKNONE).arg(subDetector);
      QSqlQuery query(myQuery);
      int resultCounter = 0;
      while (query.next()) {
	int partition = query.value(0).toInt();
	if (partition==0) {
	  result=RESULT_OK;
	} else {
	  result=RESULT_ERROR;
	}
	resultCounter++;
      }
      if (resultCounter!=1) {
	if(Debug::Inst()->getEnabled()) qDebug()  << "ERROR: in PrepareGlobal::xCheckPartition I found more than one answer to the SELECT query\n";
	result=RESULT_UNKNOWN;
      }
      
    } 
    else if ((partitionName==O2O_ID)&&(subDetector==O2O_ID)) {
      QString myQuery;
      myQuery = QString(SELECTXCHECKO2O).arg(subDetector);
      QSqlQuery query(myQuery);
      bool rset = query.exec();
      int resultCounter = 0;
      if (rset) {
	while (query.next()) {
	  int partition = query.value(0).toInt();
	  if (partition==1) {
	    result=RESULT_OK;
	  } else {
	    result=RESULT_ERROR;
	  }
	  resultCounter++;
	}
            
      }
      if (resultCounter!=1) {
	if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: in PrepareGlobal::xCheckPartition I found more than one answer to the SELECT query\n";
	result=RESULT_UNKNOWN;
      }
    } 
    else { 
      QString myQuery;
      myQuery = QString(SELECTXCHECK).arg(partitionName);
      QSqlQuery query(myQuery);
      int resultCounter = 0;
      while (query.next()) {
	int partition = query.value(0).toInt();
	if (partition==1) {
	  result=RESULT_OK;
	} else {
	  result=RESULT_ERROR;
	}
	resultCounter++;
      }
      if (resultCounter!=1) {
	if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: in PrepareGlobal::xCheckPartition I found more than one answer to the SELECT query\n";
	result=RESULT_UNKNOWN;
      }
    }
  } 
  else {
    if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: dbConnection is NULL in PrepareGlobal::xCheckPartition\n";
    result=RESULT_UNKNOWN;
  }
  
  return result;
}

int PrepareGlobal::checkVersions() {
    return checkVersions(true);
}

int PrepareGlobal::checkVersions( bool checkO2O ){

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
  // std::cout << "tecmr: " << tecmr << std::endl; // debug   

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


int PrepareGlobal::getRunNumbers ( int &nextRunNumber, int &lastIovRunNumber ) {
  
  int result=RESULT_UNKNOWN;
  
  nextRunNumber = -1;
  lastIovRunNumber = -1;
  
  if (DbConnection::Inst()->dbConnected()) {
    QString myQuery;
    myQuery = QString(SELECTNEXTRUNNUMBER);
    QSqlQuery query(myQuery);
    int resultCounter = 0;
    while (query.next()) {
      nextRunNumber    = query.value(0).toInt();
      lastIovRunNumber = query.value(1).toInt();
      resultCounter++;
    }
    if (resultCounter==1) result=RESULT_OK;
    else {
      if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: in PrepareGlobal::getRunNumbers I found more that one answer to the SELECT query\n";
      result=RESULT_UNKNOWN;
    }
    
  } 
  else if(Debug::Inst()->getEnabled()) qDebug() << "ERROR dbConnection is NULL in PrepareGlobal::getRunNumbers\n";
  return result; 
}
    
void PrepareGlobal::cacheOldConfiguration() {
  for(int i = TIBRR; i <= TECMMSM; ++i) iOldConfiguration[i] = configuration[i]->currentIndex();
}

void PrepareGlobal::on_btnAllToGlobal_clicked()
{
    // set route to SLINK64 
    setAllToReadout(SLINK64);
    // set Mode/SuperMode to ZS Normal
    setAllToModeSuperMode(readoutModes[ZS_NORMAL]);
    readoutChanged();
}


void PrepareGlobal::on_btnAllToLocal_clicked()
{
    // set route to VME
    //setAllToReadout(VME);
    setAllToModeSuperMode(readoutModes[VR]);
    readoutChanged();	
    //displayStatus(RESULT_WARNING);
}

void PrepareGlobal::setAllToModeSuperMode(int modeSuperMode)
{
  if(cmbTib->currentText()  != NONE_STRING) comboBoxMSMTib ->setCurrentIndex(modeSuperMode);
  if(cmbTob->currentText()  != NONE_STRING) comboBoxMSMTob ->setCurrentIndex(modeSuperMode);
  if(cmbTecp->currentText() != NONE_STRING) comboBoxMSMTecp->setCurrentIndex(modeSuperMode);
  if(cmbTecm->currentText() != NONE_STRING) comboBoxMSMTecm->setCurrentIndex(modeSuperMode);
}

void PrepareGlobal::setAllToReadout(int readoutMode)
{
  if(cmbTib->currentText()  != NONE_STRING) comboBoxReadRouteTib ->setCurrentIndex(readoutMode);
  if(cmbTob->currentText()  != NONE_STRING) comboBoxReadRouteTob ->setCurrentIndex(readoutMode);
  if(cmbTecp->currentText() != NONE_STRING) comboBoxReadRouteTecp->setCurrentIndex(readoutMode);	
  if(cmbTecm->currentText() != NONE_STRING) comboBoxReadRouteTecm->setCurrentIndex(readoutMode);
}

bool PrepareGlobal::preparePartitionState(QString partitionName, QString subDetector, int nextRunNumber) {

  bool result = false;
  if (DbConnection::Inst()->dbConnected()) {
    int existingEntries=99;
    QString myQuery;
    myQuery = QString(SELECTCHECKDUPLICATE).arg(partitionName).arg(nextRunNumber);
    QSqlQuery query(myQuery);
    bool rset = query.exec();
    if (rset) {
      query.next();
      existingEntries = query.value(0).toInt();
      if (existingEntries>0) {
	// std::cerr << "There is already " << existingEntries << " entry with the same properties. Skipping the insertion" << std::endl; // debug
	result = true;
      }
      if (existingEntries>1) {
	if(Debug::Inst()->getEnabled()) qDebug()  << "ERROR: There are nore than 1 partition with the same state (" << existingEntries << "): either the check is wrong or the database is corrupted.\n";
      }
    } 
    else {
      if(Debug::Inst()->getEnabled()) qDebug()  << "Could not count existing entries in o2opartition table. Skipping insertion\n"; // error message
      existingEntries = 99;
      result = false;
    }
    
    if (existingEntries==0) {
      myQuery = QString(EXECINSERTOPERATION).arg(partitionName).arg(subDetector).arg(nextRunNumber);
      QSqlQuery query2(myQuery);
      query2.exec();
      DbConnection::Inst()->dbConnection().commit();
      result=true;
    }
  } 
  else {
    if(Debug::Inst()->getEnabled()) qDebug()  << "ERROR dbConnection is NULL in PrepareGlobal::preparePartitionState\n";
  }
  return result;
}

bool PrepareGlobal::confirmO2O(int nextRunNumber) {
  bool result = false;
  if (DbConnection::Inst()->dbConnected()) {
    QString myQuery;
    // TODO: check if the o2o was already confirmed
    myQuery = QString(EXECCONFIRMO2O).arg(nextRunNumber);
    // std::cerr << myQuery.latin1() << std::endl; // debug
    QSqlQuery query(myQuery);
    query.exec();
    DbConnection::Inst()->dbConnection().commit();
    result=true;
  } 
  else {
    if(Debug::Inst()->getEnabled()) qDebug()  << "ERROR dbConnection is NULL in PrepareGlobal::confirmO2O\n";
  }
  return result;
}

QString PrepareGlobal::createCfgLines(QString subDetectorShort, QString partitionName,
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

int PrepareGlobal::getVersions(QString partitionName, int runNumber,
			       int& fecMajor, int&  fecMinor,
			       int& fedMajor, int&  fedMinor,
			       int& cablingMajor, int& cablingMinor,
			       int& dcuMajor, int& dcuMinor,
			       int& maskMajor, int& maskMinor,
			       int& dcuPsuMajor, int& dcuPsuMinor){
    
    int result = RESULT_UNKNOWN;
    
    if (DbConnection::Inst()->dbConnected()) {
      QString myQuery;
      myQuery = QString(SELECTLATESTVERSIONS).arg(runNumber).arg(partitionName);
      QSqlQuery query(myQuery);
      bool rset = query.exec();	
      int resultCounter = 0;
      if (rset) {
	while (query.next()) {
	  fecMajor     = query.value(0).toInt();
	  fecMinor     = query.value(1).toInt();
	  fedMajor     = query.value(2).toInt();
	  fedMinor     = query.value(3).toInt();
	  cablingMajor = query.value(4).toInt();
	  cablingMinor = query.value(5).toInt();
	  dcuMajor     = query.value(6).toInt();
	  dcuMinor     = query.value(7).toInt();
	  dcuPsuMajor  = query.value(8).toInt();
	  dcuPsuMinor  = query.value(9).toInt();
	  maskMajor    = query.value(10).toInt();
	  maskMinor    = query.value(11).toInt();	  
	  resultCounter++;
	}
      }
      if (resultCounter==1) {
	result=RESULT_OK;
      } else {
	if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: in PrepareGlobal::getVersions "
						 << "I found more that one answer to the SELECT query\n";
		result=RESULT_UNKNOWN;
      }
    } else {
      if(Debug::Inst()->getEnabled()) qDebug() << "ERROR dbConnection is NULL "
					       << "in PrepareGlobal::getVersions\n";
    }
    
    return result;
    
}

QString PrepareGlobal::createCfgLines(QString subDetectorShort, QString partitionName,
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

  if (DbConnection::Inst()->dbConnected()) {
    QString myQuery;
    myQuery = QString(SELECTLATESTVERSIONS).arg(runNumber).arg(partitionName);
    QSqlQuery query(myQuery);
    bool rset = query.exec();
    int resultCounter = 0;
    if (rset) {
      while (query.next()) {
	fecMajor     = query.value(0).toInt();
	fecMinor     = query.value(1).toInt();
	fedMajor     = query.value(2).toInt();
	fedMinor     = query.value(3).toInt();
	cablingMajor = query.value(4).toInt();
	cablingMinor = query.value(5).toInt();
	dcuMajor     = query.value(6).toInt();
	dcuMinor     = query.value(7).toInt();
	dcuPsuMajor  = query.value(8).toInt();
	dcuPsuMinor  = query.value(9).toInt();
	maskMajor    = query.value(10).toInt();
	maskMinor    = query.value(11).toInt();
	resultCounter++;
      }
    }

    if (resultCounter==1) {
      result=RESULT_OK;
    } else {
      if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: in PrepareGlobal::getVersions "
					       << "I found more that one answer to the SELECT query\n";
      result=RESULT_UNKNOWN;
    }
    
  } else {
    if(Debug::Inst()->getEnabled()) qDebug() << "ERROR dbConnection is NULL "
					     << "in PrepareGlobal::getVersions\n";
  }
  
  if (result==RESULT_OK) {
    
    //fgLines  = QString("%1").arg( (isFirst ? "\\\n" : ",\\\n"));
    cfgLines += QString("\tPart%1= cms.untracked.PSet( \n").arg(subDetectorShort);
    cfgLines += QString("\t\tPartitionName = cms.untracked.string(\'%1\'),\n").arg(partitionName);
    cfgLines += QString("\t\tForceCurrentState = cms.untracked.bool(False),\n");
    cfgLines += QString("\t\tForceVersions = cms.untracked.bool(True),\n");
    cfgLines += QString("\t\tCablingVersion = cms.untracked.vuint32(%1,%2),\n").arg(cablingMajor).arg(cablingMinor);
    cfgLines += QString("\t\tFecVersion = cms.untracked.vuint32(%1,%2),\n").arg(fecMajor).arg(fecMinor);
    cfgLines += QString("\t\tFedVersion = cms.untracked.vuint32(%1,%2),\n").arg(fedMajor).arg(fedMinor);
    cfgLines += QString("\t\tDcuDetIdsVersion = cms.untracked.vuint32(%1,%2),\n").arg(dcuMajor).arg(dcuMinor);
    cfgLines += QString("\t\tMaskVersion = cms.untracked.vuint32(%1,%2),\n").arg(maskMajor).arg(maskMinor);
    cfgLines += QString("\t\tDcuPsuMapVersion = cms.untracked.vuint32(%1,%2),").arg(dcuPsuMajor).arg(dcuPsuMinor);
    cfgLines += QString("\t\t\n\t), \n");

    if(isFirst == true) isFirst = false;
    
  } else {
    isValid = false;
  }
  
  return cfgLines;
  
}

void PrepareGlobal::on_btnSetConf_clicked() {   

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
      if(Debug::Inst()->getEnabled()) qDebug() << "ERROR in PrepareGlobal::getRunNumbers()."
					       << "Could not retreive the next available global run number\n";
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
      statusBar()->showMessage("ERROR: Unable to retreive the version I just wrote to DB");
      return;
    }

    int checkVer = checkVersions(false);
    
    if (checkVer!=RESULT_OK && checkVer != RESULT_ALMOST_OK) {
      statusBar()->showMessage("Error in checking versions");
      if(Debug::Inst()->getEnabled()) qDebug() << "Error checking versions\n";
      return;
    }
   
    // Everything is fine: start the O2O
    if ( (versionsOk)&&(checkVer==RESULT_OK || checkVer == RESULT_ALMOST_OK ) ) {

      std::ofstream o2oConfigFile;
      o2oConfigFile.open(PREPAREO2OCONFIG_SCRIPT);
      o2oConfigFile << cfgLines.toStdString().c_str();
      o2oConfigFile.close();

      QStringList commandArgs;
      QString runNumber;

      runNumber = QString("%1").arg(nextRun);      
      commandArgs << PREPAREGLOBAL_SCRIPT << runNumber << PREPAREO2OCONFIG_SCRIPT ;

      // launch O2O, wait for return value       
      if (launchTerminal(commandArgs, true) ) {

	confirmO2O(nextRun);
	checkVersions();

        // put back this  message if there are two versions of O2O running in parallel
        //
        //QMessageBox::information( this, "Prepare Global"
        //            "Information",    
        //            "The 31X O2O is sucessfully finished\n"
        //            "This typically means that the XXX O2O has also been successful\n"
        //            "If you are unsure, look at the log files in \n"
        //            "/opt/cmssw/shifter/o2o_2009/log_GR09_XXX_v1_hlt"
        //            , "OK", 0,
        //            0, 1 ) ;                                                            
      
      } else {
	checkVersions();
	statusBar()->showMessage("O2O process failed");
      }      
    }
}

bool PrepareGlobal::launchTerminal( QStringList & commandList, bool modal ) {

  bool result = false;

  QProcess* proc = new QProcess( this );
  TkTerminalDialog* myTerminal = new TkTerminalDialog( this );
  myTerminal->setProcessPtr(proc);
   
  //proc->setArguments( commandList );  
  connect( proc, SIGNAL(readyReadStandardOutput()), myTerminal, SLOT(readFromStdout()) );
  connect( proc, SIGNAL(finished(int, QProcess::ExitStatus)), myTerminal, SLOT(processFinished(int, QProcess::ExitStatus)) );

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), myTerminal, SLOT(executeWaitForReadyRead()));
  timer->start(100);
  
  proc->start( commandList.join(" ") );
  
  if ( !proc->waitForStarted() ) {
    // TODO: error handling
    // at least a message
    statusBar()->showMessage("Could not start analysis");
    delete myTerminal;
    result = false;
  } else {
    if(modal) {
      if (myTerminal->exec() == QDialog::Accepted) {
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

int PrepareGlobal::showCurrentState() {

  QDialog *dialog = new QDialog(this);
  dialog->setModal(true);    
  dialog->setObjectName("Current State after Upload");    

  QVBoxLayout *layout = new QVBoxLayout(dialog);

  QLabel *dialogLabel = new QLabel(dialog);
  layout->addWidget(dialogLabel);
  QHBoxLayout *hLayout = new QHBoxLayout();
  layout->addLayout(hLayout);    

  dialog->setMinimumSize(860,210);
  QPushButton* buttonOk     = new QPushButton( "&OK"     ,dialog);
  QPushButton* buttonCancel = new QPushButton( "&Cancel" ,dialog);
  hLayout->addWidget(buttonOk);
  hLayout->addWidget(buttonCancel);

  connect( buttonOk, SIGNAL( clicked() ), dialog, SLOT( accept() ) );
  connect( buttonCancel, SIGNAL( clicked() ), dialog, SLOT( reject() ) );

  dialogLabel->setMinimumSize(850,200);
  QPalette pal = dialogLabel->palette();
  pal.setColor(QPalette::Background, QColor(Qt::white));
  dialogLabel->setPalette(pal);
  dialogLabel->setScaledContents ( true );
  QString stringBEGIN = QString("<qt>"
                     "<center><font color=\"red\", size=+2><b>CHANGE TO READOUT CONFIGURATION</b></font></center>"
                     "<center><font color=\"red\", size=+2><b>(PLEASE CHECK CAREFULLY!)</b></font></center>"
                     "<hr>"
                     "<table border=1>"
                     "<tr><th></th><th>READROUTE&nbsp;(old)</th><th>READROUTE&nbsp;(new)</th><th></th>"
                     "<th>MODE/SUPERMODE&nbsp;(old)</th><th>MODE/SUPERMODE&nbsp;(new) </th></tr>");
  std::vector<QString> stringPart;
  for(size_t i = 0; i < 4; ++i ) {
    stringPart.push_back(QString("<td>%1</td><td>%2</td><td bgcolor=%4>%3</td>" ) );
  }

  QString stringEND  = QString("</table></qt>");

  QString string = stringBEGIN;
  for(size_t i = 1; i <=4; ++i ) {
    string += QString("<tr>");
    QString partition  = configuration[i]->currentText(),
      readRoute        = configuration[i+4]->currentText(),
      oldReadRoute     = getReadRoute(iOldConfiguration[i+4]),
      modeSuperMode    = configuration[i+8]->currentText(),
      oldModeSuperMode = configuration[i+8]->itemText(iOldConfiguration[i+8] );
    if(partition != NONE_STRING) {
      string += stringPart[i-1].arg(partition).arg(oldReadRoute).arg(readRoute).arg(getColor(readRoute, oldReadRoute));
      string += stringPart[i-1].arg("").arg(oldModeSuperMode).arg(modeSuperMode).arg(getColor(modeSuperMode, oldModeSuperMode));
    } else {
      //std::cout << "Partition inactive, not displaying" << std::endl;
    }
    string += QString("</tr><hr>");
  }

  string += stringEND;

  dialogLabel->setText(string);

  return dialog->exec();

}

QString PrepareGlobal::getColor(const QString &string1, const QString &string2) {
  return (string1 == string2 ? "#FFFFFF" : "#FF0000");
}


void PrepareGlobal::on_btnApplyChanges_clicked() {

  if( showCurrentState() == QDialog::Accepted ) {
    if(Debug::Inst()->getEnabled()) qDebug() << "Acknowledged\n";
    submitChanges();

    cacheOldConfiguration();

    btnApplyChanges->setEnabled(false);
    btnRevertConfiguration->setEnabled(false);

    // remember to refresh DB cache for all configuration which have been updated one way or the other
    // does occi allow for multiple queries at the same time?

  } else {
    if(Debug::Inst()->getEnabled()) qDebug() << "Rejected\n";
    return;
  }

}

QString PrepareGlobal::getReadRoute(int readRoute) {
  return (readRoute == SLINK64 ? "SLINK64" : "VME");
}

void PrepareGlobal::submitChanges()
{
  int numPart = 0;
  for(size_t i = 1; i <= 4; ++i) {
    if(configuration[i]->currentText()     != NONE_STRING) {

      if(configuration[i+4]->currentIndex() != iOldConfiguration[i+4] ) {
    setNewReadRoute(configuration[i+4],configuration[i]->currentText() );
      }
      if(configuration[i+8]->currentIndex() != iOldConfiguration[i+8] ) {
    setNewModeSuperMode(configuration[i+8], configuration[i]->currentText() );
      }

      if( configuration[i+4]->currentIndex() != iOldConfiguration[i+4] ||
      configuration[i+8]->currentIndex() != iOldConfiguration[i+8] ) {
    ++numPart;
      }


    } else {
      //std::cout << "Partition inactive, not changing anything" << std::endl;
    }
  }
  // now refresh the DB cache for the partitions in question

  //QString message = "Refreshing DB Cache for %1 Partitions\nThis will take a while\n";
  //QMessageBox::information( this, "Prepare Run State"                       
  //                "Information",                            
  //                message.arg(numPart)
  //                , "OK", 0,                                  
  //              0, 1 ) ;                                                            
  //QProgressDialog progress( this, "Refreshing...", true );
  //progress.setTotalSteps( numPart );
  //progress.show();
  //int step = 0;
  //for(size_t i = 1; i <= 4; ++i) {
  //  if(configuration[i]->currentText()     != NONE_STRING) {
  //    if( configuration[i+4]->currentItem() != iOldConfiguration[i+4] ||
  //      configuration[i+8]->currentItem() != iOldConfiguration[i+8] ) {
  //    refreshDBCache(configuration[i]->currentText());
  //    //system("sleep 2");
  //    progress.setProgress(step);
  //    ++step;
  //    }
  //  }
  //}
}

bool PrepareGlobal::setNewReadRoute(QComboBox* cmbBox, QString partition)
{
  bool result = false;
  int readRoute = cmbBox->currentIndex();
  QString sReadRoute = getReadRoute(readRoute);
  //if(Debug::Inst()->getEnabled()) { 
  //std::cout << "I will change the readroute of " << partition.ascii() << " to " << sReadRoute.ascii() << std::endl;
  //}
  QString myQuery;
  if (DbConnection::Inst()->dbConnected()) {
      myQuery = QString(EXECCHANGEREADROUTE).arg(partition).arg(sReadRoute);
      if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(myQuery) << "\n"; // debug
      //Statement* const s = dbConnection->createStatement( myQuery.latin1() );
      //s->execute();
      //dbConnection->commit();
      //dbConnection->terminateStatement(s);
      result=true;

  } else {
    if(Debug::Inst()->getEnabled()) qDebug() << "ERROR dbConnection is NULL in PrepareGlobal::preparePartitionState\n";
  }


  return result;
}

bool PrepareGlobal::setNewModeSuperMode(QComboBox* cmbBox, QString partition)
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
  if (DbConnection::Inst()->dbConnected()) {
      myQuery = QString(EXECCHANGEMODE).arg(partition).arg(mode);
      if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(myQuery) << "\n"; // debug
      //Statement* const s = dbConnection->createStatement( myQuery.latin1() );
      //s->execute();
      //dbConnection->commit();
      //dbConnection->terminateStatement(s);
      result=true;

    //
    // make separate statement of this
      myQuery = QString(EXECCHANGESUPERMODE).arg(partition).arg(supermode);
      if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(myQuery) << "\n"; // debug
      //Statement* const s = dbConnection->createStatement( myQuery.latin1() );
      //s->execute();
      //dbConnection->commit();
      //dbConnection->terminateStatement(s);
      result=true;


  } else {
    if(Debug::Inst()->getEnabled()) qDebug() << "ERROR dbConnection is NULL "
          << "in PrepareGlobal::preparePartitionState" << "\n";
  }

  return result;
}

bool PrepareGlobal::refreshDBCache(const QString &partition)
{
  bool result = false;
  QString myQuery;

  if(Debug::Inst()->getEnabled()) {
      myQuery = QString(EXECREFRESHCACHE)
    .arg(partition);
      //Statement* const s = dbConnection->createStatement( myQuery.latin1() );
      //s->execute();
      //dbConnection->commit();
      //dbConnection->terminateStatement(s);
      if(Debug::Inst()->getEnabled()) qDebug() << qPrintable(myQuery) << "\n";

      result=true;

  } else {
    if(Debug::Inst()->getEnabled()) qDebug() << "ERROR dbConnection is NULL "
          << "in PrepareGlobal::preparePartitionState" << "\n";
  }

  return result;

}

void PrepareGlobal::on_cmbTib_activated( int )
{
    checkVersions();
    partitionForConfiguration(txtTib_2,/*cmbTib*/ CONFTIB );
    revertConfiguration();
}

void PrepareGlobal::on_cmbTob_activated( int )
{
    checkVersions();
    partitionForConfiguration(txtTob_2,/*cmbTob*/ CONFTOB );
    revertConfiguration();
}

void PrepareGlobal::on_cmbTecp_activated( int )
{
    checkVersions();
    partitionForConfiguration(txtTecp_2,/*cmbTecp*/ CONFTECP );
    revertConfiguration();
}

void PrepareGlobal::on_cmbTecm_activated( int )
{
    checkVersions();
    partitionForConfiguration(txtTecm_2,/*cmbTecm*/ CONFTECM );
    revertConfiguration();
}

void PrepareGlobal::on_comboBoxReadRouteTib_activated( int )  { readoutChanged(); }
void PrepareGlobal::on_comboBoxReadRouteTob_activated( int )  { readoutChanged(); }
void PrepareGlobal::on_comboBoxReadRouteTecp_activated( int ) { readoutChanged(); }
void PrepareGlobal::on_comboBoxReadRouteTecm_activated( int ) { readoutChanged(); }

void PrepareGlobal::on_comboBoxMSMTib_activated( int )  { readoutChanged(); }
void PrepareGlobal::on_comboBoxMSMTob_activated( int )  { readoutChanged(); }
void PrepareGlobal::on_comboBoxMSMTecp_activated( int ) { readoutChanged(); }
void PrepareGlobal::on_comboBoxMSMTecm_activated( int ) { readoutChanged(); }


void PrepareGlobal::on_btnRevertConfiguration_clicked()
{
  revertConfiguration();
}

void PrepareGlobal::revertConfiguration()
{

  for(size_t i = TIBRR; i <= TECMMSM; ++i) {
    configuration[i]->setCurrentIndex(iOldConfiguration[i]);
  }

  readoutChanged();

}

void PrepareGlobal::on_btnQuit_clicked() {

   close(); 

}
