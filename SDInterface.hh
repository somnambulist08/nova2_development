/******************************************************************************
 * SDInterface.hh
 * 
 * Interface for functions for the SD reader to allow a spoofer
 * 
 * 
 * 02/23/23 - created file
******************************************************************************/
#ifndef SD_INTERFACE_HH
#define SD_INTERFACE_HH
#include "GetData.hh"

class SDInterface {
public:
    SDInterface(){} //Initializer should open the file and write any header collumns //jonse
    virtual void writeLog()=0;
    virtual void closeFile()=0;
    virtual void openFile()=0;
private:
    virtual GetData source; //change to whatever subclass the data's coming from
};






#endif //SD_INTERFACE_HH