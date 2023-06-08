#ifndef PYSAROLE_CCELL_H
#define PYSAROLE_CCELL_H

#include "CConstants.h"
#include "CParser/CParserExpression.h"
#include <string>
#include <vector>
#include <set>

class CTable; // Direct declaration of the CTable class

class CCell {
public:
    CCell(Position position, CTable* table);

    ~CCell() = default;

    // Setter
    void update(std::string & expression);

    bool checkLoop(Position rootPosition);

    void addDependence(Position cell);

    void delDependence(Position cell);

    // Getters

    Position getPosition() const;

    bool getErrorStatus() const;

    std::string getValString() const;

    DataType getValType() const;

    std::string getExpression() const;
private:
    CTable* m_table;

    Position m_position;
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