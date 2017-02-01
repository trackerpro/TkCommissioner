
/** \Class Debug
 * 
 * \brief Singleton class to enable/disable debugging information at
 * run time throughout the application with the need to recompile
 */ 
class Debug {
    public:
        /**
         * return static instance of this class
         */
        static Debug* Inst();
        //void Initialize();
        /**
         * change status of enabled bit. Default is false
         */ 
        void setEnabled(bool enable = false);
        /**
         * get status of enable bit
         */ 
        bool getEnabled() {return enabled;}
        ~Debug();
    protected:
        Debug(); // constructor
    private:
        static Debug* pInstance;
        bool enabled;
};

