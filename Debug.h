#ifndef DEBUG_H
#define DEBUG_H

#include <QDebug>


/** \Class Debug
 * 
 * \brief Singleton class to enable/disable debugging information at
 * run time throughout the application with the need to recompile
 */ 
class Debug {

    private:
        static Debug* pInstance;
        bool enabled;

    protected:
        /**
         * constructor
         */
        Debug() {
            setEnabled(false);
        }

        /**
         * destructor
         */
        ~Debug() {
            if(pInstance != 0) delete pInstance;
        }

    public:
        /**
         * return static instance of this class
         */
        static Debug* Inst() {
            if(pInstance == 0) pInstance = new Debug();
            return pInstance;
        }

        /**
         * change status of enabled bit. Default is false
         */ 
        void setEnabled(bool e = false) {
            enabled = e;
        }

        /**
         * get status of enable bit
         */ 
        bool getEnabled() {
            return enabled;
        }

        /**
         * print the tkCommissioner logo
         */ 
        void printLogo() {
            const char* sdebug= "DEBUG MODE";
            if(!Debug::Inst()->getEnabled()) sdebug = "          ";
            
            qDebug()  << "\n"
                      << "   \e[1;30m********************************************************************\e[0m\n"
                      << "   \e[1;30m*\e[0m     \e[1;30m _   _    ___                 _       _                      \e[0m\e[1;30m*\e[0m\n"
                      << "   \e[1;30m*\e[0m     \e[1;34m| |_| |__/ __|___ _ __  _ __ (_)_____(_)___ _ _  ___ _ _     \e[0m\e[1;30m*\e[0m\n"
                      << "   \e[1;30m*\e[0m     \e[1;34m|  _| / / (__/ _ \\ '  \\| '  \\| (_-<_-< / _ \\ ' \\/ -_) '_|    \e[0m\e[1;30m*\e[0m\n"
                      << "   \e[1;30m*\e[0m     \e[1;34m \\__|_\\_\\\\___\\___/_|_|_|_|_|_|_/__/__/_\\___/_||_\\___|_|      \e[0m\e[1;30m*\e[0m\n"
                      << "   \e[1;30m*\e[0m                                                                  \e[1;30m*\e[0m\n"
                      << "   \e[1;30m*\e[0m                        (tkCommissioner)                          \e[1;30m*\e[0m\n"
                      << "   *                          "       <<     sdebug      << "                            *\n"
                      << "   \e[1;30m*\e[0m                                                                  \e[1;30m*\e[0m\n"
                      << "   \e[1;30m*\e[0m In case of problems have a look at:                              \e[1;30m*\e[0m\n"
                      << "   \e[1;30m*\e[0m  https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideTkCommissioner  \e[1;30m*\e[0m\n"
                      << "   \e[1;30m*\e[0m                                                                  \e[1;30m*\e[0m\n"
                      << "   \e[1;30m********************************************************************\e[0m\n";
        }

};


#endif
