#ifndef FRMSTARTUP_H
#define FRMSTARTUP_H
 
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
#include "ui_frmstartup.h"

/** \Class Startup
 *
 * \brief Class to retrieve a list of partitions and runs and enable
 * various actions to perform on them
 *
 * This class presents the user with an interface to perform various
 * actions on a run. The user can
 * 
 * - run the standard commissioning analysis on a run
 * - display results from a given run
 * - upload analysis results to the configuration database
 * 
 */ 
class Startup : public QConnectedTabWidget, private Ui::Startup {

    Q_OBJECT
 
    private:
        QStandardItemModel *partitionModel;
        QStandardItemModel *runModel;
        QString currentPartitionName;
        QVector<QString> tmpfiles;

        /**
         * generic base method to add an item with a description to a
         * QStandardItemModel. Used by addPartition and addRun
         */ 
        void addItem(QStandardItemModel *model, const QString &first, const QString& second, bool isRunItem = false, bool analyzed = false, bool itemBad = false);
        
        /**
         * function which takes a partition name as argument and populates
         * the runView with all commissioning runs from this partition.
         */ 
        void populateRuns(const QString &partitionName);
        
        /**
         * function to populate the partitionView. This function will be
         * called when the interface is brought up.
         */ 
        void populatePartitions();
        
        /**
         * delete files (trees, etc.) created for the commissioning analysis
         */
        void deleteTmpFiles();
 
    public:
        /**
         * default constructor
         */
        Startup(QWidget *parent = 0);

        /**
         * destructor
         */
        ~Startup();

    public Q_SLOTS:
        /**
         * Function to be executed when quit button is pressed.  Currently
         * only closes the interface, can also be used for clean up if
         * needed
         */
        void on_btnQuit_clicked();
        
        /**
         * Function to be executed when "View Results" button is pressed.
         * Currently only passes run and partition to #TreeBuilder and
         * #TreeViewer to display results. 
         */
        void on_btnViewResults_clicked();
        
        /**
         * Updates the list of partitions in partitionView
         */
        void on_btnUpdatePartitions_clicked();
        
        /**
         * Updates the list of runs in runView
         */
        void on_btnUpdateRuns_clicked();
        
        /**
         * Updates comment field in the DB of the selected run to indicate them as bad
         */ 
        void on_btnMarkBad_clicked();
        
        /**
         * show a state as selected in the QComboBox
         */ 
        void on_btnState_clicked();
        
        /**
         * Analyze the selected run
         */ 
        void on_btnAnalyze_clicked();
        
        /**
         * Prepare for global running
         */ 
        void on_btnPrepareGlobal_clicked();

        /**
         * Perform timing O2O
         */ 
        void on_btnTimingO2O_clicked();

        /**
         * slot that will be called if the active run number in the runView
         * TableView. Checks whether this run has already been analyzed and
         * if so, will enable button to view results.
         */
        void runChanged(QModelIndex current, QModelIndex previous);
        
        /**
         * slot that will be called if the active partition in the
         * partitionView TableView. Will in turn call the
         * Startup::populateRuns(const QString &partitionName) slot to
         * update run numbers in the runView.
         */
        void partitionChanged(QModelIndex current, QModelIndex previous);
        
};
 
#endif
