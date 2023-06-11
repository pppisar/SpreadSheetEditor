#ifndef PYSAROLE_CTABLE_H
#define PYSAROLE_CTABLE_H

#include <map>

#include "CConstants.h"

class CCell;

class CTable {
public:
    CTable() = default;

    CTable(const CTable & src);

    virtual ~CTable();


    // Setters

    void createCell(Position position);

    void addCell(Position & position, 
                 std::string & expression, 
                 std::string & value);

    void setChange(bool isChanged);

    void setNamed(bool isNamed);
    
    void evaluateDependences(); 


    // Getters

    const std::map<Position, CCell*> & getTable() const;

    CCell * getCell(Position position) const;

    bool checkCell(Position position) const;

    bool isNamed() const;

    bool isChanged() const;
private:
    bool m_isNamed = false;
    bool m_isChanged = false;

    std::map<Position, CCell*> m_table;
};

#endif //PYSAROLE_CTABLE_H