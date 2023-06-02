#ifndef PYSAROLE_CPARSER_H
#define PYSAROLE_CPARSER_H

#include "CConstants.h"
#include "CTable.h"
#include "CCell.h"
#include <ncurses.h> // del
#include <cmath>
#include <string>
#include <stack>
#include <vector>

class CParser {
public:
    CParser(CTable* table);

    ~CParser() = default;

    ParseResult process(std::string expression);
private:
    CTable* m_table;

    void toUpperCase(std::string& text);

    bool isOperator(char op) const;

    bool execOperator(Operator& op,
                      Value& argument1,
                      Value& argument2,
                      Value& resEval);

    bool isFunction(const std::string& function) const;

    bool execFunction(const std::string& function, 
                      const std::string& argument,
                      Value& resVal);

    bool isInteger(const std::string& value) const;

    bool isNumeric(const std::string& value) const;

    bool isValidCell(const std::string& cell) const;

    Position getCellPosition(std::string link) const;

    unsigned getPriority(char op) const;

    Value getValue(std::string value) const;
};


#endif //PYSAROLE_CPARSER_H