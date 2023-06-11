#include "CStateManager.h"

CStateManager::CStateManager(CTable* table, std::string & fileName, std::string & path) 
: m_fileName(fileName), m_path(path) {
    m_table = table;
}

bool CStateManager::validFile() const {
    std::ofstream file(m_path + m_fileName + ".bin");
    return file.good();
}