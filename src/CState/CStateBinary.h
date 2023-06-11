#ifndef PYSAROLE_CSTATEBINARY_H
#define PYSAROLE_CSTATEBINARY_H

#include "CStateManager.h"
#include "../CConstants.h"
#include "../CTable.h"
#include "../CCell.h"

#include <ncurses.h>

/**
 * The class responsible for saving a table to a binary file 
 * and reading a table from a binary file
*/
class CStateBinary: public CStateManager {
public:
    /* Default constructor */
    CStateBinary(CTable* table, std::string & fileName, std::string & path);

    /* Default destructor */
    ~CStateBinary() = default;

    /**
     * Saves the table to a binary file
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