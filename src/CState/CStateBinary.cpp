#include "CStateBinary.h"

CStateBinary::CStateBinary(CTable* table, std::string & fileName, std::string & path) 
: CStateManager(table, fileName, path) {}

bool CStateBinary::save() {
    std::ofstream file(m_path + m_fileName + ".bin", std::ios::binary | std::ios::trunc);

    if (!file.good())
        return false;

    for (const auto& entry : m_table->getTable()) {
        const CCell* cell = entry.second;
        if (!cell->getErrorStatus() && !cell->getValString().empty()) {
            Position position = cell->getPosition();
            std::string value = cell->getValString();
            std::string expression = cell->getExpression();

            file << position.first << " " << position.second << " ";
            file << value.length() << " " << expression.length() << " ";
            file << value << " " << expression << '\n';
        }
    }
    file.close();

    return true;
}

bool CStateBinary::load() {
    std::ofstream file(m_fileName, std::ios::binary);

    if (!file.good())
        return false;

    for (const auto& entry : m_table->getTable()) {
        const CCell* cell = entry.second;

        if (!cell->getErrorStatus() && cell->getValString().empty()) {
            Position position = cell->getPosition();
            std::string value = cell->getValString();
            std::string expression = cell->getExpression();

            file << position.first << " " << position.second << " ";
            file << value.length() << " " << expression.length() << " ";
            file << value << " " << expression << '\n';
        }
    }

    file.close();

    return true;
}