#ifndef DBCONNECTION_H
#define DBCONNECTION_H

// Qt interface to Oracle DB
#include <QtSql/QSqlDatabase>

// Project Debug class
#include "Debug.h"

// C++ string implementation
#include <string>

/** \Class DbConnection
 *
 * \brief Singleton class to facilitate access to an oracle database
 */ 
class DbConnection {
    private:
        static DbConnection* pInstance;
        QSqlDatabase dbConnection_;
        bool dbConnected_;

    protected:
        /**
         * constructor
         */
        DbConnection():
	dbConnection_(QSqlDatabase::addDatabase("QOCI")), 
	  dbConnected_(false)
        { 
        }

    public:
        /**
         * return static instance of this class
         */
        static DbConnection* Inst() {
            if(pInstance == 0) pInstance = new DbConnection();
            return pInstance;
        }
        
        /**
         * initiate connection to database using a connect string of the
         * form schema/password@database
         */ 
        bool connectDb(const std::string &dbConnectString) {
            std::string::size_type slash = dbConnectString.find_first_of("/");
            std::string::size_type at = dbConnectString.find_first_of("@");
            
            if(slash == std::string::npos || at == std::string::npos ) {
                if (Debug::Inst()->getEnabled()) qDebug() << "could not parse DB connection string";
                return false;
            }
            std::string login = dbConnectString.substr(0,slash);
            std::string passwd = dbConnectString.substr(slash+1,at-slash-1);
            std::string dbPath = dbConnectString.substr(at+1);
            
            return connectDb(login,passwd,dbPath);
        }

        /**
         * initiate connection to database schema, password and database
         * as separate input fields
         */ 
        bool connectDb(const std::string &login, const std::string &passwd, const std::string &dbPath) {
            dbConnection_.setDatabaseName(dbPath.c_str());
            dbConnection_.setUserName(login.c_str());
            dbConnection_.setPassword(passwd.c_str());
            dbConnected_ = dbConnection_.open();
            return true;
        }

        /**
         * return database connection managed by this class so the user
         * can perform action on the database
         */ 
        QSqlDatabase dbConnection() {
            return dbConnection_;
        } 

        /**
         * return status of database connection
         */
        bool dbConnected() {
            return dbConnected_; 
        }

        /**
         * destructor
         */
        ~DbConnection() {
            if(pInstance != 0) delete pInstance;
        }

};

#endif


