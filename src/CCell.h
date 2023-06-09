#ifndef PYSAROLE_CCELL_H
#define PYSAROLE_CCELL_H

#include "CConstants.h"
#include "CParser/CParserExpression.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>

// class CTable; // Direct declaration of the CTable class

class CCell {
public:
    CCell(Position position, CTable* table);

    ~CCell() = default;

    void update(std::string & expression);

    bool checkLoop(Position rootPosition, std::set<Position> & visitedCells);

    void recalc();

    void forceChange(bool error, std::string value, DataType valueType, std::set<Position> & visitedCells);

    void addDependence(Position cell);

    void delDependence(Position cell);

    // Getters

    Position getPosition() const;

    bool getErrorStatus() const;

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
};
#endif //PYSAROLE_CCELL_H