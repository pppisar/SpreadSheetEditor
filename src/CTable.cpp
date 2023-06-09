#include "CTable.h"
#include "CCell.h"

CTable::CTable(const CTable &src) {
    m_table = src.m_table;
}

CTable::~CTable() {
    for (auto & it: m_table)
        delete it.second;
}

void CTable::createCell(Position position) {
    if (!checkCell(position)) {
        CCell * cell = new CCell(position, this);
        m_table[position] = cell;
    }
}

bool CTable::checkCell(Position position) const {
    if (m_table.find(position) == m_table.end())
        return false;
    return true;
}

CCell* CTable::getCell(Position position) const {
    auto it = m_table.find(position);
    return it->second;
}

void CTable::evaluate() {
    
}