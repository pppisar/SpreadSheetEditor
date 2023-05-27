#include "CTable.h"

CTable::CTable(const CTable &src) {
    m_id = src.m_id;
    m_table = src.m_table;
}

CTable::~CTable() {
    for (auto & it: m_table)
        delete it.second;
}

void CTable::setCell(CPosition position, std::string & expression) {
    // parsing of expression
    std::string value = expression;

    if (m_table.find(position) == m_table.end()) {
        CCell * cell = new CCell(m_id++, value, expression, false);

        m_table[position] = cell;
    }
    else {
        m_table[position]->update(expression,value, false);
    }
}

bool CTable::checkCell(CPosition position) const {
    if (m_table.find(position) == m_table.end())
        return false;
    return true;
}

CCell* CTable::getCell(CPosition position) const {
    auto it = m_table.find(position);
    if (it == m_table.end()) {
        // TODO: Error
    }
    return it->second;
}