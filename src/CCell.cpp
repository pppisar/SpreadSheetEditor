#include "CCell.h"

CCell::CCell(Position position) 
: m_position(position) { }

void CCell::update(bool error,
                   std::string & expression,
                   std::string & value,
                   DataType valueType,
                   std::set<Position> usesCells) {
    m_error = error;
    m_expression = expression;
    m_value = value;
    m_type = valueType;
    m_usesCells = usesCells;
}

void CCell::addDependence(Position cell) {
    m_usedByCells.insert(cell);
}

bool CCell::getErrorStatus() const {
    return m_error;
}

std::string CCell::getValString() const {
    return m_value;
}

DataType CCell::getValType() const {
    return m_type;
}

std::string CCell::getExpression() const {
    return m_expression;
}