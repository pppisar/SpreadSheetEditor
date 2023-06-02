#include "CParser.h"

CParser::CParser(CTable* table) {
    m_table = table;
}

ParseResult CParser::process(std::string expression) {
    size_t expLength = expression.length();
    std::stack<Value> values;
    std::stack<Operator> operators;
    std::set<Position> dependences;
    bool prevIsOper = true;
    bool isError = false;
    std::string resValue;

    if (expression.size() > 0 && expression[0] == '=') {
        Value newVal;

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
                        newVal = getValue(expression.substr(expPosStart, expPosEnd - expPosStart));
                        values.push(newVal);
                        expPosStart = expPosEnd - 1;
                        prevIsOper = false;
                    }
                    else {
                        isError = true;
                        resValue = "UnknowVal";
                        break;
                    }
                }
                else {
                    isError = true;
                    resValue = "BadSyntax";
                    break;
                }
            }
            else if (expression[expPosStart] == '"') {
                if (prevIsOper) {
                    size_t expPosEnd = ++expPosStart;
                    for (; expPosEnd < expLength; expPosEnd++)
                        if (expression[expPosEnd] == '"')
                            break;
                    std::string strVal = expression.substr(expPosStart, expPosEnd - expPosStart);
                    if (expPosEnd != expression.size()) {
                        newVal = getValue(strVal);
                        values.push(newVal);
                        expPosStart = expPosEnd + 1;
                        prevIsOper = false;
                    }
                    else {
                        isError = true;
                        resValue = "Expected\"";
                        break;
                    }
                }
                else {
                    isError = true;
                    resValue = "BadSyntax";
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
                        expPosEnd++;
                        std::string func = expression.substr(expPosStart, expPosEnd - expPosStart);
                        toUpperCase(func);
                        if (isFunction(func)) {
                            expPosStart = expPosEnd;
                            for (; expPosEnd < expLength; expPosEnd++)
                                if (expression[expPosEnd] == ')')
                                    break;
                            if (expPosEnd != expLength) {
                                std::string value = expression.substr(expPosStart, expPosEnd - expPosStart);
                                toUpperCase(value);
                                if (isNumeric(value)) {
                                    Value resEval = std::make_pair(false, "");
                                    if (!execFunction(func, value, resEval))
                                        values.push(resEval);
                                    else {
                                        isError = true;
                                        resValue = "BadFunArg";
                                        break;
                                    }
                                }
                                else if (isValidCell(value) && 
                                        isNumeric(m_table->getCell(getCellPosition(value))->getValString())) {
                                            Value resEval = std::make_pair(false, "");
                                            if (!execFunction(func, 
                                                              m_table->getCell(getCellPosition(value))->getValString(),
                                                              resEval))
                                                values.push(resEval);
                                            else {
                                                isError = true;
                                                resValue = "BadFunArg";
                                                break;
                                            }
                                        }
                                else {
                                    isError = true;
                                    resValue = "BadFunArg";
                                    break;
                                }
                                expPosStart = expPosEnd;
                                prevIsOper = false;
                            }
                            else {
                                isError = true;
                                resValue = "BadSyntax";
                                break;
                            }
                        }
                        else {
                            isError = true;
                            resValue = "UnexpFunc";
                            break;
                        }
                    }
                    else {
                        std::string cell = expression.substr(expPosStart, expPosEnd - expPosStart);
                        mvprintw(25,40,"Cell: %s", cell.c_str());
                        toUpperCase(cell);
                        if (isValidCell(cell)) {
                            dependences.insert(getCellPosition(cell));
                            newVal = getValue(m_table->getCell(getCellPosition(cell))->getValString());
                            values.push(newVal);
                            expPosStart = expPosEnd;
                            prevIsOper = false;
                        }
                        else {
                            isError = true;
                            resValue = "UnknowRef";
                            break;
                        }
                    }
                }
                else {
                    isError = true;
                    resValue = "BadSyntax";
                    break;
                }
            }
            else if (expression[expPosStart] == '(') {
                if (prevIsOper)
                    operators.push(std::make_pair(5, '('));
                else {
                    isError = true;
                    resValue = "BadSyntax";
                    break;
                }
            }
            else if (expression[expPosStart] == ')') {
                if (!prevIsOper && !operators.empty()) {
                    while (!operators.empty() && operators.top().second != '(' && values.size() >= 2) {
                        Operator op = operators.top();
                        operators.pop();
                        Value val2 = values.top();
                        values.pop();
                        Value val1 = values.top();
                        values.pop();
                        Value resEval;
                        if (!execOperator(op, val1, val2, resEval))
                            values.push(resEval);
                        else {
                            isError = true;
                            resValue = resEval.second;
                            break;
                        }
                    }
                    if (!isError && (operators.empty() || values.size() < 2)) {
                        isError = true;
                        resValue = "BadSyntax";
                    }
                    if (isError)
                        break;
                    operators.pop();
                }
                else {
                    isError = true;
                    resValue = "BadSyntax";
                    break;
                }
            }
            else if (isOperator(expression[expPosStart])) {
                if (operators.empty() || (operators.top().second == '(' && 
                    (expression[expPosStart] == '+' || expression[expPosStart] == '-'))) {
                        values.push(getValue("0"));
                        operators.push(std::make_pair(4, expression[expPosStart]));
                }
                else if (!prevIsOper) {
                    Operator currentOp = std::make_pair(getPriority(expression[expPosStart]), expression[expPosStart]);
                    
                    while (!operators.empty() && operators.top().first > currentOp.first && values.size() >= 2) {
                        Operator op = operators.top();
                        operators.pop();
                        Value val2 = values.top();
                        values.pop();
                        Value val1 = values.top();
                        values.pop();
                        Value resEval;
                        if (!execOperator(op, val1, val2, resEval))
                            values.push(resEval);
                        else {
                            isError = true;
                            resValue = resEval.second;
                            break;
                        }
                    }
                    if (!isError && (operators.empty() || values.size() < 2)) {
                        isError = true;
                        resValue = "BadSyntax";
                    }
                    if (isError)
                        break;
                    operators.pop();
                }
                else {
                    isError = true;
                    resValue = "BadSyntax";
                    break;
                }
            }
            else {
                isError = true;
                resValue = "BadSyntax";
                break;
            }
        }
    }
    else
        values.push(getValue(expression));

    mvprintw(1,0,"Exp: %s | Val: %s | isError: %d", expression.c_str(), resValue.c_str(), (int)isError);
    return std::make_pair(std::make_pair(values.top().first, isError), values.top().second);
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

bool CParser::execOperator(Operator& op,
                           Value& argument1,
                           Value& argument2,
                           Value& resEval) {
    bool error = false;
    std::string res;
    switch (op.second)
    {
    case '+':
        if (argument1.first && argument2.first)
            res = std::to_string(std::stod(argument1.second) + std::stod(argument2.second));
        else if (!argument1.first && !argument2.first)
            res = argument1.second + argument2.second;
        else {
            error = true;
            res = "BadLogic";
        }
        break;
    case '-':
        if (argument1.first && argument2.first)
            res = std::to_string(std::stod(argument1.second) - std::stod(argument2.second));
        else {
            error = true;
            res = "BadLogic";
        }
        break;
    case '*':
        if (argument1.first && argument2.first)
            res = std::to_string(std::stod(argument1.second) * std::stod(argument2.second));
        else if (!argument1.first && argument2.first && isInteger(argument2.second))
            res = std::string(argument1.second, std::stoi(argument2.second));
        else if (argument1.first && !argument2.first && isInteger(argument1.second))
            res = std::string(argument2.second, std::stoi(argument1.second));
        else {
            error = true;
            res = "BadLogic";
        }
        break;
    case '/':
        if (argument1.first && argument2.first && 
            isInteger(argument2.second) && std::stod(argument2.second) != 0)
                res = std::to_string(std::stoi(argument1.second) - std::stoi(argument2.second));
        else {
            error = true;
            res = "BadLogic";
        }
        break;
    case '^':
        if (argument1.first && argument2.first && 
            isInteger(argument1.second) && std::stoi(argument1.second) == 0 && 
            std::stod(argument2.second) < 0) {
                error = true;
                res = "BadLogic";
        }
        else if (argument1.first && argument2.first)
            res = std::to_string(pow(std::stod(argument1.second), std::stod(argument2.second)));
        else {
            error = true;
            res = "BadLogic";
        }
        break;
    case '%':
        if (argument1.first && argument2.first && 
            isInteger(argument1.second) && isInteger(argument2.second) && 
            std::stoi(argument2.second) != 0)
                res = std::to_string(std::stoi(argument1.second) % std::stoi(argument2.second));
        else {
            error = true;
            res = "BadLogic";
        }
        break;
    default:
        break;
    }
    return error;
}

bool CParser::isFunction(const std::string& function) const {
    return (function == "ABS(" ||
            function == "SIN(" || function == "COS(" ||
            function == "LN(" || function == "EXP(");
}

bool CParser::execFunction(const std::string& function, 
                           const std::string& argument,
                           Value& resEval) {
    bool error = false;
    std::string res;
    if (function == "ABS(")
        res = std::to_string(abs(std::stod(argument)));
    else if (function == "SIN(")
        res = std::to_string(sin(std::stod(argument)));
    else if (function == "COS(")
        res = std::to_string(cos(std::stod(argument)));
    else if (function == "LN(") {
        if (std::stod(argument) > 0)
            res = std::to_string(log(std::stod(argument)));
        else {
            res = "BadFunArg";
            error = true;
        }
    }
    else if (function == "EXP(")
        res = std::to_string(exp(std::stod(argument)));

    resEval.first = isNumeric(res);
    resEval.second = res;
    return error;
}

bool CParser::isInteger(const std::string& value) const {
    bool res = true;
    if (value.size() == 0)
        res = false;
    for (char num: value) {
        res = isdigit(num);
        if (!res)
            break;
    }
    return res;
}

bool CParser::isNumeric(const std::string& value) const {
    try {
        std::stod(value);
        return true;
    } catch (...) {
        return false;
    }
}

bool CParser::isValidCell(const std::string& cell) const {
    if (cell.empty() || !isalpha(cell[0]))
        return false;

    bool hasDigit = false;
    for (char c : cell) {
        if (!isalnum(c) || (hasDigit && isalpha(c)))
            return false;
        if (isdigit(c) && !hasDigit)
            hasDigit = true;
    }

    return hasDigit && m_table->checkCell(getCellPosition(cell));
}

Position CParser::getCellPosition(std::string link) const {
    int y, x;

    int i = 0;
    for (; isalpha(link[i]); i++)
        x = x * 26 + (toupper(link[i]) - 'A' + 1);
    
    y = std::stoi(link.substr(i));
    
    return std::make_pair(x, y);
}

unsigned CParser::getPriority(char op) const {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^' || op == '%')
        return 3;
    return 0;
}

Value CParser::getValue(std::string value) const {
    return std::make_pair(isNumeric(value), value);
}