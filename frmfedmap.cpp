#include "frmfedmap.h"
#include "frmterminal.h"
#include "Debug.h"

#include <QtSql/QSqlQuery>
#include <QMap>

#include <TBranch.h>

FedMap::FedMap(QWidget* parent):
    QConnectedTabWidget(parent),
    performUpload(false)        
{
    setupUi(this);

    scene = new FedGraphicsScene(parent);
    graphicsView->setScene(scene);    
    graphicsView->scale(0.25, 0.25);
    matrix = graphicsView->matrix();

    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(graphicsView, SIGNAL(sendWheelSignal(QWheelEvent*)), this, SLOT(catchWheelSignal(QWheelEvent*)));
    connect(scene, SIGNAL(sendZoomSignal(const QPointF&)), this, SLOT(catchZoomSignal(const QPointF&)));
}

FedMap::FedMap(const QVector<int>& smap, QPair<QString, QString> runid, TTree* tree, QWidget *parent): 
    QConnectedTabWidget(parent)
{
    setupUi(this);

    scene = new FedGraphicsScene(parent);
    graphicsView->setScene(scene);    
    graphicsView->scale(0.25, 0.25);
    matrix = graphicsView->matrix();

    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(graphicsView, SIGNAL(sendWheelSignal(QWheelEvent*)), this, SLOT(catchWheelSignal(QWheelEvent*)));
    connect(scene, SIGNAL(sendZoomSignal(const QPointF&)), this, SLOT(catchZoomSignal(const QPointF&)));

    part = runid.first;
    run  = runid.second;
    mode = "";

    if (part == "" || run == "" || run.toInt() == 137 || run.toInt() == 138 || run.toInt() == 139) btnUpload->setEnabled(false);
    else {
        btnUpload->setEnabled(true);
        btnUpload->setText(QString("Selective upload : ")+runid.second);

        mode = "";
        QString squery = QString("select distinct runnumber, modedescription from viewallrun left outer join analysis using(runnumber) where partitionname='%1' and local = 1").arg(part);
        QSqlQuery query(squery);
        while (query.next()) {
            QString runNumber       = query.value(0).toString();
            QString modeDescription = query.value(1).toString();
        
            if (runNumber == run) mode = modeDescription;
        } 

        if (mode != "PEDESTAL" && mode != "TIMING" && mode != "GAINSCAN" && mode != "VPSPSCAN" && mode != "CALIBRATION_SCAN") btnUpload->setEnabled(false); 

    }

    if (tree && tree->GetEntries() == smap.size()) {
        QMap<unsigned, QVector<QVector<bool> > > markedFeds;
        
        for (int i = 0; i < 10; i++) {
            fedview::Rack rack;
            QString racknamess = "";
            if (i != 0) racknamess += QString("VME-S1B0") + QString::number( 10-i);
            else        racknamess += QString("VME-S1B" ) + QString::number( 10  );
            rack.name = racknamess;
            racks.push_back(rack);
        }
        for (int i = 10; i < 20; i++) {
            fedview::Rack rack;
            QString racknamess;
            if (i != 10) racknamess += QString("VME-S1C0") + QString::number( 20-i);
            else         racknamess += QString("VME-S1C" ) + QString::number( 10  );
            rack.name = racknamess;
            racks.push_back(rack);
        }

        TBranch* bFedId   = tree->GetBranch("FedId");
        TBranch* bFedUnit = tree->GetBranch("FeUnit");
        TBranch* bFedChan = tree->GetBranch("FeChan");
        if (!bFedId || !bFedUnit || !bFedChan) {
            if (Debug::Inst()->getEnabled()) qDebug() << "Unable to read FED-related branches from the tree";
            return;
        }
        double FedId    = 0.0;
        double FedUnit  = 0.0;
        double FedChan  = 0.0;
        bFedId  ->SetAddress(&FedId);
        bFedUnit->SetAddress(&FedUnit);
        bFedChan->SetAddress(&FedChan);
        
        for(int i = 0; i < tree->GetEntries(); i++) {
            if (smap[i] == 1) {
                bFedId  ->GetEvent(i);
                bFedUnit->GetEvent(i);
                bFedChan->GetEvent(i);
                bool seenBefore = false;
                unsigned fid = unsigned(FedId);
                unsigned fun = unsigned(FedUnit);
                unsigned fch = unsigned(FedChan);
                for (QMap<unsigned, QVector<QVector<bool> > >::const_iterator iter = markedFeds.begin(); iter != markedFeds.end(); ++iter) {
                    if (iter.key() == fid) seenBefore = true;
                }
                if (!seenBefore) {
                    QVector<QVector<bool> > feinfo;
                    for (int j = 0; j < 8; j++) {
                        QVector<bool> fechaninfo;
                        for (int k = 0; k < 12; k++) fechaninfo.push_back(false);
                        feinfo.push_back(fechaninfo);
                    }
                    markedFeds[fid] = feinfo;
                }
                markedFeds[fid][fun-1][fch-1] = true;
            }
        }
        bFedId  ->ResetAddress();
        bFedUnit->ResetAddress();
        bFedChan->ResetAddress();
        
        QString squery = "";
        squery += "select distinct HOSTNAME, IDVSHOSTNAME.ID, CRATESLOT, CRATEID, CRATENUMBER, FED.CRATE ";
        squery +=  "from IDVSHOSTNAME join fed on to_char(FED.ID)=IDVSHOSTNAME.ID and fed.partitionid in (select partitionid from viewcurrentstate)";
        
        QSqlQuery query(squery);

        while(query.next()) {
            QString crateid = query.value(3).toString();
            QString rackname = crateid;
            rackname = rackname.remove("-d");
            rackname = rackname.remove("-h");
            rackname = rackname.remove("-l");
       
            QVector<QVector<bool> > feinfo;
            for (QMap<unsigned, QVector<QVector<bool> > >::const_iterator iter = markedFeds.begin(); iter != markedFeds.end(); ++iter) {
                if (unsigned(query.value(1).toInt()) == iter.key()) feinfo = iter.value();
            }
        
            bool rackadded = false;
            for (int i = 0; i < racks.size(); i++) {
                if (rackname == racks[i].name) {
                    rackadded = true;
                    if      (crateid.contains("-d")) racks[i].d.addFed(query.value(2).toInt(), query.value(1).toInt(), feinfo);
                    else if (crateid.contains("-h")) racks[i].h.addFed(query.value(2).toInt(), query.value(1).toInt(), feinfo);
                    else if (crateid.contains("-l")) racks[i].l.addFed(query.value(2).toInt(), query.value(1).toInt(), feinfo);
                    racks[i].isEmpty = false;
                }
            }
            if (!rackadded) {
                if (Debug::Inst()->getEnabled()) qDebug() << "Error in rack initialization for crate id " << crateid;
            }
        }
        
        int place = 0;
        for (int i = 0; i < 10; i++) {
            if (!racks[i].isEmpty) {
                racks[i].setCoordinates(place, true);
                place++;
            }
        }
        place = 10;
        for (int i = 0; i < 10; i++) {
            if (!racks[i+10].isEmpty) {
                racks[i+10].setCoordinates(place-10, false);
                place++;
            }
        }
    }
    else {
        if (Debug::Inst()->getEnabled()) qDebug() << "Unable to construct FED map from given tree and selection";
    }

    for (int i = 0; i < racks.size() ; i++) {
        if (!racks[i].isEmpty) racks[i].createScene(scene);
    }
}

FedMap::~FedMap() {
}

void FedMap::setupMatrix() {
    qreal scale = qPow(qreal(1.15), zoomSlider->value()/qreal(2.));

    QMatrix m = matrix;
    m.scale(scale, scale);

    graphicsView->setMatrix(m);
    setViewInfoVisibility(zoomSlider);
}

void FedMap::setViewInfoVisibility(QSlider* slider) {
    for (int i = 0; i < racks.size(); i++) {
        if (racks[i].isEmpty) continue;
        for (int j = 0; !racks[i].h.isEmpty && j < racks[i].h.feds.size(); j++) {
            if (racks[i].h.feds[j].id != 0 && racks[i].h.feds[j].fedtext) {
                racks[i].h.feds[j].fedtext ->setVisible(slider->value() > 20);
                racks[i].h.feds[j].slottext->setVisible(slider->value() > 20);
                for (int k = 0; k < 8; k++) {
                    racks[i].h.feds[j].units[k].feunittext->setVisible(slider->value() > 20);
                    for (int l = 0; l < 12; l++) racks[i].h.feds[j].units[k].channels[l].fechannelframe->setVisible(slider->value() > 15);
                } 
            }
        }
        for (int j = 0; !racks[i].l.isEmpty && j < racks[i].l.feds.size(); j++) {
            if (racks[i].l.feds[j].id != 0 && racks[i].l.feds[j].fedtext) {
                racks[i].l.feds[j].fedtext ->setVisible(slider->value() > 20); 
                racks[i].l.feds[j].slottext->setVisible(slider->value() > 20);
                for (int k = 0; k < 8; k++) {
                    racks[i].l.feds[j].units[k].feunittext->setVisible(slider->value() > 20);
                    for (int l = 0; l < 12; l++) racks[i].l.feds[j].units[k].channels[l].fechannelframe->setVisible(slider->value() > 15);
                } 
            }
        }
        for (int j = 0; !racks[i].d.isEmpty && j < racks[i].d.feds.size(); j++) {
            if (racks[i].d.feds[j].id != 0 && racks[i].d.feds[j].fedtext) {
                racks[i].d.feds[j].fedtext ->setVisible(slider->value() > 20); 
                racks[i].d.feds[j].slottext->setVisible(slider->value() > 20);
                for (int k = 0; k < 8; k++) {
                    racks[i].d.feds[j].units[k].feunittext->setVisible(slider->value() > 20);
                    for (int l = 0; l < 12; l++) racks[i].d.feds[j].units[k].channels[l].fechannelframe->setVisible(slider->value() > 15);
                } 
            }
        }
    }
}

void FedMap::on_btnZoomIn_clicked() {
    zoomSlider->triggerAction(QAbstractSlider::SliderSingleStepAdd);
}

void FedMap::on_btnZoomOut_clicked() {
    zoomSlider->triggerAction(QAbstractSlider::SliderSingleStepSub);
}

void FedMap::on_btnUpload_clicked() {
    QFile file("/exports/slc7/scripts/analysis_template_CC7_cfg.py");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    
    QByteArray total;
    QByteArray line;
    while (!file.atEnd()) {
        line = file.readAll();
        total.append(line);
    }

    QList<QGraphicsItem*> feds = scene->selectedItems();
    QString sveto = (chkVeto->isChecked() ? "True" : "False");

    if (chkEnable->isChecked() && feds.size() > 0) {
        if (mode.contains("PEDESTAL")) {
	  total.append("process.db_client.PedestalsParameters.doSelectiveUpload = cms.bool(True)\n");
	  total.append("process.db_client.PedestalsParameters.vetoModules = cms.bool(");
	  total.append(sveto);
	  total.append(")\n");
	  total.append("process.db_client.PedestalsParameters.fedMaskVector = cms.vuint32(");
	  for (int i = 0; i < feds.size(); i++) {
	    total.append(feds[i]->data(0).toString());
	    if (i < feds.size()-1) total.append(",");
            }
	  total.append(")\n");
        }
        else if (mode.contains("TIMING")) {
	  total.append("process.db_client.ApvTimingParameters.doSelectiveUpload = cms.bool(True)\n");
	  total.append("process.db_client.ApvTimingParameters.vetoModules = cms.bool(");
	  total.append(sveto);
	  total.append(")\n");
	  total.append("process.db_client.ApvTimingParameters.fedMaskVector = cms.vuint32(");
	  for (int i = 0; i < feds.size(); i++) {
	    total.append(feds[i]->data(0).toString());
	    if (i < feds.size()-1) total.append(",");
	  }
	  total.append(")\n");
        }
        else if (mode.contains("GAINSCAN")) {
	  total.append("process.db_client.OptoScanParameters.doSelectiveUpload = cms.bool(True)\n");
	  total.append("process.db_client.OptoScanParameters.vetoModules = cms.bool(");
	  total.append(sveto);
	  total.append(")\n");
	  total.append("process.db_client.OptoScanParameters.fedMaskVector = cms.vuint32(");
	  for (int i = 0; i < feds.size(); i++) {
	    total.append(feds[i]->data(0).toString());
	    if (i < feds.size()-1) total.append(",");
	  }
	  total.append(")\n");
        }
        else if (mode.contains("CALIBRATION_SCAN") or mode.contains("CALIBRATION_DECO") or mode.contains("CALIBRATION_SCAN_DECO")) {
	  total.append("process.db_client.CalibrationParameters.doSelectiveUpload = cms.bool(True)\n");
	  total.append("process.db_client.CalibrationParameters.vetoModules = cms.bool(");
	  total.append(sveto);
	  total.append(")\n");
	  total.append("process.db_client.CalibrationParameters.fedMaskVector = cms.vuint32(");
	  for (int i = 0; i < feds.size(); i++) {
	    total.append(feds[i]->data(0).toString());
	    if (i < feds.size()-1) total.append(",");
	  }
	  total.append(")\n");
        }
        else if (mode.contains("VPSPSCAN")) {
	  total.append("process.db_client.VpspScanParameters.doSelectiveUpload = cms.bool(True)\n");
	  total.append("process.db_client.VpspScanParameters.vetoModules = cms.bool(");
	  total.append(sveto);
	  total.append(")\n");
	  total.append("process.db_client.VpspScanParameters.fedMaskVector = cms.vuint32(");
	  for (int i = 0; i < feds.size(); i++) {
	    total.append(feds[i]->data(0).toString());
	    if (i < feds.size()-1) total.append(",");
	  }
	  total.append(")\n");
        }
    }

    QFile outfile("/exports/slc7/scripts/selectiveupload_template_CC7.py");
    outfile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outstream(&outfile);
    outstream << total;
    outfile.close();

    qDebug() << total;    

    QStringList commandArgs;
    QString uploadString;
    QString uploadAnalString;
    QString useClientString;
    QString saveClientString;
    QString disableModulesString;
    
    uploadString = "false";
    uploadAnalString = "false";
    useClientString="false";
    saveClientString="false";   
    disableModulesString="false";   
      
    if (uploadString == "true") {
        if (QMessageBox::question(NULL, QObject::tr("Confirmation"), QObject::tr("You are going to upload run analysis results to the configuration database. You should have already run the same analysis and verified the quality of the run. Do you want to continue?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;
    }
      
    commandArgs << run << uploadString << uploadAnalString << part << useClientString << disableModulesString << saveClientString;

    if (performUpload) {
        TkTerminal* terminal = new TkTerminal();
        terminal->startProcess("/exports/slc7/scripts/run_analysis_selup_CC7.sh", commandArgs);
        if (terminal->didStartFail()) delete terminal;
        else emit showTabSignal(terminal, "Run Analysis");
    }

}

void FedMap::wheelEvent(QWheelEvent* event) {
    if (event->delta() > 0) zoomSlider->triggerAction(QAbstractSlider::SliderSingleStepAdd);
    if (event->delta() < 0) zoomSlider->triggerAction(QAbstractSlider::SliderSingleStepSub);
}

void FedMap::catchWheelSignal(QWheelEvent* event) {
    if (event->delta() > 0) zoomSlider->triggerAction(QAbstractSlider::SliderSingleStepAdd);
    if (event->delta() < 0) zoomSlider->triggerAction(QAbstractSlider::SliderSingleStepSub);
}

void FedMap::catchZoomSignal(const QPointF& pos) {
    graphicsView->centerOn(pos);
    if (zoomSlider->value() < 27) {
        zoomSlider->setValue(27);
    }
}

