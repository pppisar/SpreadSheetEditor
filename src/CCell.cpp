#include "CCell.h"

CCell::CCell(Position position, CTable* table) 
: m_position(position), m_table(table) { }

void CCell::update(std::string & expression) {
    m_expression = expression;
    CParserExpression parser(m_table, expression);
    parser.process();

    m_value = parser.getResValue();
    m_type = parser.getDataType();
    m_error = parser.haveError();

    // Delete dependencies that have disappeared
    std::vector<Position> lostDependences;
    std::set_difference(m_usesCells.begin(), m_usesCells.end(),
                        parser.getDependences().begin(), parser.getDependences().end(),
                        lostDependences.begin());
    for (Position & cellPos: lostDependences)
        m_table->getCell(cellPos)->delDependence(m_position);

    // Add dependencies that have appeared
    std::vector<Position> newDependences;
    std::set_difference(parser.getDependences().begin(), parser.getDependences().end(),
                        m_usesCells.begin(), m_usesCells.end(),
                        newDependences.begin());
    for (const Position & cellPos: newDependences)
        m_table->getCell(cellPos)->addDependence(m_position);

    m_usesCells = parser.getDependences();

    if (!m_error) {
        if (checkLoop(m_position)) {
            // TODO: Calculate all cells that depend on it
        }
        else {
            // TODO: Set LoopError to all dependent cells
        }
    }

}

bool CCell::checkLoop(Position rootPosition) {
    if (m_usesCells.find(rootPosition) != m_usesCells.end())
        return false;
    for (const Position& cellPosition: m_usesCells)
        if (!m_table->getCell(cellPosition)->checkLoop(rootPosition))
            return false;
    return true;
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