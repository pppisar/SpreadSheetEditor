#ifndef PYSAROLE_CTABLE_H
#define PYSAROLE_CTABLE_H

#include <map>

#include "CCell.h"

class CTable {
public:
    CTable() = default;

    CTable(const CTable & src);

    ~CTable();

    // Getter
    CCell * getCell(int x, int y) const;
private:
    std::map<std::pair<int, int>, CCell*> m_table;
};


#endif //PYSAROLE_CTABLE_H