#ifndef PYSAROLE_CCELL_H
#define PYSAROLE_CCELL_H

#include "CConstants.h"
#include <string>
#include <set>

class CCell {
public:
    CCell(int id,
          std::string & newExpression, std::string & newValue,
          bool isNumeric);

    CCell(const CCell & src);

    virtual ~CCell() = default;

    // Getters
    virtual double getValNumeric() const;

    virtual std::string getValString() const;

    virtual std::string getExpression() const;

    // Setter
    virtual void update(std::string & newExpression, std::string & newValue,
                        bool isNumeric);

private:
    int m_id;
    std::string m_value;
    std::string m_expression;
    bool m_isNumeric;
    std::set<CPosition> m_dependences;
};
#endif //PYSAROLE_CCELL_H