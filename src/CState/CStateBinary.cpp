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
    std::ifstream file(m_path + m_fileName + ".bin", std::ios::binary);

    if (!file.good())
        return false;

    std::string line;

    while (getline(file, line)) {
        if(line.empty())
            break;
        int x, y;
        int valueSize, expressionSize;
        Position position;
        std::string value;
        std::string expression;
        
        size_t spacePos1 = line.find(' ');
        size_t spacePos2 = line.find(' ', spacePos1 + 1);
        size_t spacePos3 = line.find(' ', spacePos2 + 1);
        size_t spacePos4 = line.find(' ', spacePos3 + 1);

        x = stoi(line.substr(0, spacePos1));
        y = stoi(line.substr(spacePos1 + 1, spacePos2 - spacePos1 - 1));
        position = std::make_pair(x, y);
        valueSize = stoi(line.substr(spacePos2 + 1, spacePos3 - spacePos2 - 1));
        expressionSize = stoi(line.substr(spacePos3 + 1, spacePos4 - spacePos3 - 1));
        
        value = line.substr(spacePos4 + 1, valueSize);
        expression = line.substr(spacePos4 + 1 + valueSize + 1, expressionSize);
        
        m_table->addCell(position, expression, value);
    }

    file.close();

    return true;
}