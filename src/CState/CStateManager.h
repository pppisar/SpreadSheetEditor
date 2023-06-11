#ifndef PYSAROLE_CSTATEMANAGER_H
#define PYSAROLE_CSTATEMANAGER_H

#include "../CConstants.h"
#include "../CTable.h"
#include "../CCell.h"

#include <string>
#include <fstream>

/**
 * A template class that declares abstract methods 
 * for saving and loading a file
*/
class CStateManager {
public:
    /* Constructor */
    CStateManager(CTable* table, std::string & fileName, std::string & path);

    /* Default destructor */
    virtual ~CStateManager() = default;

    /**
     * Saves the table to a file
     * @return Returns true if the file was saved successfully, otherwise false
    */
    virtual bool save() = 0;

    /**
     * Fills the table according to the data in the file
     * @return Returns true if the file was loaded successfully, otherwise false
    */
    virtual bool load() = 0;
protected:
    std::string m_fileName;
    std::string m_path;
    CTable* m_table;
};

#endif //PYSAROLE_CSTATEMANAGER_H