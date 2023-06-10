#include "CTable.h"
#include "CCell.h"

CTable::CTable(const CTable &src) {
    m_table = src.m_table;
}

CTable::~CTable() {
    for (auto & it: m_table)
        delete it.second;
}

// Setters

void CTable::createCell(Position position) {
    if (!checkCell(position)) {
        CCell * cell = new CCell(position, this);
        m_table[position] = cell;
    }
}

void CTable::setChange(bool isChanged) {
    m_isChanged = isChanged;
}

void CTable::setNamed(bool isNamed) {
    m_isNamed = isNamed;
}

void CTable::evaluateDependences() {
    
}


// Getters

const std::map<Position, CCell*> & CTable::getTable() const {
    return m_table;
}

CCell* CTable::getCell(Position position) const {
    auto it = m_table.find(position);
    return it->second;
}

bool CTable::checkCell(Position position) const {
    if (m_table.find(position) == m_table.end())
        return false;
    return true;
}

bool CTable::isNamed() const {
    return m_isNamed;
}

bool CTable::isChanged() const {
    return m_isChanged;
}