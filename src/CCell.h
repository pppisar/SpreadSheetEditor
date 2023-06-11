#ifndef PYSAROLE_CCELL_H
#define PYSAROLE_CCELL_H

#include "CConstants.h"
#include "CParser/CParserExpression.h"

#include <string>
#include <vector>
#include <set>
#include <algorithm>

class CCell {
public:
    CCell(Position& position, CTable* table);

    CCell(Position& position,
          std::string & expression,
          std::string & value,
          CTable* table);

    ~CCell() = default;


    // Setters

    void update(std::string & expression);

    void updateDependences();

    void forceChange(bool error, const std::string& value, DataType valueType, std::set<Position> & visitedCells);

    void addDependence(const Position& cell);

    void delDependence(const Position& cell);


    // Getters

    Position getPosition() const;

    const bool getErrorStatus() const;

    std::string getValString() const;

    DataType getValType() const;

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
    const bool checkLoop(Position& rootPosition, std::set<Position> & visitedCells) const;

    void recalc();
};
#endif //PYSAROLE_CCELL_H