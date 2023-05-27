#ifndef PYSAROLE_CTABLE_H
#define PYSAROLE_CTABLE_H

#include <map>

#include "CConstants.h"
#include "CCell.h"
#include "CParser.h"

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

    void evaluate(); 
private:
    int m_id = 0;

    CParser m_parser;

    std::map<CPosition, CCell*> m_table;
};

#endif //PYSAROLE_CTABLE_H
