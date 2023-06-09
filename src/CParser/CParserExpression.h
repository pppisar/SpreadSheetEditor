#ifndef PYSAROLE_CPARSEREXPRESSION_H
#define PYSAROLE_CPARSEREXPRESSION_H

#include "CParser.h"
#include "../CCell.h"
#include "../CTable.h"
#include <ncurses.h> // del

class CParserExpression : public CParser {
public:
    CParserExpression(CTable* table, std::string& expression);

    ~CParserExpression() = default;

    void process() override;

    bool haveError() const;

    std::string getResValue() const;

    DataType getDataType() const;

    const std::set<Position>& getDependences() const;
private:
    bool m_error = false;
    
    std::string m_resValue;
    DataType m_resDataType = DataType::String;
    
    std::set<Position> m_dependences;
};

#endif //PYSAROLE_CPARSEREXPRESSION_H