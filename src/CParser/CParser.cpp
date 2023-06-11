#include "CParser.h"

CParser::CParser(CTable* table, std::string& expression) {
    m_expression = expression;
    m_table = table;
}

void CParser::toUpperCase(std::string& text) {
    for (unsigned i = 0; i < text.size(); i++)
        text[i] = toupper(text[i]);
}

bool CParser::isOperator(char op) const {
    return (op == '+' || op == '-' || 
            op == '*' || op == '/' ||  
            op == '^'||  op == '%');
}

bool CParser::isFunction(const std::string& funcName) const {
    return (funcName == "ABS" || funcName == "SQRT" ||
            funcName == "SIN" || funcName == "COS" ||
            funcName == "LN" || funcName == "EXP");
}

bool CParser::isNumeric(const std::string & value) const {
    std::istringstream iss(value);
    double numVal;
    iss >> std::noskipws >> numVal;
    return iss.eof() && !iss.fail();
}

bool CParser::isInteger(const std::string& value) const {
    if (value.length() == 0)
        return false;
    if (std::abs(std::stold(value) - std::stoll(value)) > 1e-9)
        return false;
    return true;
}

bool CParser::isValidCell(const std::string& cell) const {
    std::regex pattern("[A-Z]+[0-9]+");
    return std::regex_match(cell, pattern);
}

Position CParser::getCellPosition(const std::string& link) const {
    int y = 0, x = 0;

    int i = 0;
    for (; isalpha(link[i]); i++)
        x = x * 26 + (toupper(link[i]) - 'A' + 1);
    
    y = std::stoll(link.substr(i));
    
    return std::make_pair(x - 1, y);
}

unsigned CParser::getPriority(const std::string& op) const {
    if (op == "+" || op == "-")
        return 1;
    else if (op == "*" || op == "/")
        return 2;
    else if (op == "^" || op == "%")
        return 3;
    else
        return 0;
}

std::string CParser::repeatString(const std::string& text, int n) const {
    std::string resText;
    for (int i = 0; i < n; i++)
        resText += text;
    return resText;
}

bool CParser::execOperation(const COperation& op,
                            const CValue& argument1,
                            const CValue& argument2,
                            CValue& resEval) const {
    bool error = false;
    DataType resType = DataType::String;
    std::string resValue;
    try {
        if (op.operation == "+") {
            if (argument1.type != DataType::String && argument2.type != DataType::String) {
                resValue = std::to_string(std::stold(argument1.value) + std::stold(argument2.value));
                if (isInteger(resValue)) {
                    resType = DataType::Integer;
                    resValue = std::to_string(std::stoll(resValue));
                }
                else
                    resType = DataType::Double;
            }
            else if (argument1.type == argument2.type && argument1.type == DataType::String)
                resValue = argument1.value + argument2.value;
            else {
                error = true;
                resValue = "BadOpArgs";
            }
        }
        else if (op.operation == "-") {
            if (argument1.type != DataType::String && argument2.type != DataType::String) {
                resValue = std::to_string(std::stold(argument1.value) - std::stold(argument2.value));
                if (isInteger(resValue)) {
                    resType = DataType::Integer;
                    resValue = std::to_string(std::stoll(resValue));
                }
                else
                    resType = DataType::Double;
            }
            else {
                error = true;
                resValue = "BadLogic";
            }
        }
        else if (op.operation == "*") {
            if (argument1.type != DataType::String && argument2.type != DataType::String) {
                resValue = std::to_string(std::stold(argument1.value) * std::stold(argument2.value));
                if (isInteger(resValue)) {
                    resType = DataType::Integer;
                    resValue = std::to_string(std::stoll(resValue));
                }
                else
                    resType = DataType::Double;
            }
            else if (argument1.type == DataType::String && argument2.type == DataType::Integer)
                resValue = repeatString(argument1.value, std::stoll(argument2.value));
            else if (argument1.type == DataType::Integer && argument2.type == DataType::String)
                resValue = repeatString(argument2.value, std::stoll(argument1.value));
            else {
                error = true;
                resValue = "BadLogic";
            }
        }
        else if (op.operation == "/") {
            if (argument1.type != DataType::String && argument2.type != DataType::String) {
                if (argument2.type == DataType::Integer && stoll(argument2.value) == 0) {
                    error = true;
                    resValue = "BadLogic";
                }
                else {
                    resValue = std::to_string(std::stoll(argument1.value) / std::stoll(argument2.value));
                    if (isInteger(resValue)) {
                        resType = DataType::Integer;
                        resValue = std::to_string(std::stoll(resValue));
                    }
                    else
                        resType = DataType::Double;
                }
            }
            else {
                error = true;
                resValue = "BadLogic";
            }
        }
        else if (op.operation == "^") {
            if (argument1.type == DataType::Integer && stoll(argument1.value) == 0 && 
                argument2.type != DataType::String && stold(argument2.value) <= 0) {
                    error = true;
                    resValue = "BadLogic";
            }
            else if (argument1.type != DataType::String && argument2.type != DataType::String) {
                resValue = std::to_string(pow(std::stold(argument1.value), std::stold(argument2.value)));
                if (isInteger(resValue)) {
                    resType = DataType::Integer;
                    resValue = std::to_string(std::stoll(resValue));
                }
                else
                    resType = DataType::Double;
            }
            else {
                error = true;
                resValue = "BadLogic";
            }
        }
        else if (op.operation == "%") {
            if (argument1.type == argument2.type && argument1.type == DataType::Integer) {
                resValue = std::to_string(std::stoll(argument1.value) % std::stoll(argument2.value));
                resType = DataType::Integer;
            }
            else {
                error = true;
                resValue = "BadLogic";
            }
        }
    } catch(...) {
        error = true;
        resValue = "BigNumRes";
    }
    
    resEval.value = resValue;
    resEval.type = resType;
    return error;
}

bool CParser::execFunction(const COperation& op, 
                           const CValue& argument,
                           CValue& resEval) const {
    bool error = false;
    std::string resValue;
    DataType resType = argument.type;
    try {
        if (argument.type != DataType::String) {
            if (op.operation == "ABS")
                resValue = std::to_string(std::abs(std::stold(argument.value)));
            else if (op.operation == "SQRT") {
                if (std::stold(argument.value) >= 0) {
                    resValue = std::to_string(std::sqrt(std::stold(argument.value)));
                    if (isInteger(resValue)) {
                        resType = DataType::Integer;
                        resValue = std::to_string(std::stoll(resValue));
                    }
                    else
                        resType = DataType::Double;
                }
                else {
                    resValue = "BadOpArgs";
                    error = true;
                }
            }
            else if (op.operation == "SIN") {
                resValue = std::to_string(std::sin(std::stold(argument.value)));
                if (isInteger(resValue)) {
                    resType = DataType::Integer;
                    resValue = std::to_string(std::stoll(resValue));
                }
                else
                    resType = DataType::Double;
            }
            else if (op.operation == "COS") {
                resValue = std::to_string(std::cos(std::stold(argument.value)));
                if (isInteger(resValue)) {
                    resType = DataType::Integer;
                    resValue = std::to_string(std::stoll(resValue));
                }
                else
                    resType = DataType::Double;
            }
            else if (op.operation == "LN") {
                if (std::stold(argument.value) > 0) {
                    resValue = std::to_string(std::log(std::stold(argument.value)));
                        if (isInteger(resValue)) {
                        resType = DataType::Integer;
                        resValue = std::to_string(std::stoll(resValue));
                    }
                    else
                        resType = DataType::Double;
                }
                else {
                    resValue = "BadOpArgs";
                    error = true;
                }
            }
            else if (op.operation == "EXP") {
                resValue = std::to_string(std::exp(std::stold(argument.value)));
                if (isInteger(resValue)) {
                    resType = DataType::Integer;
                    resValue = std::to_string(std::stoll(resValue));
                }
                else
                    resType = DataType::Double;
            }
        }
        else {
            error = true;
            resValue = "BadOpArgs";
        }
    } catch(...) {
        error = true;
        resValue = "BigNumRes";
    }
    resEval.value = resValue;
    resEval.type = resType;
    return error;
}