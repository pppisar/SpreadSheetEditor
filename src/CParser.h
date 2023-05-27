#ifndef PYSAROLE_CPARSER_H
#define PYSAROLE_CPARSER_H

#include <string>

class CParser {
public:
    CParser(const std::string & expression);

    bool process();
private:
    std::string m_expression;

    // TODO: functions and math constants
};


#endif //PYSAROLE_CPARSER_H