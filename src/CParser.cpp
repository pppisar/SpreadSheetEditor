#include "CParser.h"

CParser::CParser(CTable* table) {
    m_table = table;
}

void CParser::process(std::string expression, CCell & cell) {
    size_t expLength = expression.length();
    std::stack<CValue> values;
    std::stack<COperation> operations;
    bool prevIsOper = true;


    bool error = false;
    std::string resValue;
    DataType resDataType = DataType::String;
    std::set<Position> dependences;

    if (expression.size() > 0 && expression[0] == '=') {
        for (size_t expPosStart = 1; expPosStart < expLength; expPosStart++) {
            if (isspace(expression[expPosStart]))
                continue;
            else if (isdigit(expression[expPosStart])) {
                if (prevIsOper) {
                    size_t expPosEnd = expPosStart;
                    for (; expPosEnd < expLength; expPosEnd++)
                        if (!isdigit(expression[expPosEnd]) && expression[expPosEnd] != '.')
                            break;
                    std::string value = expression.substr(expPosStart, expPosEnd - expPosStart);
                    mvprintw(25,20,"Int val: %s", value.c_str());
                    if (isNumeric(value)) {
                        if (isInteger(value))
                            values.push(CValue(value, DataType::Integer));
                        else
                            values.push(CValue(value, DataType::Double));
                        expPosStart = expPosEnd - 1;
                        prevIsOper = false;
                    }
                    else {
                        error = true;
                        resValue = "BadSynt01";
                        break;
                    }
                }
                else {
                    error = true;
                    resValue = "BadSynt02";
                    break;
                }
            }
            else if (expression[expPosStart] == '"') {
                if (prevIsOper) {
                    size_t expPosEnd = ++expPosStart;
                    for (; expPosEnd < expLength; expPosEnd++)
                        if (expression[expPosEnd] == '"')
                            break;
                    std::string value = expression.substr(expPosStart, expPosEnd - expPosStart);
                    if (expPosEnd != expression.size()) {
                        values.push(CValue(value, DataType::String));
                        expPosStart = expPosEnd;
                        prevIsOper = false;
                    }
                    else {
                        error = true;
                        resValue = "Expected\"";
                        break;
                    }
                }
                else {
                    error = true;
                    resValue = "BadSynt03";
                    break;
                }
            }
            else if (isalpha(expression[expPosStart])) {
                if (prevIsOper) {
                    size_t expPosEnd = expPosStart;
                    for (; expPosEnd < expLength; expPosEnd++)
                        if (!isalnum(expression[expPosEnd]))
                            break;
                    if (expPosEnd != expLength && expression[expPosEnd] == '(') {
                        std::string func = expression.substr(expPosStart, expPosEnd - expPosStart);
                        toUpperCase(func);
                        if (isFunction(func)) {
                            operations.push(COperation(func, 0));
                            prevIsOper = true;
                            expPosStart = expPosEnd;
                        }
                        else {
                            error = true;
                            resValue = "BadSynt04";
                            break;
                        }
                    }
                    else {
                        std::string value = expression.substr(expPosStart, expPosEnd - expPosStart);
                        mvprintw(25,40,"Cell: %s", value.c_str());
                        toUpperCase(value);
                        if (isValidCell(value)) {
                            Position cellPosition = getCellPosition(value);
                            if (m_table->checkCell(cellPosition) && !m_table->getCell(cellPosition)->getErrorStatus()) {
                                m_table->getCell(cellPosition)->addDependence(cellPosition); // ----------------------
                                std::string cellValue = m_table->getCell(cellPosition)->getValString();
                                DataType cellDataType = m_table->getCell(cellPosition)->getValType();
                                values.push(CValue(cellValue, cellDataType));
                                expPosStart = expPosEnd;
                                prevIsOper = false;
                            }
                            else {
                                error = true;
                                resValue = "BadLogic";
                                break;
                            }
                        }
                        else {
                            error = true;
                            resValue = "BadSynt05";
                            break;
                        }
                    }
                }
                else {
                    error = true;
                    resValue = "BadSynt06";
                    break;
                }
            }
            else if (expression[expPosStart] == '(') {
                if (prevIsOper)
                    operations.push(COperation("(", 0));
                else {
                    error = true;
                    resValue = "BadSynt07";
                    break;
                }
            }
            else if (expression[expPosStart] == ')') {
                if (!prevIsOper && !operations.empty()) {
                    while (!operations.empty() && 
                    (operations.top().operation != "(" && !isFunction(operations.top().operation))) {
                        COperation op = operations.top();
                        operations.pop();
                        CValue val2 = values.top();
                        values.pop();
                        CValue val1 = values.top();
                        values.pop();
                        CValue resEval;
                        if (!execOperation(op, val1, val2, resEval))
                            values.push(resEval);
                        else {
                            error = true;
                            resValue = resEval.value;
                            break;
                        }
                    }
                    if (error)
                        break;
                    if (operations.empty()) {
                        error = true;
                        resValue = "BadSynt08";
                        break;
                    }
                    if (isFunction(operations.top().operation)) {
                        COperation op = operations.top();
                        CValue val1 = values.top();
                        values.pop();
                        CValue resEval;
                        if (!execFunction(op, val1, resEval))
                            values.push(resEval);
                        else {
                            error = true;
                            resValue = resEval.value;
                            break;
                        }
                    }
                    operations.pop();
                }
                else {
                    error = true;
                    resValue = "BadSynt09";
                    break;
                }
            }
            else if (isOperator(expression[expPosStart])) {
                if (((values.empty() && operations.empty()) || 
                (prevIsOper && !operations.empty() && 
                (operations.top().operation == "(" || isFunction(operations.top().operation)))) &&
                (expression[expPosStart] == '+' || expression[expPosStart] == '-')) {
                    values.push(CValue("0", DataType::Integer));
                    operations.push(COperation(std::string(1, expression[expPosStart]), 4));
                }
                else if (!prevIsOper) {
                    COperation currentOp(std::string(1, expression[expPosStart]),
                                         getPriority(std::string(1, expression[expPosStart])));
                    
                    while (!operations.empty() && operations.top().priority >= currentOp.priority) {
                        COperation op = operations.top();
                        operations.pop();
                        CValue val2 = values.top();
                        values.pop();
                        CValue val1 = values.top();
                        values.pop();
                        CValue resEval;
                        if (!execOperation(op, val1, val2, resEval))
                            values.push(resEval);
                        else {
                            error = true;
                            resValue = resEval.value;
                            break;
                        }
                    }
                    if (error)
                        break;
                    operations.push(currentOp);
                    prevIsOper = true;
                }
                else {
                    error = true;
                    resValue = "BadSynt10";
                    break;
                }
            }
            else {
                error = true;
                resValue = "BadSynt11";
                break;
            }
        }
    }
    else
        values.push(CValue(expression, resDataType));
    
    if(!error) {
        resValue =  values.top().value;
        resDataType = values.top().type;
    }

    cell.update(error, expression, resValue, resDataType, dependences);
    
    mvprintw(1,0,"Exp: %s | Val: %s | isError: %d", expression.c_str(), resValue.c_str(), (int)error);
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
    return (funcName == "ABS" ||
            funcName == "SIN" || funcName == "COS" ||
            funcName == "LN" || funcName == "EXP");
}

bool CParser::isNumeric(std::string & value) const {
    std::istringstream iss(value);
    double numVal;
    iss >> std::noskipws >> numVal;
    return iss.eof() && !iss.fail();
}

bool CParser::isInteger(const std::string& value) const {
    if (value.length() == 0)
        return false;
    if (std::stod(value) - std::stoi(value) > 1e-6)
        return false;
    return true;
}

bool CParser::isValidCell(const std::string& cell) const {
    std::regex pattern("[A-Z]+[0-9]+");
    return std::regex_match(cell, pattern);
}

Position CParser::getCellPosition(std::string link) const {
    int y, x;

    int i = 0;
    for (; isalpha(link[i]); i++)
        x = x * 26 + (toupper(link[i]) - 'A' + 1);
    
    y = std::stoi(link.substr(i));
    
    return std::make_pair(x, y);
}

unsigned CParser::getPriority(std::string op) const {
    if (op == "+" || op == "-")
        return 1;
    else if (op == "*" || op == "/")
        return 2;
    else if (op == "^" || op == "%")
        return 3;
    else
        return 0;
}

std::string CParser::repeatString(std::string text, int n) const {
    std::string resText;
    for (int i = 0; i < n; i++)
        resText += text;
    return resText;
}

bool CParser::execOperation(COperation& op,
                            CValue& argument1,
                            CValue& argument2,
                            CValue& resEval) {
    bool error = false;
    DataType resType = DataType::String;
    mvprintw(25,20,"Int val: %s %s %s", argument1.value.c_str(), op.operation.c_str(), argument2.value.c_str());
    std::string resValue;
    if (op.operation == "+") {
        if (argument1.type != DataType::String && argument2.type != DataType::String) {
            resValue = std::to_string(std::stod(argument1.value) + std::stod(argument2.value));
            if (isInteger(resValue)) {
                resType = DataType::Integer;
                resValue = std::to_string(std::stoi(resValue));
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
            resValue = std::to_string(std::stod(argument1.value) - std::stod(argument2.value));
            if (isInteger(resValue)) {
                resType = DataType::Integer;
                resValue = std::to_string(std::stoi(resValue));
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
            resValue = std::to_string(std::stod(argument1.value) * std::stod(argument2.value));
            if (isInteger(resValue)) {
                resType = DataType::Integer;
                resValue = std::to_string(std::stoi(resValue));
            }
            else
                resType = DataType::Double;
        }
        else if (argument1.type == DataType::String && argument2.type == DataType::Integer)
            resValue = repeatString(argument1.value, std::stoi(argument2.value));
        else if (argument1.type == DataType::Integer && argument2.type == DataType::String)
            resValue = repeatString(argument2.value, std::stoi(argument1.value));
        else {
            error = true;
            resValue = "BadLogic";
        }
    }
    else if (op.operation == "/") {
        if (argument1.type != DataType::String && argument2.type != DataType::String) {
            if (argument2.type == DataType::Integer && stoi(argument2.value) == 0) {
                error = true;
                resValue = "BadLogic";
            }
            else {
                resValue = std::to_string(std::stoi(argument1.value) / std::stoi(argument2.value));
                if (isInteger(resValue)) {
                    resType = DataType::Integer;
                    resValue = std::to_string(std::stoi(resValue));
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
        if (argument1.type == DataType::Integer && stoi(argument1.value) == 0 && 
            argument2.type != DataType::String && stod(argument2.value) <= 0) {
                error = true;
                resValue = "BadLogic";
        }
        else if (argument1.type != DataType::String && argument2.type != DataType::String) {
            resValue = std::to_string(pow(std::stod(argument1.value), std::stod(argument2.value)));
            if (isInteger(resValue)) {
                resType = DataType::Integer;
                resValue = std::to_string(std::stoi(resValue));
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
            resValue = std::to_string(std::stoi(argument1.value) % std::stoi(argument2.value));
            resType = DataType::Integer;
        }
        else {
            error = true;
            resValue = "BadLogic";
        }
    }
    resEval.value = resValue;
    resEval.type = resType;
    return error;
}

bool CParser::execFunction(COperation& op, 
                           CValue& argument,
                           CValue& resEval) {
    bool error = false;
    std::string resValue;
    DataType resType = argument.type;
    if (argument.type != DataType::String) {
        if (op.operation == "ABS")
            resValue = std::to_string(abs(std::stod(argument.value)));
        else if (op.operation == "SIN") {
            resValue = std::to_string(sin(std::stod(argument.value)));
            if (isInteger(resValue)) {
                resType = DataType::Integer;
                resValue = std::to_string(std::stoi(resValue));
            }
            else
                resType = DataType::Double;
        }
        else if (op.operation == "COS") {
            resValue = std::to_string(cos(std::stod(argument.value)));
            if (isInteger(resValue)) {
                resType = DataType::Integer;
                resValue = std::to_string(std::stoi(resValue));
            }
            else
                resType = DataType::Double;
        }
        else if (op.operation == "LN") {
            if (std::stod(argument.value) > 0) {
                resValue = std::to_string(log(std::stod(argument.value)));
                if (isInteger(resValue)) {
                resType = DataType::Integer;
                resValue = std::to_string(std::stoi(resValue));
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
            resValue = std::to_string(exp(std::stod(argument.value)));
            if (isInteger(resValue)) {
                resType = DataType::Integer;
                resValue = std::to_string(std::stoi(resValue));
            }
            else
                resType = DataType::Double;
        }
    }
    else {
        error = true;
        resValue = "BadOpArgs";
    }
    resEval.value = resValue;
    resEval.type = resType;
    return error;
}