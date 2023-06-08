#ifndef PYSAROLE_CPARSER_H
#define PYSAROLE_CPARSER_H

#include "../CConstants.h"
#include "../CTable.h"
#include "../CCell.h"
#include <ncurses.h> // del
#include <sstream>
#include <cmath>
#include <regex>
#include <string>
#include <stack>

class CParser {
public:
    CParser(CTable* table, std::string expression);

    virtual ~CParser() = default;

    virtual void process() = 0;
protected:
    CTable* m_table;
    std::string m_expression;
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

    bool isNumeric(std::string& value) const;

    bool isInteger(const std::string& value) const;

    bool isValidCell(const std::string& cell) const;

    Position getCellPosition(std::string link) const;

    unsigned getPriority(std::string op) const;

    std::string repeatString(std::string text, int n) const;

    bool execOperation(COperation& op,
                       CValue& argument1,
                       CValue& argument2,
                       CValue& resEval);


    bool execFunction(COperation& op, 
                      CValue& argument1,
                      CValue& resEval);
};


#endif //PYSAROLE_CPARSER_H