#ifndef PYSAROLE_CSTATETXT_H
#define PYSAROLE_CSTATETXT_H

#include "CStateManager.h"
#include "../CConstants.h"
#include "../CTable.h"
#include "../CCell.h"

/**
 * The class responsible for saving a table to a text file 
 * and reading a table from a text file
*/
class CStateTxt: public CStateManager {
public:
    /* Default constructor */
    CStateTxt(CTable* table, std::string & fileName, std::string & path);

    /* Default destructor */
    ~CStateTxt() = default;

    /**
     * Saves the table to a text file
     * @return Returns true if the file was saved successfully, otherwise false
    */
    bool save() override;

    /**
     * Fills the table according to the data in the binary file
     * @return Returns true if the file was loaded successfully, otherwise false
    */
    bool load() override;
};

#endif //PYSAROLE_CSTATEBINARY_H