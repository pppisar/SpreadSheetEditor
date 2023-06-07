#ifndef PYSAROLE_CCELL_H
#define PYSAROLE_CCELL_H

#include "CConstants.h"
#include <string>
#include <set>

class CCell {
public:
    CCell(Position position);

    ~CCell() = default;

    // Setter
    void update(bool error,
                std::string & expression,
                std::string & value,
                DataType valueType,
                std::set<Position> usesCells);

    void addDependence(Position cell);

    // Getters

    Position getPosition() const;

    bool getErrorStatus() const;

    std::string getValString() const;

    DataType getValType() const;

    std::string getExpression() const;
private:
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