#include "CStateBinary.h"

CStateBinary::CStateBinary(CTable* table, std::string & fileName, std::string & path) 
: CStateManager(table, fileName, path) {}

bool CStateBinary::save() {
    std::ofstream file(m_path + m_fileName + ".bin", std::ios::binary | std::ios::trunc);

    if (!file.good())
        return false;

    for (const auto& entry : m_table->getTable()) {
        const CCell* cell = entry.second;
        if (!cell->getErrorStatus() || !cell->getValString().empty()) {
            Position position = cell->getPosition();
            std::string expression = cell->getExpression();

            file << position.first << " " << position.second << " ";
            file << expression << '\n';
        }
    }
    file.close();

    return true;
}

bool CStateBinary::load() {
    std::ifstream file(m_path + m_fileName + ".bin", std::ios::binary);

    if (!file.good())
        return false;

    m_table->reset();
    std::string line;

    while (getline(file, line)) {
        if(line.empty())
            break;
        int x, y;
        Position position;
        std::string expression;
        
        size_t spacePos1 = line.find(' ');
        size_t spacePos2 = line.find(' ', spacePos1 + 1);

        x = stoi(line.substr(0, spacePos1));
        y = stoi(line.substr(spacePos1 + 1, spacePos2 - spacePos1 - 1));
        position = std::make_pair(x, y);
        expression = line.substr(spacePos2 + 1);
        
        m_table->createCell(position);
        m_table->getCell(position)->update(expression);
    }

    file.close();

    return true;
}