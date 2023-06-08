#include "CParserExpression.h"

CParserExpression::CParserExpression(CTable* table, std::string expression)
: CParser(table, expression) {}

void CParserExpression::process() {
    m_error = false;
    m_dependences.clear();

    size_t expLength = m_expression.length();
    std::stack<CValue> values;
    std::stack<COperation> operations;
    bool prevIsOper = true;

    if (m_expression.size() > 0 && m_expression[0] == '=') {
        for (size_t expPosStart = 1; expPosStart < expLength; expPosStart++) {
            if (isspace(m_expression[expPosStart]))
                continue;
            else if (isdigit(m_expression[expPosStart])) {
                if (prevIsOper) {
                    size_t expPosEnd = expPosStart;
                    for (; expPosEnd < expLength; expPosEnd++)
                        if (!isdigit(m_expression[expPosEnd]) && m_expression[expPosEnd] != '.')
                            break;
                    std::string value = m_expression.substr(expPosStart, expPosEnd - expPosStart);
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
                        m_error = true;
                        m_resValue = "BadSynt01";
                        break;
                    }
                }
                else {
                    m_error = true;
                    m_resValue = "BadSynt02";
                    break;
                }
            }
            else if (m_expression[expPosStart] == '"') {
                if (prevIsOper) {
                    size_t expPosEnd = ++expPosStart;
                    for (; expPosEnd < expLength; expPosEnd++)
                        if (m_expression[expPosEnd] == '"')
                            break;
                    std::string value = m_expression.substr(expPosStart, expPosEnd - expPosStart);
                    if (expPosEnd != m_expression.size()) {
                        values.push(CValue(value, DataType::String));
                        expPosStart = expPosEnd;
                        prevIsOper = false;
                    }
                    else {
                        m_error = true;
                        m_resValue = "Expected\"";
                        break;
                    }
                }
                else {
                    m_error = true;
                    m_resValue = "BadSynt03";
                    break;
                }
            }
            else if (isalpha(m_expression[expPosStart])) {
                if (prevIsOper) {
                    size_t expPosEnd = expPosStart;
                    for (; expPosEnd < expLength; expPosEnd++)
                        if (!isalnum(m_expression[expPosEnd]))
                            break;
                    if (expPosEnd != expLength && m_expression[expPosEnd] == '(') {
                        std::string func = m_expression.substr(expPosStart, expPosEnd - expPosStart);
                        toUpperCase(func);
                        if (isFunction(func)) {
                            operations.push(COperation(func, 0));
                            prevIsOper = true;
                            expPosStart = expPosEnd;
                        }
                        else {
                            m_error = true;
                            m_resValue = "BadSynt04";
                            break;
                        }
                    }
                    else {
                        std::string value = m_expression.substr(expPosStart, expPosEnd - expPosStart);
                        mvprintw(25,40,"Cell: %s", value.c_str());
                        toUpperCase(value);
                        if (isValidCell(value)) {
                            Position cellPosition = getCellPosition(value);
                            if (m_table->checkCell(cellPosition) && !m_table->getCell(cellPosition)->getErrorStatus()) {
                                m_dependences.insert(cellPosition);
                                std::string cellValue = m_table->getCell(cellPosition)->getValString();
                                DataType cellDataType = m_table->getCell(cellPosition)->getValType();
                                values.push(CValue(cellValue, cellDataType));
                                expPosStart = expPosEnd;
                                prevIsOper = false;
                            }
                            else {
                                m_error = true;
                                m_resValue = "BadLogic";
                                break;
                            }
                        }
                        else {
                            m_error = true;
                            m_resValue = "BadSynt05";
                            break;
                        }
                    }
                }
                else {
                    m_error = true;
                    m_resValue = "BadSynt06";
                    break;
                }
            }
            else if (m_expression[expPosStart] == '(') {
                if (prevIsOper)
                    operations.push(COperation("(", 0));
                else {
                    m_error = true;
                    m_resValue = "BadSynt07";
                    break;
                }
            }
            else if (m_expression[expPosStart] == ')') {
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
                            m_error = true;
                            m_resValue = resEval.value;
                            break;
                        }
                    }
                    if (m_error)
                        break;
                    if (operations.empty()) {
                        m_error = true;
                        m_resValue = "BadSynt08";
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
                            m_error = true;
                            m_resValue = resEval.value;
                            break;
                        }
                    }
                    operations.pop();
                }
                else {
                    m_error = true;
                    m_resValue = "BadSynt09";
                    break;
                }
            }
            else if (isOperator(m_expression[expPosStart])) {
                if (((values.empty() && operations.empty()) || 
                (prevIsOper && !operations.empty() && 
                (operations.top().operation == "(" || isFunction(operations.top().operation)))) &&
                (m_expression[expPosStart] == '+' || m_expression[expPosStart] == '-')) {
                    values.push(CValue("0", DataType::Integer));
                    operations.push(COperation(std::string(1, m_expression[expPosStart]), 4));
                }
                else if (!prevIsOper) {
                    COperation currentOp(std::string(1, m_expression[expPosStart]),
                                         getPriority(std::string(1, m_expression[expPosStart])));
                    
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
                            m_error = true;
                            m_resValue = resEval.value;
                            break;
                        }
                    }
                    if (m_error)
                        break;
                    operations.push(currentOp);
                    prevIsOper = true;
                }
                else {
                    m_error = true;
                    m_resValue = "BadSynt10";
                    break;
                }
            }
            else {
                m_error = true;
                m_resValue = "BadSynt11";
                break;
            }
        }
    }
    else {
        if (isNumeric(m_expression)) {
            if (isInteger(m_expression))
                m_resDataType = DataType::Integer;
            else
                m_resDataType = DataType::Double;
        }
        values.push(CValue(m_expression, m_resDataType));
    }
    if(!m_error) {
        while(!operations.empty() && operations.top().operation != "(" && !isFunction(operations.top().operation)) {
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
                m_error = true;
                m_resValue = resEval.value;
                break;
            }
        }
        if (operations.empty() && !m_error) {
            m_resValue =  values.top().value;
            m_resDataType = values.top().type;
        }
        else if (!operations.empty() && !m_error) {
            m_error = true;
            m_resValue = "BadSynt12";
        }
    }
    
    mvprintw(1,0,"Exp: %s | Val: %s | ism_error: %d", m_expression.c_str(), m_resValue.c_str(), (int)m_error);
}

bool CParserExpression::haveError() const {
    return m_error;
}

std::string CParserExpression::getResValue() const {
    return m_resValue;
}

DataType CParserExpression::getDataType() const {
    return m_resDataType;
}

std::set<Position> CParserExpression::getDependences() const {
    return m_dependences;
}