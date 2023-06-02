#include "CTable.h"

CTable::CTable(const CTable &src) {
    m_id = src.m_id;
    m_table = src.m_table;
}

CTable::~CTable() {
    for (auto & it: m_table)
        delete it.second;
}

void CTable::setCell(Position position, 
                     std::string & expression, 
                     ParseResult& info) {
    std::string value = expression;

    if (m_table.find(position) == m_table.end()) {
        CCell * cell = new CCell(m_id++, expression, info);

        m_table[position] = cell;
    }
    else {
        m_table[position]->update(expression, info);
    }
}

bool CTable::checkCell(Position position) const {
    if (m_table.find(position) == m_table.end())
        return false;
    return true;
}

CCell* CTable::getCell(Position position) const {
    auto it = m_table.find(position);
    if (it == m_table.end()) {
        // TODO: Error
    }
    return it->second;
}

void CTable::evaluate() {
    
}