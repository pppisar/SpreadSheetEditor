#ifndef PYSAROLE_CSTATETXT_H
#define PYSAROLE_CSTATETXT_H

#include "CStateManager.h"
#include "../CConstants.h"
#include "../CTable.h"
#include "../CCell.h"

class CStateTxt: public CStateManager {
public:
    CStateTxt(CTable* table, std::string & fileName, std::string & path);

    ~CStateTxt() = default;

    bool save() override;

    bool load() override;
};

#endif //PYSAROLE_CSTATEBINARY_H