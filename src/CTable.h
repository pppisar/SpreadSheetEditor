#ifndef PYSAROLE_CTABLE_H
#define PYSAROLE_CTABLE_H

#include "CConstants.h"

#include <map>

class CCell;

class CTable {
public:
    CTable();

    virtual ~CTable();

    void reset();

    // Setters

    void createCell(Position position);

    void setChange(bool isChanged);

    void setName(const FileName& fileName);
    
    void evaluateDependences(); 


    // Getters

    const std::map<Position, CCell*> & getTable() const;

    CCell * getCell(const Position& position) const;

    const bool checkCell(const Position& position) const;

    FileName getName() const;

    const bool isNamed() const;

    const bool isChanged() const;
private:
    bool m_isNamed;
    bool m_isChanged;
    FileName m_fileName;
    std::map<Position, CCell*> m_table;
};

#endif //PYSAROLE_CTABLE_H