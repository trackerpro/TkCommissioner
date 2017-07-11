#ifndef FRMPREPAREGLOBAL_H
#define FRMPREPAREGLOBAL_H
 
// Qt containers
#include <QVector>
#include <QMap>
#include <QMultiMap>
#include <QMainWindow>

// To set up the run selection tables in the startup window
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>

// Other UIs needed here
#include "frmpartitions.h"

// UI file
#include "ui_frmprepareglobal.h"

/** \Class PrepareGlobal
 *
 * \brief Lauch the interface to perform O2O
 * 
 */ 
class PrepareGlobal : public QMainWindow, private Ui::PrepareGlobal {

    Q_OBJECT

    public:
        /**
         * default constructor
         */
        PrepareGlobal(QWidget *parent = 0);

        /**
         * destructor
         */
        ~PrepareGlobal();

    private:

        std::map<int, int> iOldConfiguration;
        std::map<int, int> readoutModes;

        void addReadRoutes();
        
        void addReadRouteTo(QComboBox* readRouteList);

        void addModesAndSuperModes();

        void addModeAndSuperModeTo(QComboBox* modeList);

        void partitionForConfiguration(QLabel* label, int partitionLabel);

        void setPartitions();

        void addChoosePartitionName(QComboBox * myPartList);

        void displayStatus(int newStatus);

        void displayStatus(int newStatus, const int& nextRunNumber, const int& lastIovRunNumber, bool allowO2O );

        void readoutChanged();

        void checkReadoutConfiguration();

        void activatePartition(QComboBox* subDet, QComboBox* readRoute, QComboBox* modeSuperMode);

        int validCombination(QComboBox* comboReadRoute, QComboBox* comboMSM);

        void populatePartition(QStringList partitionNames, QComboBox* cmbPart, bool usedPart);

        void populatePartitions();

        QStringList getUsedPartitionNames(QString subDetector, bool& used);

        int getCurrentConfiguration();

        int getCurrentConfigurationFor(QLabel *label, QComboBox* comboReadRoute, QComboBox* comboMSM );

        bool updateMSM(QComboBox* combo, QString fedmode, QString supermode);

        int xCheckPartition( QString partitionName , QString subDetector);

        int checkVersions();

        int checkVersions(bool checkO2O);

        int getRunNumbers(int &nextRunNumber, int &lastIovRunNumber);

        void cacheOldConfiguration();

        void setAllToModeSuperMode(int modeSuperMode);

        void setAllToReadout(int readoutMode);

        bool preparePartitionState(QString partitionName, QString subDetector, int nextRunNumber);

        bool confirmO2O(int nextRunNumber);

        QString createCfgLines(QString, QString, int, int, int, int, int, int, int, int, int, int, int, int);

        int getVersions(QString, int, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);

        QString createCfgLines(QString subDetectorShort, QString partitionName, int runNumber, bool& isValid, bool &isFirst);

        bool launchTerminal(QStringList & commandList, bool modal);

        QString getColor(const QString &string1, const QString &string2);

        int showCurrentState();

        QString getReadRoute(int);

        void submitChanges();

        bool setNewReadRoute(QComboBox* cmbBox, QString partition);

        bool setNewModeSuperMode(QComboBox* cmbBox, QString partition);

        bool refreshDBCache(const QString &partition);

        void revertConfiguration();

    public Q_SLOTS:

        void on_btnTibMore_clicked();

        void on_btnTobMore_clicked();
        
        void on_btnTecpMore_clicked();
        
        void on_btnTecmMore_clicked();

        void on_btnAllToGlobal_clicked();

        void on_btnAllToLocal_clicked();

        void on_btnSetConf_clicked();

        void on_btnApplyChanges_clicked();

        void on_cmbTib_activated(int);

        void on_cmbTob_activated(int);

        void on_cmbTecp_activated(int);

        void on_cmbTecm_activated(int);

        void on_comboBoxReadRouteTib_activated(int) ;

        void on_comboBoxReadRouteTob_activated(int) ;

        void on_comboBoxReadRouteTecp_activated(int);

        void on_comboBoxReadRouteTecm_activated(int);

        void on_comboBoxMSMTib_activated(int);

        void on_comboBoxMSMTob_activated(int);

        void on_comboBoxMSMTecp_activated(int);

        void on_comboBoxMSMTecm_activated(int);

        void on_btnRevertConfiguration_clicked();

        void on_btnQuit_clicked();
};
 
#endif
