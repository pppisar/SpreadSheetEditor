#ifndef PYSAROLE_CSTATEBINARY_H
#define PYSAROLE_CSTATEBINARY_H

#include "CStateManager.h"
#include "../CConstants.h"
#include "../CTable.h"
#include "../CCell.h"

#include <ncurses.h>

class CStateBinary: public CStateManager {
public:
    CStateBinary(CTable* table, std::string & fileName, std::string & path);

    ~CStateBinary() = default;

    bool save() override;

    bool load() override;
};

#endif //PYSAROLE_CSTATEBINARY_H