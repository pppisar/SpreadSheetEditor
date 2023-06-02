#include "CCell.h"

CCell::CCell(int id,
             std::string & expression,
             ParseResult& info) {
    m_id = id;
    m_expression = expression;
    m_value = info.second;
    m_isNumeric = info.first.first;
    m_isError = info.first.second;
}

CCell::CCell(const CCell &src) {
    m_id = src.m_id;
    m_value = src.m_value;
    m_expression = src.m_expression;
    m_isNumeric = src.m_isNumeric;
    m_isError = src.m_isError;
}

std::string CCell::getValString() const {
    return m_value;
}

std::string CCell::getExpression() const {
    return m_expression;
}


void CCell::update(std::string & newExpression, ParseResult& info) {
    m_expression = newExpression;
    m_value = info.second;
    m_isNumeric = info.first.first;
    m_isError = info.first.second;
}