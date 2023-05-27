#include "CCell.h"


CCell::CCell(const CCell &src) {
    m_value = src.m_value;
    m_expression = src.m_expression;
}


double CCell::getValNumeric() const {
    // TODO: Convert value to double if it is a number.
}

std::string CCell::getValString() const {
    return m_value;
}

std::string CCell::getExpression() const {
    return m_expression;
}


bool CCell::update(std::string input) {
    // TODO: Update the expression and check the syntax and possible loops
}

void CCell::process() {
    // TODO: Calculate the expression(Text)
}