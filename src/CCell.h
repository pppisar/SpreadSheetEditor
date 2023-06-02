#ifndef PYSAROLE_CCELL_H
#define PYSAROLE_CCELL_H

#include "CConstants.h"
#include <string>
#include <set>

class CCell {
public:
    CCell(int id,
          std::string & expression, 
          ParseResult& info);

    CCell(const CCell & src);

    virtual ~CCell() = default;

    // Getters

    virtual std::string getValString() const;

    virtual std::string getExpression() const;

    // Setter
    virtual void update(std::string & newExpression, ParseResult& info);

private:
    int m_id;
    std::string m_value;
    std::string m_expression;
    bool m_isNumeric;
    bool m_isError;
    std::set<Position> m_dependences;
};
#endif //PYSAROLE_CCELL_H