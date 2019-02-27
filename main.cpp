// All the Qt classes need to setup the TkCommissioner GUI
#include <QApplication>
#include <QPlastiqueStyle>
#include <QPixmap>
#include <QSplashScreen>

// Class for debug flagging and console output
#include "Debug.h"
// Class that handles DB connection
#include "DbConnection.h"
// TkCommissioiner UI
#include "frmcommissioner.h"

#include <unistd.h>
#include <iostream>

int main(int argc, char ** argv) {

    // Boolean to decide whether or not to show the splash screen    
    bool showSplash = true;

    // Parsing of arguments 
    for (int i = 1; i < argc; i++) {
        QString qarg(argv[i]);
        if (qarg == "-h") {
            qDebug()  << "\n\n"
                      << "Valid command line arguments are:\n"
                      << "\n"
                      << "  -h  : display this message and exit\n"
                      << "  -d  : debug\n"
                      << "  -l  : suppress splash screen\n\n";
            return 0;
        }
        else if (qarg == "-d") Debug::Inst()->setEnabled(true);
        else if (qarg == "-l") showSplash = false;
        else {
            qDebug()  << "\n\n"
                      << "Invalid command line argument(s). You can only use the following:\n"
                      << "\n"
                      << "  -h  : display this message and exit\n"
                      << "  -d  : debug\n"
                      << "  -l  : suppress splash screen\n\n";
            return 0;
        }
    }

    // Set up the Qt application
    QApplication::setStyle(new QPlastiqueStyle);
    QApplication app(argc, argv);

    // Set up the connection to the Oracle DB
    char* confDb;
    confDb = getenv ("CONFDB");
    DbConnection::Inst()->connectDb(std::string(confDb));

    // Splash screen at start up
    QPixmap pixmap("/opt/cmssw/shifter/avartak/qtRoot/NewCommissioningGui/Stable/TkCommissioner/images/slide_TIB_lights2.png"); 
    QSplashScreen *splash = new QSplashScreen( pixmap );

    // Print the text logo
    Debug::Inst()->printLogo();

    // Show splash screen
    if(showSplash) {
        sleep(1);
        splash->show();
        splash->showMessage("Established connections", Qt::AlignHCenter, Qt::white);
        sleep(1);
	}

    // Start the TkCommissioner
    Commissioner* tkcom = new Commissioner;
    tkcom->show();
    splash->finish(tkcom);
    app.connect(tkcom, SIGNAL(destroyed()), &app, SLOT(quit()) );
    
    return app.exec();
}
