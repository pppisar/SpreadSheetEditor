#ifndef PYSAROLE_CPARSER_H
#define PYSAROLE_CPARSER_H

#include "../CConstants.h"
#include "../CTable.h"
#include <sstream>
#include <cmath>
#include <regex>
#include <string>
#include <stack>
#include <set>

class CParser {
public:
    CParser(CTable* table, std::string& expression);

    virtual ~CParser() = default;

    virtual void process() = 0;
protected:
    std::string m_expression;
    CTable* m_table;
protected:
    struct CValue {
        CValue() = default;

        CValue(std::string inValue, DataType inType)
        : value(inValue), type(inType) { }

        std::string value;
        DataType type;
    };

    struct COperation {
        COperation(std::string inOperation, unsigned inPriority)
        : operation(inOperation), priority(inPriority) { }

        std::string operation;
        unsigned priority;
    };
protected:
    void toUpperCase(std::string& text);

    bool isOperator(char op) const;

    bool isFunction(const std::string& function) const;

    bool isNumeric(const std::string& value) const;

    bool isInteger(const std::string& value) const;

    bool isValidCell(const std::string& cell) const;

    Position getCellPosition(const std::string& link) const;

    unsigned getPriority(const std::string& op) const;

    std::string repeatString(const std::string& text, int n) const;

    bool execOperation(const COperation& op,
                       const CValue& argument1,
                       const CValue& argument2,
                       CValue& resEval) const;


    bool execFunction(const COperation& op, 
                      const CValue& argument1,
                      CValue& resEval) const;
};


#endif //PYSAROLE_CPARSER_H