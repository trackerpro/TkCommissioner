include("$(ROOTSYS)/include/rootcint.pri")

OBJECTS_DIR = .obj
MOC_DIR     = .moc
UI_DIR      = .ui

HEADERS +=  Debug.h \
            DbConnection.h \
            QConnectedTabWidget.h \
            CustomTQtWidget.h \
            BaseTypes.h \
            TreeBuilder.h \
            TreeViewerRunInfo.h \ 
            FedView.h \
            FedGraphicsView.h \            
            FedGraphicsScene.h \ 
            TkMapGlobals.h \
            Chip.h \
            TkView.h \
            frmcommissioner.h \
            frmstartup.h \
            frmtreeviewer.h \
            frmreferencechooser.h \
            frmdbupload.h \
            frmaddskip.h \
            frmdetails.h \
            frmdbtag.h \
            frmsavetags.h \
            frmtrends.h \
            frmsource.h \
            frmtkmap.h \
            frmfedmap.h \
            frmterminal.h \
            frmmultipart.h \
            frmprepareglobal.h \
            frmpartitions.h \
            frmterminaldialog.h \
            cmssw/SiStripFecKey.h \
            cmssw/SiStripFedKey.h

SOURCES +=  main.cpp \
            Debug.cpp \
            DbConnection.cpp \
            TreeBuilder.cpp \
            TreeViewerRunInfo.cpp \ 
            FedView.cpp \
            FedGraphicsView.cpp \            
            FedGraphicsScene.cpp \            
            Chip.cpp \
            TkView.cpp \
            frmstartup.cpp \
            frmtreeviewer.cpp \
            frmdbupload.cpp \
            frmaddskip.cpp \
            frmdetails.cpp \
            frmsource.cpp \
            frmtkmap.cpp \
            frmfedmap.cpp \
            frmmultipart.cpp \
            frmprepareglobal.cpp \
            frmpartitions.cpp \
            cmssw/SiStripKey.cc \
            cmssw/SiStripFecKey.cc \
            cmssw/SiStripFedKey.cc \

FORMS +=    uifiles/frmcommissioner.ui \
            uifiles/frmstartup.ui \
            uifiles/frmtreeviewer.ui \
            uifiles/frmreferencechooser.ui \
            uifiles/frmdbupload.ui \
            uifiles/frmaddskip.ui \
            uifiles/frmfedmap.ui \
            uifiles/frmdetails.ui \
            uifiles/frmdbtag.ui \
            uifiles/frmsavetags.ui \
            uifiles/frmsource.ui \
            uifiles/frmtrends.ui \
            uifiles/frmterminal.ui \
            uifiles/frmprepareglobal.ui \
            uifiles/frmpartitions.ui \
            uifiles/frmterminaldialog.ui \
            uifiles/frmmultipart.ui
