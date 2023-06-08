#ifndef PYSAROLE_CPARSEREXPRESSION_H
#define PYSAROLE_CPARSEREXPRESSION_H

#include "CParser.h"

class CParserExpression : public CParser {
public:
    CParserExpression(CTable* table, std::string expression);

    ~CParserExpression() = default;

    void process() override;

    bool haveError() const;

    std::string getResValue() const;

    DataType getDataType() const;

    std::set<Position> getDependences() const;
private:
    bool m_error;
    
    std::string m_resValue;
    DataType m_resDataType = DataType::String;
    
    std::set<Position> m_dependences;
};

#endif //PYSAROLE_CPARSEREXPRESSION_H