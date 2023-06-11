#include "CCell.h"

CCell::CCell(Position& position, CTable* table) {
    m_position = position;
    m_table = table;
    m_error = true;
}

void CCell::update(std::string & expression) {
    m_expression = expression;
    CParserExpression parser(m_table, expression);
    parser.process();
    // Delete dependencies that have disappeared
    std::vector<Position> lostDependences;
    std::set_difference(m_usesCells.begin(), m_usesCells.end(),
                        parser.getDependences().begin(), parser.getDependences().end(),
                        back_inserter(lostDependences));
    for (Position & cellPos: lostDependences) {
        m_table->createCell(cellPos);
        m_table->getCell(cellPos)->delDependence(m_position);
    }
    // Add dependencies that have appeared
    std::vector<Position> newDependences;
    std::set_difference(parser.getDependences().begin(), parser.getDependences().end(),
                        m_usesCells.begin(), m_usesCells.end(),
                        back_inserter(newDependences));
    for (Position & cellPos: newDependences) {
        m_table->createCell(cellPos);
        m_table->getCell(cellPos)->addDependence(m_position);
    }
    m_value = parser.getResValue();
    m_type = parser.getDataType();
    m_error = parser.haveError();
    m_usesCells = parser.getDependences();

    if (!m_error || !m_value.empty())
        m_table->setChange(true);

    std::set<Position> visitedCells;
    if (checkLoop(m_position, visitedCells)) {
        for (const Position & cellPos: m_usedByCells)
            m_table->getCell(cellPos)->recalc();
    }
    else {
        visitedCells.clear();
        forceChange(true, "LoopError", DataType::String, visitedCells);
    }
}

void CCell::forceChange(bool error, const std::string& value, DataType valueType, std::set<Position> & visitedCells) {
    if (visitedCells.find(m_position) == visitedCells.end()) {
        visitedCells.insert(m_position);
        
        m_error = error;
        m_value = value;
        m_type = valueType;

        for (const Position & cellPos: m_usedByCells)
            m_table->getCell(cellPos)->forceChange(error, value, valueType, visitedCells);
    }
}

void CCell::addDependence(const Position& cell) {
    m_usedByCells.insert(cell);
}

void CCell::delDependence(const Position& cell) {
    m_usedByCells.erase(cell);
}


Position CCell::getPosition() const {
    return m_position;
}

const bool CCell::getErrorStatus() const {
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


const bool CCell::checkLoop(Position& rootPosition, std::set<Position> & visitedCells) const {
    if (m_usesCells.find(rootPosition) != m_usesCells.end())
        return false;
    if (visitedCells.find(m_position) == visitedCells.end()) {
        visitedCells.insert(m_position);
        for (const Position& cellPosition: m_usesCells)
            if (!m_table->getCell(cellPosition)->checkLoop(rootPosition, visitedCells))
                return false;
    }
    return true;
}

void CCell::recalc() {
    CParserExpression parser(m_table, m_expression);
    parser.process();

    m_value = parser.getResValue();
    m_type = parser.getDataType();
    m_error = parser.haveError();

    for (const Position & cellPos: m_usedByCells)
        m_table->getCell(cellPos)->recalc();
}