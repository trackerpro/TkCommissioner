#ifndef FRMTAGUPLOAD_H
#define FRMTAGUPLOAD_H

#include <sstream>

// Qt includes
#include <QValidator> 
#include <QRegExpValidator> 
#include <QRegExp> 
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QVector>
#include <QPushButton>
#include <QProgressDialog>
#include <QInputDialog>
#include <QDialogButtonBox>
#include <QStandardItemModel>
#include <QtSql/QSqlQuery>

// Debug output
#include "Debug.h"
#include "DbConnection.h"

// UI file
#include "ui_frmsavetags.h"

class TagUpload : public QDialog, private Ui::TagUpload {

    Q_OBJECT
 
    public:

        typedef std::multimap<int,std::pair<int, QStandardItem*> > iiQMultimap;

        TagUpload(QWidget *parent = 0) {
            Q_UNUSED(parent);

            setupUi(this); 

            closeTicket_ = false;
            currentDevice = NULL;
            currentComment = NULL;

            buttonOk->setEnabled(false);

            tagsModel = new QStandardItemModel(0, 2,this);
            tagsModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Device Id"));
            tagsModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Comment"));

            uploadList->setModel(tagsModel);
            uploadList->setSelectionMode(QAbstractItemView::SingleSelection);
            uploadList->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
            uploadList->setSelectionBehavior(QAbstractItemView::SelectRows);

            connect(uploadList->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(devChanged(QModelIndex,QModelIndex)));
        }

        ~TagUpload() {
        }

        void setCloseTicketFlag(bool flag) {
            closeTicket_ = flag;
            if(closeTicket_) topLabel->setText("You want to close tickets for the following items in the database");
        }

        void setUploadTag(int tagNumber, QString tagDescription) {
            tagNumber_ = tagNumber;
            tagDescription_ = tagDescription;
            displayTag->setText(tagDescription_);
        }

        void setRunNumber(int runNumber) {
            runNumber_= runNumber;
        }

        void setOpenTicketAndTagList( std::multimap< int, std::pair<int, QStandardItem*> > openTickets, std::map<int, std::string> tagList) {
            openTickets_ = openTickets;
            tagList_ = tagList;
        }

        void setTagDeviceList(QVector<QStandardItem*> list) {
            for (int i = 0; i < list.size(); i++) {
                QList<QStandardItem*> itemrow;
                itemrow.append(list[i]);
                QStandardItem* comm = new QStandardItem("");
                comm->setEditable(false);
                itemrow.append(comm);
                tagsModel->appendRow(itemrow);
            }
        }

    private:
        QStandardItemModel* tagsModel;
        bool closeTicket_;
        int runNumber_;
        int tagNumber_;
        QString tagDescription_;
        std::multimap<int, std::pair<int,QStandardItem*> > openTickets_;
        std::map<int, std::string> tagList_;

        QStandardItem* currentDevice;
        QStandardItem* currentComment;

        int openTicket(int runNumber, int deviceId, const char* tagDescription, const char* comment, const char* author) {
            int ticketId = 0;
            std::stringstream myQuery;
            myQuery << "select PkgTkAnalysisLog.openTicket(" << runNumber << "," << deviceId << ",'" << tagDescription << "','" << comment << "','" << author << "') from dual";
            
            if (DbConnection::Inst()->dbConnected()) {
                QSqlQuery query(myQuery.str().c_str());
                bool rset = query.exec();
                
                if (rset) {
                    while(query.next()) ticketId = query.value(0).toInt();
                }
            }
            else {
	            if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: Unable to find DB connection\n";
            } 
            return ticketId;
        }

        bool insertComment(int runNumber, int deviceId, const char* tagDescription, const char* comment, const char* author) {
            std::stringstream myQuery;
            myQuery << "BEGIN PkgTkAnalysisLog.insertTkAnalysisLog(" << runNumber << "," << deviceId << ",'" << tagDescription << "','" << comment << "','" << author << "'); END;";
            
            if (DbConnection::Inst()->dbConnected()) {
                QSqlQuery query(myQuery.str().c_str());
                bool rset = query.exec();
                return rset;
            }
            else {
	            if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: Unable to find DB connection\n";
                return false;
            } 
        }
            
        bool updateComment(int runNumber, int deviceId, const char* tagDescription, const char* comment, const char* author) {
            std::stringstream myQuery;
            myQuery << "BEGIN PkgTkAnalysisLog.updateTkAnalysisLog(" << runNumber << "," << deviceId << ",'" << tagDescription << "','" << comment << "','" << author << "'); END;";
            
            if (DbConnection::Inst()->dbConnected()) {
                QSqlQuery query(myQuery.str().c_str());
                bool rset = query.exec();
                return rset;
            }
            else {
	            if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: Unable to find DB connection\n";
                return false;
            } 
        }


        bool closeTicket(int deviceId, const char* tagDescription) {
            std::stringstream myQuery;
            myQuery << "BEGIN PkgTkAnalysisLog.closeTicket(" << deviceId << ",'" << tagDescription << "'); END;";
            
            if (DbConnection::Inst()->dbConnected()) {
                QSqlQuery query(myQuery.str().c_str());
                bool rset = query.exec();
                return rset;
            }
            else {
	            if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: Unable to find DB connection\n";
                return false;
            } 
        }


        bool deleteTicket(int runNumber, int deviceId, const char* tagDescription) {

            std::stringstream myQuery;
            myQuery << "BEGIN PkgTkAnalysisLog.deleteTkAnalysisLog(" << runNumber << "," << deviceId << ",'" << tagDescription << "'); END;";
            
            if (DbConnection::Inst()->dbConnected()) {
                QSqlQuery query(myQuery.str().c_str());
                bool rset = query.exec();
                return rset;
            }
            else {
	            if(Debug::Inst()->getEnabled()) qDebug() << "ERROR: Unable to find DB connection\n";
                return false;
            } 
        }

    public Q_SLOTS:
        void devChanged(QModelIndex current, QModelIndex) {
            currentDevice  = tagsModel->item(current.row(),0);
            currentComment = tagsModel->item(current.row(),1);
        }

        void on_confirmCheck_toggled (bool) {
            buttonOk->setEnabled( static_cast<bool>(confirmCheck->isChecked() ) );
        }

        void on_buttonCancel_clicked() {
            done(0);                    
        }

        void on_btnAddComment_clicked() {
            bool ok;
            QString text = QInputDialog::getText(this, "DB Upload", "Enter Comment", QLineEdit::Normal, QString::null, &ok);
            if (currentComment) currentComment->setText(text);
        }

        void on_buttonOk_clicked() {

            bool ok;
            QString text = QInputDialog::getText(this, "DB Upload", "Enter Your Name (author)", QLineEdit::Normal, QString::null, &ok);
            
            if (ok && !text.isEmpty()) {
                QProgressDialog progress("Upload to DB", "&Cancel", 0, tagsModel->rowCount(), this);
                progress.show();
                QString label;
                
                int i = 0;
                while (i < tagsModel->rowCount()) {
                    std::pair<iiQMultimap::iterator, iiQMultimap::iterator> itp = openTickets_.equal_range(static_cast<int>(tagsModel->item(i, 0)->text().toInt()   ) );
                    
                    int nrOpenTickets = 0;
                    bool hasOpenTicket = false;
                    bool hasCommentInRun = false;
                    
                    iiQMultimap::iterator itTicket;
                    for (itTicket = itp.first; itTicket != itp.second; ++itTicket) {
                        if ( itTicket != openTickets_.end()  && tagList_[((*itTicket).second.first)].c_str() == tagDescription_  ) {
                            hasOpenTicket = true;
                            ++nrOpenTickets;
                            QStandardItem *child = (*itTicket).second.second;
                            QString help("Run Nr: ");
                            int pos = (child->text().toStdString().find(help.toStdString()))+ help.length();
                            int pos2 = child->text().toStdString().find("\n",pos);
                            QString runNr =  child->text().mid(pos,(pos2-pos));
                            bool worked = false;
                            int irunNr = runNr.toInt(&worked);
                            if(worked && irunNr == runNumber_ ) hasCommentInRun = true;
                        }
                    }
                    
                    progress.setLabelText(label.sprintf("Creating Ticket for device %d", +static_cast<int>(tagsModel->item(i, 0)->text().toInt() ) ) );
                    progress.setValue(i);
                    if (progress.wasCanceled()) break;
                    
                    int localDeviceId = tagsModel->item(i, 0)->text().toInt();
                                        
                    if(closeTicket_ && hasOpenTicket) {
                        QString str = "CLOSED:" + tagsModel->item(i, 1)->text();
                        if(hasCommentInRun && nrOpenTickets == 1) deleteTicket(runNumber_, localDeviceId, tagDescription_.toStdString().c_str());
                        else if(hasCommentInRun) {
                            updateComment(runNumber_,localDeviceId, tagDescription_.toStdString().c_str(), str.toStdString().c_str() , text.toStdString().c_str());
                            closeTicket(localDeviceId, tagDescription_.toStdString().c_str() );
                        } 
                        else {
                            insertComment(runNumber_,localDeviceId, tagDescription_.toStdString().c_str(), str.toStdString().c_str() , text.toStdString().c_str());
                            closeTicket( localDeviceId ,  tagDescription_.toStdString().c_str() );
                        }
                    } 
                    else {
                        if(hasOpenTicket) {
                            if(hasCommentInRun) updateComment(runNumber_,localDeviceId, tagDescription_.toStdString().c_str(), qPrintable(tagsModel->item(i, 1)->text()), text.toStdString().c_str());
                            else insertComment(runNumber_,localDeviceId, tagDescription_.toStdString().c_str(), qPrintable(tagsModel->item(i, 1)->text()), text.toStdString().c_str());
                        } 
                        else openTicket(runNumber_,localDeviceId, tagDescription_.toStdString().c_str(), qPrintable(tagsModel->item(i, 1)->text()), text.toStdString().c_str() );
                    }
                    ++i;
                }
            } 

            else return;
        }

};
#endif



