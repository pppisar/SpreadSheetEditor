#ifndef PYSAROLE_CTABLE_H
#define PYSAROLE_CTABLE_H

#include "CConstants.h"

#include <map>

class CCell;

/**
 * The CTable class represents a table (matrix) that 
 * consists of cells (objects of the CCell class)
*/
class CTable {
public:
    /* Constructor */
    CTable();
    
    /* Destructor */
    virtual ~CTable();

    /**
     * A method that deletes information from the entire table
    */
    void reset();


    /**
     * Creates an empty cell at the specified position if no cell exists at this position.
     * @param[in] position - Position of the cell
    */ 
    void createCell(Position position);

    /**
     * Changes the editing status of the table. 
     * Was it edited after saving/downloading?
     * @param[in] isChanged - Status: there are changes (true) / no changes (false)
    */
    void setChange(bool isChanged);

    /**
     * Assigns a name to the table.
     * @param[in] fileName - Name of the loaded/saved table
    */
    void setName(const FileName& fileName);


    /**
     * Returns the table structure (positions by which cells are hidden)
     * @return Returns a reference to the CCell table (map)
    */
    const std::map<Position, CCell*> & getTable() const;

    /**
     * A method that returns the cell that is hidden at the specified position
     * @param[in] position - Cell position
     * @return Returns a pointer to the selected cell (CCell)
    */
    CCell * getCell(const Position& position) const;

    /**
     * Checks for the presence of a cell at a specific position
     * @param[in] position - Cell position
     * @return Returns true if there is a cell at the position, otherwise false
    */
    const bool checkCell(const Position& position) const;

    /**
     * A method that returns the name of the loaded/created table.
     * @return Returns file name of the table
    */
    FileName getName() const;

    /**
     * Check if the table has been assigned a name
     * @return Returns true if the name is assigned, otherwise false
    */
    const bool isNamed() const;

    /**
     * Checks if the table has any changes
     * @return Returns true if the table has unsaved changes, otherwise false
    */
    const bool isChanged() const;
private:
    bool m_isNamed;
    bool m_isChanged;
    FileName m_fileName;
    std::map<Position, CCell*> m_table;
};

#endif //PYSAROLE_CTABLE_H