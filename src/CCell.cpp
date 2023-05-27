#include "CCell.h"

CCell::CCell(int id,
             std::string & expression, std::string & value,
             bool isNumeric) {
    m_id = id;
    m_expression = expression;
    m_value = value;
    m_isNumeric = isNumeric;
}

CCell::CCell(const CCell &src) {
    m_id = src.m_id;
    m_value = src.m_value;
    m_expression = src.m_expression;

}


double CCell::getValNumeric() const {
    // TODO: Convert value to double if it is a number.
    if (m_isNumeric)
        return 1.0;
    return 0.0; // throw error
}

std::string CCell::getValString() const {
    return m_value;
}

std::string CCell::getExpression() const {
    return m_expression;
}


void CCell::update(std::string & newExpression, std::string & newValue, bool isNumeric) {
    m_expression = newExpression;
    m_value = newValue;
    m_isNumeric = isNumeric;
}