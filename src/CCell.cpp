#include "CCell.h"

CCell::CCell(Position position, CTable* table) 
: m_position(position), m_table(table) { }

void CCell::update(std::string & expression) {
    m_expression = expression;
    CParserExpression parser(m_table, expression);
    parser.process();
    // Delete dependencies that have disappeared
    std::vector<Position> lostDependences;
    std::set_difference(m_usesCells.begin(), m_usesCells.end(),
                        parser.getDependences().begin(), parser.getDependences().end(),
                        back_inserter(lostDependences));
    for (Position & cellPos: lostDependences)
        m_table->getCell(cellPos)->delDependence(m_position);
    // Add dependencies that have appeared
    std::vector<Position> newDependences;
    std::set_difference(parser.getDependences().begin(), parser.getDependences().end(),
                        m_usesCells.begin(), m_usesCells.end(),
                        back_inserter(newDependences));
    for (Position & cellPos: newDependences)
        m_table->getCell(cellPos)->addDependence(m_position);
    m_value = parser.getResValue();
    m_type = parser.getDataType();
    m_error = parser.haveError();
    m_usesCells = parser.getDependences();

    if (!m_error) {
        std::set<Position> visitedCells;
        if (checkLoop(m_position, visitedCells)) {
            visitedCells.clear();
            visitedCells.insert(m_position);
            for (const Position & cellPos: m_usedByCells)
                m_table->getCell(cellPos)->recalc(visitedCells);
        }
        else {
            visitedCells.clear();
            forceChange(true, "LoopError", DataType::String, visitedCells);
        }
    }

}

bool CCell::checkLoop(Position rootPosition, std::set<Position> & visitedCells) {
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


void CCell::recalc(std::set<Position> & visitedCells) {
    if (visitedCells.find(m_position) == visitedCells.end()) {
        visitedCells.insert(m_position);
        CParserExpression parser(m_table, m_expression);
        parser.process();

        m_value = parser.getResValue();
        m_type = parser.getDataType();
        m_error = parser.haveError();

        for (const Position & cellPos: m_usedByCells)
            m_table->getCell(cellPos)->recalc(visitedCells);
    }
}

void CCell::forceChange(bool error, std::string value, DataType valueType, std::set<Position> & visitedCells) {
    if (visitedCells.find(m_position) == visitedCells.end()) {
        visitedCells.insert(m_position);
        
        m_error = error;
        m_value = value;
        m_type = valueType;

        for (const Position & cellPos: m_usedByCells)
            m_table->getCell(cellPos)->recalc(visitedCells);
    }
}

void CCell::addDependence(Position cell) {
    m_usedByCells.insert(cell);
}

void CCell::delDependence(Position cell) {
    m_usedByCells.erase(cell);
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