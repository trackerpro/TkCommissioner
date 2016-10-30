#include "frmruninfo.h"
#include <sstream>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QTextCursor>
#include <QTextTable>

RunInfo::RunInfo(QWidget* parent):
    QConnectedTabWidget(parent),
    currentRun()
{
    setupUi(this);
}

RunInfo::~RunInfo() {
}

void RunInfo::setCurrentRun(QString r) {
    currentRun = r;
}

QString RunInfo::getCurrentRun() {
    return currentRun;
}

void RunInfo::displayRunInfo() {
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

}

