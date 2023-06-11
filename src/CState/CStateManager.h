#ifndef PYSAROLE_CSTATEMANAGER_H
#define PYSAROLE_CSTATEMANAGER_H

#include "../CConstants.h"
#include "../CTable.h"
#include "../CCell.h"

#include <string>
#include <fstream>

class CStateManager {
public:
    CStateManager(CTable* table, std::string & fileName, std::string & path);

    virtual ~CStateManager() = default;

    virtual bool save() = 0;

    virtual bool load() = 0;
protected:
    std::string m_fileName;
    std::string m_path;
    CTable* m_table;
protected:
    bool validFile() const;
};

#endif //PYSAROLE_CSTATEMANAGER_H