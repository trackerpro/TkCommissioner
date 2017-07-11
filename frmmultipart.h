#ifndef FRMMULTIPART_H
#define FRMMULTIPART_H
 
// Qt containers
#include <QVector>
#include <QMap>
#include <QMultiMap>

// To set up the run selection tables in the startup window
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>

// Parent widget for the TkCommissioner tabs 
#include "QConnectedTabWidget.h"

// UI file
#include "ui_frmmultipart.h"

/** \Class MultiPart
 *
 * \brief Class to open runs of a given type in the tree viewer in a combined way for all the partitions
 * This class is also the starting point for the Timing O2O
 *
 * This class presents the user with an interface that allows the user to 
 * - Select the run type (should be TIMING for Timing O2O)
 * - Select the runs of that run type for each of the four partitions
 * - Launch the treeviewer for these runs
 * 
 */ 
class MultiPart : public QConnectedTabWidget, private Ui::MultiPart {

    Q_OBJECT

    private: 
        /**
        * Fill in the run types - TIMING, PEDESTAL, GAINSCAN, VPSPSCAN
        */ 
        void prepareRunTypes();
 
        /**
        * Fill in the partition names - basically call the next function for each of the four partitions
        */ 
        void preparePartitions();
 
        /**
        * Prepare the list of partition names for a given partition
        */ 
        void preparePartitionList(const QString&, QComboBox*);
 
        /**
        * Fill in the run numbers - basically call the next function for each of the four partitions
        */ 
        void prepareRuns();
 
        /**
        * Fill in the Db information for given set of runs
        */ 
        void prepareDbTable(const QString&, const QString&);
 
        /**
        * Prepare the list of run numbers for a given partition
        */ 
        void prepareRunList(const QString&, const QString&, QComboBox*);

        QVector<QString>* tfiles;
 
    public:
        /**
         * default constructor
         */
        MultiPart(QVector<QString>* tf, QWidget *parent = 0);

        /**
         * destructor
         */
        ~MultiPart();

    public Q_SLOTS:
        /**
         * Update the list of partitions and runs
         */
        void on_btnUpdate_clicked();
        
        /**
         * Open the tree viewer for the selected runs
         */
        void on_btnShow_clicked();
        
        /**
         * When the run type is changed in the run-type combo box, 
         * the runs for the new type need to be loaded into the run lists for each partition
         */
        void on_cmbRunType_currentIndexChanged(const QString&);
        
        /**
         * When the TIB  run number is changed 
         * update the entries in the DB table
         */
        void on_cmbRunTib_currentIndexChanged(const QString&);
        
        /**
         * When the TOB  run number is changed 
         * update the entries in the DB table
         */
        void on_cmbRunTob_currentIndexChanged(const QString&);
        
        /**
         * When the TECP  run number is changed 
         * update the entries in the DB table
         */
        void on_cmbRunTecp_currentIndexChanged(const QString&);
        
        /**
         * When the TECM  run number is changed 
         * update the entries in the DB table
         */
        void on_cmbRunTecm_currentIndexChanged(const QString&);
        
        
};
 
#endif
