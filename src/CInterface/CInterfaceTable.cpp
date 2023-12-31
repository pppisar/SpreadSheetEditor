#include "CInterfaceTable.h"

CInterfaceTable::CInterfaceTable(CTable *table) {
    m_table = table;
    m_startX = m_startY = m_posY = m_posX = 0;
    m_realX = m_startX + m_posX;
    m_realY = m_startY + m_posY;
}

void CInterfaceTable::reset() {
    m_startX = m_startY = m_posY = m_posX = 0;
    m_realX = m_startX + m_posX;
    m_realY = m_startY + m_posY;
}

void CInterfaceTable::action(int actKey) {
    switch (actKey) {
        case KEY_UP:
            changePosition(0, -1);
            break;
        case KEY_DOWN:
            changePosition(0, 1);
            break;
        case KEY_LEFT:
            changePosition(-1, 0);
            break;
        case KEY_RIGHT:
            changePosition(1, 0);
            break;
        case '\n':
        case KEY_ENTER:
            editCell(3, 12);
            break;
    }
}

void CInterfaceTable::display() {
    updateTerminalSize();
    clear();
    m_tableHeight = m_terminalHeight - HEADER_HEIGHT - FOOTER_HEIGHT;
    m_rowCount = (m_tableHeight - CELL_HEIGHT) / CELL_HEIGHT;
    m_columnCount = (m_terminalWidth - CELL_WIDTH/2) / CELL_WIDTH;
    if (m_startX + m_columnCount > 25)
        m_startX = 25 - m_columnCount + 1;
    if (m_startY + m_rowCount > 99)
        m_startY = 99 - m_rowCount + 1;
    m_posX = m_posY = 0;
    m_realX = m_startX + m_posX;
    m_realY = m_startY + m_posY;
    renderHeader();
    renderBody();
    renderFooter();
}

void CInterfaceTable::renderHeader() const {
    std::string expression = " ";
    std::string value = " ";

    if (m_table->checkCell(std::make_pair(m_realX, m_realY))) {
        CCell* chosenCell = m_table->getCell(std::make_pair(m_realX, m_realY));
        expression = chosenCell->getExpression();
        value = chosenCell->getValString();
    }

    // Clear lines and render new one
    move(0, 0);
    clrtoeol();
    
    mvprintw(0, 0, "Position: (row = %d, column = %s)",
             m_realY, numToAlpha(m_realX).c_str());

    move(2, 0);
    clrtoeol();
    if (value.length() + 7 > MIN_WIDTH)
        mvprintw(2, 0, "Value: %s...", value.substr(0, MIN_WIDTH - 10).c_str());
    else
        mvprintw(2, 0, "Value: %s", value.c_str());

    move(3, 0);
    clrtoeol();
    if (expression.length() + 12 > MIN_WIDTH)
        mvprintw(3, 0, "Expression: %s...", expression.substr(0, MIN_WIDTH - 15).c_str());
    else
        mvprintw(3, 0, "Expression: %s", expression.c_str());

    // Border
    move(4, 0);
    hline(0, m_terminalWidth);
}

void CInterfaceTable::renderBody() const {
    renderGrid();
    renderRCTitle();
    renderCells();
}

void CInterfaceTable::renderFooter() const {
    move(m_terminalHeight-2, 0);
    hline(0, m_terminalWidth);

    move(m_terminalHeight-1, 0);
    clrtoeol();

    std::string fileName;
    if (m_table->isChanged())
        fileName += "*";

    if(m_table->isNamed()) {
        if (m_table->getName().second == FileType::Binary)
            fileName += m_table->getName().first + ".bin";
        else
            fileName += m_table->getName().first + ".txt";
    }

    if (fileName.length() > (MIN_WIDTH - 25))
        mvprintw(m_terminalHeight - 1, 0, "Name: %.17s...", fileName.c_str());
    else
        mvprintw(m_terminalHeight - 1, 0, "Name: %s", fileName.c_str());

    wattron(stdscr, A_REVERSE);
    mvprintw(m_terminalHeight - 1, m_terminalWidth-18, "F1");
    mvprintw(m_terminalHeight - 1, m_terminalWidth-10, "|");
    mvprintw(m_terminalHeight - 1, m_terminalWidth-8, "ESC");
    wattroff(stdscr, A_REVERSE);
    mvprintw(m_terminalHeight-1, m_terminalWidth-15, "HELP");
    mvprintw(m_terminalHeight-1, m_terminalWidth-4, "MENU");
}

void CInterfaceTable::changePosition(int x, int y) {
    if (m_posX + x > m_columnCount - 2)
        m_startX++;
    else if (m_posX + x < 0 && m_startX > 0)
        m_startX--;
    else if (m_posY + y > m_rowCount - 2)
        m_startY++;
    else if (m_posY + y < 0 && m_startY > 0)
        m_startY--;
    else {
        if(m_posX + x >= 0)
            m_posX += x;
        if(m_posY + y >= 0)
            m_posY += y;
    }
    m_realX = m_startX + m_posX;
    m_realY = m_startY + m_posY;
    renderHeader();
    renderGrid();
    renderRCTitle();
    renderCells();
}

void CInterfaceTable::renderGrid() const {
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    for (int i = 0; i < m_rowCount; i++) {
        if (i == m_posY || i == m_posY + 1)
            attron(COLOR_PAIR(1));
        move(TABLE_START_POSITION_Y + i * CELL_HEIGHT, 0);
        hline(0, m_terminalWidth);
        attroff(COLOR_PAIR(1));
    }
    for (int i = 0; i < m_columnCount; i++) {
        if (i == m_posX || i == m_posX + 1)
            attron(COLOR_PAIR(1));
        move(TABLE_START_POSITION_Y - 2, TABLE_START_POSITION_X + i * CELL_WIDTH);
        vline(0, m_tableHeight);
        attroff(COLOR_PAIR(1));
    }
    higlightSelected();
}

void CInterfaceTable::higlightSelected() const {
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    mvaddch(TABLE_START_POSITION_Y + m_posY * CELL_HEIGHT,
            TABLE_START_POSITION_X + m_posX * CELL_WIDTH,
            ACS_ULCORNER);
    mvaddch(TABLE_START_POSITION_Y + (m_posY + 1) * CELL_HEIGHT,
            TABLE_START_POSITION_X + m_posX * CELL_WIDTH,
            ACS_LLCORNER);
    mvaddch(TABLE_START_POSITION_Y + m_posY * CELL_HEIGHT,
            TABLE_START_POSITION_X + (m_posX + 1) * CELL_WIDTH,
            ACS_URCORNER);
    mvaddch(TABLE_START_POSITION_Y + (m_posY + 1) * CELL_HEIGHT,
            TABLE_START_POSITION_X + (m_posX + 1) * CELL_WIDTH,
            ACS_LRCORNER);
    move(TABLE_START_POSITION_Y + m_posY * CELL_HEIGHT + 1,
        TABLE_START_POSITION_X + m_posX * CELL_WIDTH);
    vline(0, CELL_HEIGHT - 1);
    move(TABLE_START_POSITION_Y + m_posY * CELL_HEIGHT + 1,
        TABLE_START_POSITION_X + (m_posX + 1) * CELL_WIDTH);
    vline(0, CELL_HEIGHT - 1);
    move(TABLE_START_POSITION_Y + m_posY * CELL_HEIGHT,
        TABLE_START_POSITION_X + m_posX * CELL_WIDTH + 1);
    hline(0, CELL_WIDTH - 1);
    move(TABLE_START_POSITION_Y + (m_posY + 1) * CELL_HEIGHT,
        TABLE_START_POSITION_X + m_posX * CELL_WIDTH + 1);
    hline(0, CELL_WIDTH - 1);
    attroff(COLOR_PAIR(2));
}

void CInterfaceTable::renderRCTitle() const {
    int maxNumY = m_startY + m_rowCount;
    int posY = TABLE_START_POSITION_Y + 1;
    move(TABLE_START_POSITION_Y, TABLE_START_POSITION_X - 1);
    vline(0, m_tableHeight - CELL_HEIGHT);
    for (int i = m_startY; i < maxNumY; i++) {
        mvprintw(posY, 0, "%3d", i);
        posY += CELL_HEIGHT;
    }

    int maxNumX = m_startX + m_columnCount;
    int posX = TABLE_START_POSITION_X + 4;
    move(TABLE_START_POSITION_Y - 1, TABLE_START_POSITION_X);
    hline(0, m_terminalWidth - TABLE_START_POSITION_X);
    for (int i = m_startX; i < maxNumX; i++) {
        mvprintw(TABLE_START_POSITION_Y - 2, posX, "%6s", numToAlpha(i).c_str());
        posX += CELL_WIDTH;
    }
}

void CInterfaceTable::renderCells() const {
    for (int column = 0; column < m_columnCount; column++) {
        for (int row = 0; row < m_rowCount; row++) {
            if (m_table->checkCell(std::make_pair(column + m_startX, row + m_startY))) {
                std::string value = m_table->getCell(std::make_pair(column + m_startX, row + m_startY))->getValString();
                if (value.size() > 9) {
                    mvprintw(TABLE_START_POSITION_Y + 1 + row * CELL_HEIGHT,
                             TABLE_START_POSITION_X + 1 + column * CELL_WIDTH,
                             "%s", std::string(9, ' ').c_str());
                    mvprintw(TABLE_START_POSITION_Y + 1 + row * CELL_HEIGHT,
                             TABLE_START_POSITION_X + 1 + column * CELL_WIDTH,
                             "%.6s...", value.c_str());
                }
                else {
                    mvprintw(TABLE_START_POSITION_Y + 1 + row * CELL_HEIGHT,
                             TABLE_START_POSITION_X + 1 + column * CELL_WIDTH,
                             "%s", std::string(9, ' ').c_str());
                    mvprintw(TABLE_START_POSITION_Y + 1 + row * CELL_HEIGHT,
                             TABLE_START_POSITION_X + 1 + column * CELL_WIDTH,
                             "%.9s", value.c_str());
                }
            }
            else
                mvprintw(TABLE_START_POSITION_Y + 1 + row * CELL_HEIGHT,
                         TABLE_START_POSITION_X + 1 + column * CELL_WIDTH,
                         "%s", std::string(9, ' ').c_str());
        }
    }
}

void CInterfaceTable::editCell(unsigned startY, unsigned startX) {
    std::string buffer;

    if (m_table->checkCell(std::make_pair(m_realX, m_realY)))
        buffer = m_table->getCell(std::make_pair(m_realX, m_realY))->getExpression();
    
    buffer = readInputString(startY, startX, buffer);

    m_table->createCell(std::make_pair(m_realX, m_realY));
    m_table->getCell(std::make_pair(m_realX, m_realY))->update(buffer);

    renderHeader();
    renderCells();
    renderFooter();
}

std::string CInterfaceTable::numToAlpha(int num) const {
    std::string res;

    while (num >= 0) {
        res.insert(0, 1, ('A' + num % 26));
        num = (num / 26) - 1;
    }

    return res;
}