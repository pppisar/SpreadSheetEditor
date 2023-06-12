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

/**
 * A template class that implements methods for processing strings 
 * and performing arithmetic operations and functions for use in inheritance
*/
class CParser {
public:
    /* Constructor */
    CParser(CTable* table, std::string& expression);
    
    /* Destructor */
    virtual ~CParser() = default;

    /* Function template for processing an expression */
    virtual void process() = 0;
protected:
    std::string m_expression;
    CTable* m_table;
protected:
    /**
     * An auxiliary structure that represents a value 
     * of a certain type that was in the expression
    */
    struct CValue {
        /* Default constructor */
        CValue() = default;

        /* Additional constructor */
        CValue(std::string inValue, DataType inType)
        : value(inValue), type(inType) { }

        std::string value;
        DataType type;
    };

    /**
     * An auxiliary structure that represents a specific operand 
     * or function that was found in the expression
    */
    struct COperation {
        /* Constructor */
        COperation(std::string inOperation, unsigned inPriority)
        : operation(inOperation), priority(inPriority) { }

        std::string operation;
        unsigned priority;
    };
protected:
    /**
     * Translation of the text to the upper case
     * @param[in/out] text - The text to be transformed
    */
    void toUpperCase(std::string& text);

    /**
     * Checking if a character is an operator
     * @param[in] op - The character to check
     * @return Returns true if the character is an operator, otherwise false
    */
    const bool isOperator(char op) const;

    /**
     * Checking a string for a match with a function name
     * @param[in] function - The string to check
     * @return Returns true if the specified string is a function, otherwise false
    */
    const bool isFunction(const std::string& function) const;

    /**
     * Checking the contents of a string for whether it can be converted to a number (Integer or Real)
     * @param[in] value - The string to be checked
     * @return Returns true if the string consists of characters that can be converted to a number, otherwise false
    */
    const bool isNumeric(const std::string& value) const;
    
    /**
     * Checking the contents of a string for whether it can be converted to a integer number
     * @param[in] value - The string to be checked
     * @return Returns true if the contents of the string can be converted to an integer, otherwise false
    */
    const bool isInteger(const std::string& value) const;

    /**
     * Checking the correctness of the syntax when referring to a cell
     * @param[in] cell - Cell name
     * @return Returns true if the cell syntax is correct, false otherwise
    */
    const bool isValidCell(const std::string& cell) const;

    /**
     * Convert a cell reference to its position in a table
     * @param[in] link - Cell name
     * @return Returns the position of a cell in the table
    */
    Position getCellPosition(const std::string& link) const;

    /**
     * Determining operand priority
     * @param[in] op - Operand
     * @return Returns the priority of the operand
    */
    unsigned getPriority(const std::string& op) const;

    /**
     * Method for repeating text multiple times
     * @param[in] text - Text that needs to be repeated
     * @param[in] in - How many times to repeat the text
     * @return Returns text that has been duplicated a specified number of times
    */
    std::string repeatString(const std::string& text, int n) const;

    /**
     * A method that calculates an arithmetic operation with two arguments
     * @param[in] op - Operand (arithmetic operation)
     * @param[in] argument1 - The first argument of the operation (on the left side)
     * @param[in] argument2 - The second argument of the operation (on the right side)
     * @param[out] resEval - The resulting value of the operation
     * @return Returns true if the operation was successful, otherwise false
    */
    const bool execOperation(const COperation& op,
                             const CValue& argument1,
                             const CValue& argument2,
                             CValue& resEval) const;

    /**
     * A method that calculates an arithmetic function from a single argument
     * @param[in] op - Operand (arithmetic function)
     * @param[in] argument1 - Function argument
     * @param[out] resEval - The resulting value of the operation
     * @return Returns true if the operation was successful, otherwise false
    */
    const bool execFunction(const COperation& op, 
                            const CValue& argument1,
                            CValue& resEval) const;
};


#endif //PYSAROLE_CPARSER_H