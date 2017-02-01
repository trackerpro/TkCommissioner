#include "Debug.h"


Debug* Debug::pInstance = 0;

Debug* Debug::Inst(){
    if(pInstance == 0) pInstance = new Debug();
    return pInstance;
}

Debug::Debug(){ // constructor
    setEnabled(false);
    //Initialize(); // you can ignore this function
}

Debug::~Debug(){
    if(pInstance != 0)delete pInstance;
}

void Debug::setEnabled(bool enable) {
    enabled = enable;
}
