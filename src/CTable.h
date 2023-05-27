#ifndef PYSAROLE_CTABLE_H
#define PYSAROLE_CTABLE_H

#include <map>

#include "CConstants.h"
#include "CCell.h"

class CTable {
public:
    CTable() = default;

    CTable(const CTable & src);

    virtual ~CTable();

    // Setter
    void setCell(CPosition position, std::string & expression);

    bool checkCell(CPosition position) const;

    // Getter
    CCell * getCell(CPosition position) const;
private:
    int m_id = 0;

    std::map<CPosition, CCell*> m_table;
};

#endif //PYSAROLE_CTABLE_H
