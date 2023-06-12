#ifndef PYSAROLE_CPARSEREXPRESSION_H
#define PYSAROLE_CPARSEREXPRESSION_H

#include "CParser.h"
#include "../CCell.h"
#include "../CTable.h"

/**
 * A class that fully processes an arithmetic expression
*/
class CParserExpression : public CParser {
public:
    /* Default constructor */
    CParserExpression(CTable* table, std::string& expression);

    /* Default destructor */
    ~CParserExpression() = default;

    /**
     * A method that processes an expression contained in a parser
    */
    void process() override;

    /**
     * A method that returns the false status of an expression after evaluation
     * @return Returns true if the expression contains errors, otherwise false
    */
    const bool haveError() const;

    /**
     * A method that returns the calculated value of an expression
     * @return Returns calculated value of an expression
    */
    std::string getResValue() const;

    /**
     * A method that returns the type of the calculated value of an expression
     * @return Returns the type of the calculated value of an expression (Integer/Double/String)
    */
    DataType getDataType() const;

    /**
     * A method that returns the calculated dependencies that were in the expression
     * @return Returns a reference to the set of cell positions on which this expression depends
    */
    const std::set<Position>& getDependences() const;
private:
    bool m_error = false;
    
    std::string m_resValue;
    DataType m_resDataType = DataType::String;
    
    std::set<Position> m_dependences;
};

#endif //PYSAROLE_CPARSEREXPRESSION_H