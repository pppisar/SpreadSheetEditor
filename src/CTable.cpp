#include "CTable.h"

CTable::CTable(const CTable &src) {
    m_table = src.m_table;
}

CTable::~CTable() {
    for (auto it: m_table) {
        delete it.second;
    }
}

CCell *CTable::getCell(int x, int y) const {
    auto it = m_table.find(std::make_pair(x, y));
    if (it == m_table.end()) {
        // TODO: Error
    }
    return it->second;
}