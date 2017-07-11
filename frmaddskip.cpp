#include "frmaddskip.h"
#include "Debug.h"
#include "cmssw/SiStripFedKey.h"
#include "cmssw/SiStripFecKey.h"

#include <QMessageBox>

AddSkipChannel::AddSkipChannel(bool fed, bool crate, bool fec, bool ring, bool ccu, bool ccuchan, bool lldchan, QWidget *parent):
    QDialog(parent),
    enableFed(fed),
    enableCrate(crate),
    enableFec(fec),
    enableRing(ring),
    enableCcu(ccu),
    enableCcuChan(ccuchan),
    enableLLDChan(lldchan)
{
    setupUi(this);

    lineFed    ->setEnabled(enableFed    );    
    lineCrate  ->setEnabled(enableCrate  );    
    lineFec    ->setEnabled(enableFec    );    
    lineRing   ->setEnabled(enableRing   );    
    lineCcu    ->setEnabled(enableCcu    );    
    lineCcuChan->setEnabled(enableCcuChan);    
    lineLLDChan->setEnabled(enableLLDChan);    

    if (!enableFed    ) lineFed    ->setText("0");
    if (!enableCrate  ) lineCrate  ->setText("0");
    if (!enableFec    ) lineFec    ->setText("0");
    if (!enableRing   ) lineRing   ->setText("0");
    if (!enableCcu    ) lineCcu    ->setText("0");
    if (!enableCcuChan) lineCcuChan->setText("0");
    if (!enableLLDChan) lineLLDChan->setText("0");
}

AddSkipChannel::~AddSkipChannel() {
}

void AddSkipChannel::accept() {
    bool ok = true;

    unsigned vfed     = lineFed    ->text().toUInt(&ok); 
    unsigned vcrate   = lineCrate  ->text().toUInt(&ok); 
    unsigned vfec     = lineFec    ->text().toUInt(&ok); 
    unsigned vring    = lineRing   ->text().toUInt(&ok); 
    unsigned vccu     = lineCcu    ->text().toUInt(&ok); 
    unsigned vccuchan = lineCcuChan->text().toUInt(&ok); 
    unsigned vlldchan = lineLLDChan->text().toUInt(&ok); 

    if (!ok) {
        QMessageBox::critical(0, tr("Add Channel"), tr("Invalid entries. Please correct") );
        return;      
    }

    if (enableFed) {
        if (vfed == 0) {
            QMessageBox::critical(0, tr("Add Channel"), tr("Enter non-zero FED ID") );
            return;      
        }
        SiStripFedKey fedkey(vfed, 0, 0, 0);
        emit key(QPair<unsigned, unsigned>(fedkey.key(),0));
    }
    else if (enableFed && enableCrate) {
        if (vfed == 0 || vcrate == 0 || vfec == 0) {
            QMessageBox::critical(0, tr("Add Channel"), tr("FED, FEC crate, FEC slot values need to be non-zero") );
            return;      
        }
        SiStripFedKey fedkey(vfed, 0, 0, 0);
        SiStripFecKey feckey(vcrate, vfec, vring, vccu, vccuchan, vlldchan, 0);
        emit key(QPair<unsigned, unsigned>(fedkey.key(),feckey.key()));
    }
    else {
        if (vcrate == 0 || vfec == 0) {
            QMessageBox::critical(0, tr("Add Channel"), tr("Crate and FEC slot values need to be non-zero") );
            return;      
        }
        SiStripFecKey feckey(vcrate, vfec, vring, vccu, vccuchan, vlldchan, 0);
        emit key(QPair<unsigned, unsigned>(0,feckey.key()));
    }

    done(QDialog::Accepted);
}

void AddSkipChannel::reject() {
    done(QDialog::Rejected);
}
