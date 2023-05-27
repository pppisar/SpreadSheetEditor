#include "CInterfaceHelp.h"

void CInterfaceHelp::reset() {
    m_selected = 0;
}

void CInterfaceHelp::action(int actKey) {
    switch (actKey) {
        case KEY_LEFT:
            if (m_selected - 1 >= 0)
                m_selected -= 1;
            renderHeader();
            renderBody();
            break;
        case KEY_RIGHT:
            if (m_selected + 1 <= 2)
                m_selected += 1;
            renderHeader();
            renderBody();
            break;
        default:
            break;
    }
}

void CInterfaceHelp::renderHeader() const {
    int startPos = 1;
    for (int i = 0; i < 3; i++) {
        if (i == m_selected)
            wattron(stdscr, A_REVERSE);
        mvprintw(0, startPos, "%s", CHOISE_HELP[i].c_str());
        wattroff(stdscr, A_REVERSE);
        startPos += CHOISE_HELP[i].size() + 2;
    }
}

void CInterfaceHelp::renderBody() const {
    int line = 2, position = 0;
    for (auto ch: TEXT_HELP[m_selected]) {
        mvprintw(line, position, "%c", ch);
        position++;
    }
}

void CInterfaceHelp::renderFooter() const {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    wattron(stdscr, A_REVERSE);
    mvprintw(yMax - 1, xMax - 21, "<-");
    mvprintw(yMax - 1, xMax - 14, "->");
    mvprintw(yMax - 1, 0, "F1");
    mvprintw(yMax - 1, 6, "ESC");
    wattroff(stdscr, A_REVERSE);
    mvprintw(yMax-1, xMax - 18, "and");
    mvprintw(yMax-1, xMax - 11, "CHOOSE PAGE");
    mvprintw(yMax-1, 3, "or");
    mvprintw(yMax-1, 10, "CLOSE");
}

void CInterfaceHelp::display() {
    clear();
    renderHeader();
    renderBody();
    renderFooter();
}

