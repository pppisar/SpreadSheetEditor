#ifndef PYSAROLE_CCELL_H
#define PYSAROLE_CCELL_H

#include <string>

class CCell {
public:
    CCell() = default;

    CCell(const CCell & src);

    virtual ~CCell() = default;

    // Getters
    virtual double getValNumeric() const;

    virtual std::string getValString() const;

    virtual std::string getExpression() const;

    // Setter
    virtual bool update(std::string input);

    // Processing of expression(only text)
    virtual void process();

protected:
    std::string m_value;
    std::string m_expression;
private:

};


#endif //PYSAROLE_CCELL_H