#ifndef PYSAROLE_CTABLE_H
#define PYSAROLE_CTABLE_H

#include <map>

#include "CConstants.h"
// #include "CCell.h"

class CCell;

class CTable {
public:
    CTable() = default;

    CTable(const CTable & src);

    virtual ~CTable();

    // Setter
    void createCell(Position position);

    bool checkCell(Position position) const;

    // Getter
    CCell * getCell(Position position) const;

    void evaluate(); 
private:
    std::map<Position, CCell*> m_table;
};

#endif //PYSAROLE_CTABLE_H
