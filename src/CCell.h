#ifndef PYSAROLE_CCELL_H
#define PYSAROLE_CCELL_H

#include "CConstants.h"
#include "CParser/CParserExpression.h"

#include <string>
#include <vector>
#include <set>
#include <algorithm>

/**
 * A class that represents a table cell
*/
class CCell {
public:
    /* Constructor */
    CCell(Position& position, CTable* table);

    /* Default destructor */
    ~CCell() = default;


    /**
     * Updates a cell expression and calculates its value
     * @param[in] expression - The specified expression for the cell
    */
    void update(std::string & expression);

    /**
     * Replace cell parameters with precisely specified values
     * Also recursively replaces the parameters of all dependent cells
     * @param[in] error - Error status of the cell
     * @param[in] value - Calculated value of the cell
     * @param[in] valueType - Type of the calculated value (Integer/Double/String)
     * @param[in] visitedCell - Passed cells to prevent repeated changes to the same cell
    */
    void forceChange(bool error, const std::string& value, DataType valueType, std::set<Position> & visitedCells);

    /**
     * Add a cell that depends on this cell
     * @param[in] cell - Position of the dependent cell
    */
    void addDependence(const Position& cell);

    /**
     * Removing a dependent cell from the dependency set
     * @param[in] cell - Position of the cell that has lost its dependency
    */
    void delDependence(const Position& cell);


    /**
     * A method that returns the position of a cell in a table
     * @return Returns the position of a cell
    */
    Position getPosition() const;

    /**
     * A method that returns the state of the cell, whether it has errors
     * @return Returns false if the cell has no error, otherwise true
    */
    const bool getErrorStatus() const;

    /**
     * A method that returns the calculated value of a cell expression
     * @return Returns the calculated value of a cell expression
    */
    std::string getValString() const;

    /**
     * A method that returns the type of the calculated value of a cell expression
     * @return Returns the type of the calculated value of a cell expression
    */
    DataType getValType() const;

    /**
     * Method that returns the expression that was assigned to the cell
     * @return Returns the expression of the cell
    */
    std::string getExpression() const;
private:
    Position m_position;
    CTable* m_table;

    bool m_error;
    std::string m_expression;
    std::string m_value;
    DataType m_type;

    // Which cells this cell refers to
    std::set<Position> m_usesCells;

    // Who refers to this cell.
    std::set<Position> m_usedByCells;
private:
    /**
     * Recursive method for finding a loop with the cells it depends on
     * @param[in] rootPosition - The position of the cell relative to which the cycles are searched
     * @param[in] visitedCells - Already passed cells
     * @return Returns true if a loop was found, otherwise false
    */
    const bool checkLoop(Position& rootPosition, std::set<Position> & visitedCells) const;

    /**
     * Recursive method for calculating all dependent cells
    */
    void recalc();
};
#endif //PYSAROLE_CCELL_H