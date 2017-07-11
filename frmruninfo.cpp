#include "frmruninfo.h"
#include "frmterminaldialog.h"
#include "TreeBuilder.h"
#include "cmssw/SiStripFedKey.h"
#include <sstream>
#include <fstream>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QTextCursor>
#include <QTextTable>
#include <QMessageBox>

RunInfo::RunInfo(QWidget* parent):
    QConnectedTabWidget(parent),
    currentRun(""),
    currentPartition("")
{
    setupUi(this);
}

RunInfo::~RunInfo() {
}

void RunInfo::setCurrentRun(QString r) {
    currentRun = r;
}

void RunInfo::setCurrentPartition(QString p) {
    currentPartition = p;
}

void RunInfo::setTree(TTree* t) {
    tree = t;
}

void RunInfo::setSelMap(QVector<int> sm) {
    for (int i = 0; i < sm.size(); i++) selMap.push_back(sm[i]);
}

QString RunInfo::getCurrentRun() {
    return currentRun;
}

QString RunInfo::getCurrentPartition() {
    return currentPartition;
}

bool RunInfo::displayRunInfo() {

    if (currentRun == "") return false;

    else if (currentRun.toInt() == sistrip::MULTIPART) {

        if (QMessageBox::question(NULL, QObject::tr("Confirmation"), QObject::tr("You are going to perform Timing O2O. Are you sure you want to continue?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return false;
      
        QStringList parts = currentPartition.split("*");
        QVector<QRunId> runIds;       
 
        if (parts.size() != 5) {
            if(Debug::Inst()->getEnabled()) qDebug() << "Unable to deconstruct 4 partition names for multi-partition view\n";
            return false;
        }

        for (int i = 1; i < parts.size(); i++) {
            QString part = parts.at(i);
            QStringList subparts = part.split("#");
            if (subparts.size() != 2) {
                if(Debug::Inst()->getEnabled()) qDebug() << "Unable to deconstruct 4 partition names and run numbers for multi-partition view\n";
                return false;
            }
            runIds.push_back(QRunId(subparts[0], subparts[1]));
        }

        std::stringstream infoss;
        std::stringstream partss;            
        std::stringstream skipss;            

        infoss << "<html>" << std::endl;
        infoss << "<b>Timing O2O : </b>" << "<br/>";

        if (parts.at(0) != "TIMING") {
            if(Debug::Inst()->getEnabled()) qDebug() << "Run type should be TIMING in order to perform TIMING O2O\n";


            infoss << "<b>Run type :  </b>" << qPrintable(parts.at(0)) << "<br/>";
            infoss << "<b>Cannot perform Timing O2O unless run type is TIMING  </b>" << "<br/>";
            infoss << "</html>" << std::endl;
            
            QTextCursor cursor(txtCurRunInfo->textCursor());
            cursor.insertHtml(infoss.str().c_str());
            return false;
        }

        for (int i = 0; i < runIds.size(); i++) {
            QString partition, modeDescription, creationDate, startTime, endTime;
            QString fecMajor, fecMinor, fedMajor, fedMinor, connMajor, connMinor, dcuinfoMajor, dcuinfoMinor, dcumapMajor, dcumapMinor, maskMajor, maskMinor;
            QString analMajor, analMinor;
            
            QString tablename = "viewallrun";
            
            std::stringstream queryss;
            queryss << "select distinct ";
            queryss << "partitionname, ";
            queryss << "modedescription, ";
            queryss << "to_char( starttime,'yyyy-mm-dd' ) as creationdate, ";
            queryss << "to_char( starttime, 'hh24:mi:ss' ) as creationtime, ";
            queryss << "to_char( endtime, 'hh24:mi:ss' ) as finishtime, ";
            queryss << "fecversionmajorid, ";
            queryss << "fecversionminorid, ";
            queryss << "fedversionmajorid, ";
            queryss << "fedversionminorid, ";
            queryss << "connectionversionmajorid, ";
            queryss << "connectionversionminorid, ";
            queryss << "dcuinfoversionmajorid, ";
            queryss << "dcuinfoversionminorid, ";
            queryss << "dcupsumapversionmajorid, ";
            queryss << "dcupsumapversionminorid, ";
            queryss << "maskversionmajorid, ";
            queryss << "maskversionminorid ";
            queryss << "from ";
            queryss <<  tablename.toStdString();
            queryss << " where runnumber=" << qPrintable(runIds[i].second);
        
            QString myQuery(queryss.str().c_str());
            QSqlQuery query(myQuery);
            
            while (query.next()) {
                partition       = query.value(0).toString();
                modeDescription = query.value(1).toString();
                creationDate    = query.value(2).toString();
                startTime       = query.value(3).toString();
                endTime         = query.value(4).toString();
                fecMajor        = query.value(5).toString();
                fecMinor        = query.value(6).toString();
                fedMajor        = query.value(7).toString();
                fedMinor        = query.value(8).toString();
                connMajor       = query.value(9).toString();
                connMinor       = query.value(10).toString();
                dcuinfoMajor    = query.value(11).toString();
                dcuinfoMinor    = query.value(12).toString();
                dcumapMajor     = query.value(13).toString();
                dcumapMinor     = query.value(14).toString();
                maskMajor       = query.value(15).toString();
                maskMinor       = query.value(16).toString();
            }

            tablename = "analysis";
            queryss.str("");
            queryss << "select distinct ";
            queryss << "versionmajorid, ";
            queryss << "versionminorid ";
            queryss << "from ";
            queryss <<  tablename.toStdString();
            queryss << " where analysisid = ( select max(analysisid) from analysis where runnumber = " << qPrintable(runIds[i].second) << ")";

            myQuery = queryss.str().c_str();
            QSqlQuery query2(myQuery);

            while (query2.next()) {
                analMajor       = query2.value(0).toString();
                analMinor       = query2.value(1).toString();
            }

            QString pname = "";
            if      (partition.startsWith("TI")) pname = "PartTIBD";
            else if (partition.startsWith("TO")) pname = "PartTOB";
            else if (partition.startsWith("TP")) pname = "PartTECP";
            else if (partition.startsWith("TM")) pname = "PartTECM";
            infoss << "\t" << qPrintable(pname) << " = cms.untracked.PSet("      << std::endl << "<br/>";
            infoss << "\t\tForceCurrentState = cms.untracked.bool(False)," << std::endl << "<br/>";
            infoss << "\t\tForceVersions = cms.untracked.bool(True),"      << std::endl << "<br/>";
            infoss << "\t\tPartitionName = cms.untracked.string(\'"        << qPrintable(partition)        << "\')," << std::endl << "<br/>";
            infoss << "\t\tRunNumber = cms.untracked.uint32("              << qPrintable(runIds[i].second) << "),"   << std::endl << "<br/>";
            infoss << "\t\tCablingVersion = cms.untracked.vuint32("        << qPrintable(connMajor)        << ", "   << qPrintable(connMinor)     << ")," << std::endl << "<br/>";
            infoss << "\t\tFecVersion = cms.untracked.vuint32("            << qPrintable(fecMajor)         << ", "   << qPrintable(fecMinor)      << ")," << std::endl << "<br/>";
            infoss << "\t\tFedVersion = cms.untracked.vuint32("            << qPrintable(fedMajor)         << ", "   << qPrintable(fedMinor)      << ")," << std::endl << "<br/>";
            infoss << "\t\tDcuDetIdsVersion = cms.untracked.vuint32("      << qPrintable(dcuinfoMajor)     << ", "   << qPrintable(dcuinfoMinor)  << ")," << std::endl << "<br/>";
            infoss << "\t\tDcuPsuMapVersion = cms.untracked.vuint32("      << qPrintable(dcumapMajor)      << ", "   << qPrintable(dcumapMinor)   << ")," << std::endl << "<br/>";
            infoss << "\t\tMaskVersion = cms.untracked.vuint32("           << qPrintable(maskMajor)        << ", "   << qPrintable(maskMinor)     << ")," << std::endl << "<br/>";
            infoss << "\t\tApvTimingVersion = cms.untracked.vuint32("      << qPrintable(analMajor)        << ", "   << qPrintable(analMinor)     << ")," << std::endl << "<br/>";
            infoss << "\t)," << std::endl << "<br/>" << "<br/>";

            partss << "\t" << qPrintable(pname) << " = cms.untracked.PSet("      << std::endl;
            partss << "\t\tForceCurrentState = cms.untracked.bool(False)," << std::endl;
            partss << "\t\tForceVersions = cms.untracked.bool(True),"      << std::endl;
            partss << "\t\tPartitionName = cms.untracked.string(\'"        << qPrintable(partition)        << "\')," << std::endl;
            partss << "\t\tRunNumber = cms.untracked.uint32("              << qPrintable(runIds[i].second) << "),"   << std::endl;
            partss << "\t\tCablingVersion = cms.untracked.vuint32("        << qPrintable(connMajor)        << ", "   << qPrintable(connMinor)     << ")," << std::endl;
            partss << "\t\tFecVersion = cms.untracked.vuint32("            << qPrintable(fecMajor)         << ", "   << qPrintable(fecMinor)      << ")," << std::endl;
            partss << "\t\tFedVersion = cms.untracked.vuint32("            << qPrintable(fedMajor)         << ", "   << qPrintable(fedMinor)      << ")," << std::endl;
            partss << "\t\tDcuDetIdsVersion = cms.untracked.vuint32("      << qPrintable(dcuinfoMajor)     << ", "   << qPrintable(dcuinfoMinor)  << ")," << std::endl;
            partss << "\t\tDcuPsuMapVersion = cms.untracked.vuint32("      << qPrintable(dcumapMajor)      << ", "   << qPrintable(dcumapMinor)   << ")," << std::endl;
            partss << "\t\tMaskVersion = cms.untracked.vuint32("           << qPrintable(maskMajor)        << ", "   << qPrintable(maskMinor)     << ")," << std::endl;
            partss << "\t\tApvTimingVersion = cms.untracked.vuint32("      << qPrintable(analMajor)        << ", "   << qPrintable(analMinor)     << ")," << std::endl;
            partss << "\t)," << std::endl;

        }

        if (tree != NULL && selMap.size() > 0) {

            TBranch* bdevId          = tree->GetBranch("DeviceId");
            TBranch* bdetId          = tree->GetBranch("Detid");
            TBranch* bFecCrate       = tree->GetBranch("FecCrate");
            TBranch* bFec            = tree->GetBranch("Fec");
            TBranch* bRing           = tree->GetBranch("Ring");
            TBranch* bCcu            = tree->GetBranch("Ccu");
            TBranch* bCcuArrangement = tree->GetBranch("CcuArrangement");
            TBranch* bI2CChannel     = tree->GetBranch("I2CChannel");
            TBranch* bI2CAddress     = tree->GetBranch("I2CAddress");
            TBranch* blasChan        = tree->GetBranch("lasChan");
            TBranch* bFedId          = tree->GetBranch("FedId");
            TBranch* bFeUnit         = tree->GetBranch("FeUnit");
            TBranch* bFeChan         = tree->GetBranch("FeChan");
            TBranch* bFeApv          = tree->GetBranch("FeApv");
            
            double devId          = 0.0;
            double detId          = 0.0;
            double FecCrate       = 0.0;
            double Fec            = 0.0;
            double Ring           = 0.0;
            double Ccu            = 0.0;
            double CcuArrangement = 0.0;
            double I2CChannel     = 0.0;
            double I2CAddress     = 0.0;
            double lasChan        = 0.0;
            double FedId          = 0.0;
            double FeUnit         = 0.0;
            double FeChan         = 0.0;
            double FeApv          = 0.0;
            
            bdevId         ->SetAddress(&devId);
            bdetId         ->SetAddress(&detId);
            bFecCrate      ->SetAddress(&FecCrate);
            bFec           ->SetAddress(&Fec);
            bRing          ->SetAddress(&Ring);
            bCcu           ->SetAddress(&Ccu);
            bCcuArrangement->SetAddress(&CcuArrangement);
            bI2CChannel    ->SetAddress(&I2CChannel);
            bI2CAddress    ->SetAddress(&I2CAddress);
            blasChan       ->SetAddress(&lasChan);
            bFedId         ->SetAddress(&FedId);
            bFeUnit        ->SetAddress(&FeUnit);
            bFeChan        ->SetAddress(&FeChan);
            bFeApv         ->SetAddress(&FeApv);


            infoss << "<b>Skipped channels : </b>" << "<br/>";

            QMap<unsigned, int> selChannels;

            for(int i = 0; i < tree->GetEntries(); i++) {
                bdevId         ->GetEvent(i);
                bdetId         ->GetEvent(i);
                bFecCrate      ->GetEvent(i);
                bFec           ->GetEvent(i);
                bRing          ->GetEvent(i);
                bCcu           ->GetEvent(i);
                bCcuArrangement->GetEvent(i);
                bI2CChannel    ->GetEvent(i);
                bI2CAddress    ->GetEvent(i);
                blasChan       ->GetEvent(i);
                bFedId         ->GetEvent(i);
                bFeUnit        ->GetEvent(i);
                bFeChan        ->GetEvent(i);
                bFeApv         ->GetEvent(i);
            
                if (selMap[i] == 0) continue;

                SiStripFedKey fedkey(
                    QString::number(FedId ).toInt(),
                    QString::number(FeUnit).toInt(),
                    QString::number(FeChan).toInt(),
                    QString::number(FeApv ).toInt()
                );

                selChannels[fedkey.key()] = 1;

            }

            QMap<unsigned, int>::const_iterator map_iter = selChannels.constBegin();
            while (map_iter != selChannels.constEnd()) {
                SiStripFedKey fedkey(map_iter.key());

                infoss << "\tcms.PSet(" << std::endl << "<br/>";
                infoss << "\t\t fedId = cms.untracked.uint32("  << fedkey.fedId()  << ")," << std::endl << "<br/>";
                infoss << "\t\t feUnit = cms.untracked.uint32(" << fedkey.feUnit() << ")," << std::endl << "<br/>";
                infoss << "\t\t feChan = cms.untracked.uint32(" << fedkey.feChan() << ")," << std::endl << "<br/>";
                infoss << "\t\t fedApv = cms.untracked.uint32(" << fedkey.fedApv() << ")"  << std::endl << "<br/>";
                infoss << "\t)," << std::endl << "<br/>";

                skipss << "\tcms.PSet(" << std::endl;
                skipss << "\t\t fedId = cms.untracked.uint32("  << fedkey.fedId()  << ")," << std::endl;
                skipss << "\t\t feUnit = cms.untracked.uint32(" << fedkey.feUnit() << ")," << std::endl;
                skipss << "\t\t feChan = cms.untracked.uint32(" << fedkey.feChan() << ")," << std::endl;
                skipss << "\t\t fedApv = cms.untracked.uint32(" << fedkey.fedApv() << ")"  << std::endl;
                skipss << "\t)," << std::endl;

                ++map_iter;
            }

        }
        
        QString nextRun;
        QString iovQueryStr("select max(runnumbertbl.runnumber+1) runnumber from CMS_RUNINFO.runnumbertbl");
        QSqlQuery iovQuery(iovQueryStr);
        
        while (iovQuery.next()) {
            nextRun = iovQuery.value(0).toString();
        }
        
        infoss << "<b>Next global run : </b>" << qPrintable(nextRun) << "<br/><br/>";

        std::ofstream partFile;
        std::ofstream skipFile;

        QString partFilename = "/nfshome0/trackerpro/o2o/scripts/TimingO2O_Partitions.py";
        QString skipFilename = "/nfshome0/trackerpro/o2o/scripts/TimingO2O_SkippedChannels.py";

        partFile.open(partFilename.toStdString().c_str());
        skipFile.open(skipFilename.toStdString().c_str());

        partFile << partss.str().c_str();
        skipFile << skipss.str().c_str();

        partFile.close();
        skipFile.close();

        QStringList commandArgs;
        //commandArgs << "/nfshome0/trackerpro/o2o/scripts/testGainO2O.sh" << nextRun << partFilename << skipFilename;
        commandArgs << "/nfshome0/trackerpro/o2o/scripts/simpletest.sh" << nextRun << partFilename << skipFilename;

        bool o2oresult = false;
        QProcess* proc = new QProcess(this);
        TkTerminalDialog* timingO2OTerm = new TkTerminalDialog(this);
        timingO2OTerm->setProcessPtr(proc);
        
        connect( proc, SIGNAL(readyReadStandardOutput())          , timingO2OTerm, SLOT(readFromStdout())  );
        connect( proc, SIGNAL(finished(int, QProcess::ExitStatus)), timingO2OTerm, SLOT(processFinished(int, QProcess::ExitStatus)) );
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), timingO2OTerm, SLOT(executeWaitForReadyRead()));
        timer->start(100);
        
        proc->start(commandArgs.join(" "));
        if (!proc->waitForStarted()) {
            infoss << "Could not start analysis" << qPrintable(nextRun) << "<br/>";
            delete timingO2OTerm;
            o2oresult = false;
        } 
        else {
            if (timingO2OTerm->exec()==QDialog::Accepted) o2oresult = true;
            else o2oresult = false;
        }

        if (o2oresult) infoss << "<b>O2O process completed successfully</b>" << "<br/>";
        else           infoss << "<b>O2O process failed</b>"                 << "<br/>";

        infoss << "</html>" << std::endl;
        QTextCursor cursor(txtCurRunInfo->textCursor());
        cursor.insertHtml(infoss.str().c_str());

        return true;

    }

    else { 
        QString partition, modeDescription, creationDate, startTime, endTime, o2o;
        QString fecMajor, fecMinor, fedMajor, fedMinor, connMajor, connMinor, dcuinfoMajor, dcuinfoMinor, dcumapMajor, dcumapMinor, maskMajor, maskMinor, analysisid;
        QString cpsetpoint;
        
        QString tablename = "viewallrun";
        
        std::stringstream queryss;
        queryss << "select distinct ";
        queryss << "partitionname, ";
        queryss << "modedescription, ";
        queryss << "to_char( starttime,'yyyy-mm-dd' ) as creationdate, ";
        queryss << "to_char( starttime, 'hh24:mi:ss' ) as creationtime, ";
        queryss << "to_char( endtime, 'hh24:mi:ss' ) as finishtime, ";
        queryss << "fecversionmajorid, ";
        queryss << "fecversionminorid, ";
        queryss << "fedversionmajorid, ";
        queryss << "fedversionminorid, ";
        queryss << "connectionversionmajorid, ";
        queryss << "connectionversionminorid, ";
        queryss << "dcuinfoversionmajorid, ";
        queryss << "dcuinfoversionminorid, ";
        queryss << "dcupsumapversionmajorid, ";
        queryss << "dcupsumapversionminorid, ";
        queryss << "maskversionmajorid, ";
        queryss << "maskversionminorid, ";
        queryss << "analysisversionid ";
        queryss << "from ";
        queryss <<  tablename.toStdString();
        queryss << " where runnumber=" << qPrintable(currentRun);
        
        QString myQuery(queryss.str().c_str());
        QSqlQuery query(myQuery);
        
        while (query.next()) {
            partition       = query.value(0).toString();
            modeDescription = query.value(1).toString();
            creationDate    = query.value(2).toString();
            startTime       = query.value(3).toString();
            endTime         = query.value(4).toString();
            fecMajor        = query.value(5).toString();
            fecMinor        = query.value(6).toString();
            fedMajor        = query.value(7).toString();
            fedMinor        = query.value(8).toString();
            connMajor       = query.value(9).toString();
            connMinor       = query.value(10).toString();
            dcuinfoMajor    = query.value(11).toString();
            dcuinfoMinor    = query.value(12).toString();
            dcumapMajor     = query.value(13).toString();
            dcumapMinor     = query.value(14).toString();
            maskMajor       = query.value(15).toString();
            maskMinor       = query.value(16).toString();
            analysisid      = query.value(17).toString();
        }
        
        std::stringstream infoss;
        infoss << "<html>" << std::endl;
        infoss << "<p>" << std::endl;
        infoss << "<b>About the run:</b>" << "<br/>";
        infoss << "Run Number : "         << qPrintable(currentRun)      << " (" << qPrintable(modeDescription) << ") <br/>";
        infoss << "Partition          : " << qPrintable(partition)       << "<br/>";
        infoss << "Created On    : "      << qPrintable(creationDate)    << " during " << qPrintable(startTime) << " to " << qPrintable(endTime) << "<br/>";
        infoss << std::endl;
        infoss << "</p>" << std::endl;
        
        infoss << "<b>DB Versions:" << "</b>" << "<br/>";
        
        QTextCursor cursor(txtCurRunInfo->textCursor());
        cursor.insertHtml(infoss.str().c_str());
        
        cursor.insertTable(6,2);
        cursor.insertText("FEC");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(fecMajor+"."+fecMinor);
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText("FED");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(fedMajor+"."+fedMinor);
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText("CONN");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(connMajor+"."+connMinor);
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText("DCU  INFO");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(dcuinfoMajor+"."+dcuinfoMinor);
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText("DCU-PSU MAP");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(dcumapMajor+"."+dcumapMinor);
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText("MASK");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(maskMajor+"."+maskMinor);
        cursor.movePosition(QTextCursor::NextCell);
        
        std::stringstream info2ss;
        info2ss << "</html>" << std::endl;
        cursor.movePosition(QTextCursor::End);
        cursor.insertHtml(info2ss.str().c_str());

        return true;
    }
}

