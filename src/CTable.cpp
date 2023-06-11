#include "CTable.h"
#include "CCell.h"

CTable::CTable() {
    m_isNamed = false;
    m_isChanged = false;
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

void CTable::addCell(Position& position, 
                     std::string & expression, 
                     std::string & value) {
    if (!checkCell(position)) {
        CCell * cell = new CCell(position, expression, value, this);
        m_table[position] = cell;
    }
}

void CTable::setChange(bool isChanged) {
    m_isChanged = isChanged;
}

void CTable::setName(const FileName& fileName) {
    m_fileName = fileName;
    m_isNamed = true;
}

void CTable::evaluateDependences() {
    
}


// Getters

const std::map<Position, CCell*> & CTable::getTable() const {
    return m_table;
}

CCell* CTable::getCell(const Position& position) const {
    auto it = m_table.find(position);
    return it->second;
}

const bool CTable::checkCell(const Position& position) const {
    if (m_table.find(position) == m_table.end())
        return false;
    return true;
}

FileName CTable::getName() const {
    return m_fileName;
}

const bool CTable::isNamed() const {
    return m_isNamed;
}

const bool CTable::isChanged() const {
    return m_isChanged;
}