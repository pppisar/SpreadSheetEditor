#include "CStateManager.h"

CStateManager::CStateManager(CTable* table, std::string & fileName, std::string & path) 
: m_table(table), m_fileName(fileName), m_path(path) { }

bool CStateManager::validFile() const {
    std::ofstream file(m_fileName);
    return file.good();
}