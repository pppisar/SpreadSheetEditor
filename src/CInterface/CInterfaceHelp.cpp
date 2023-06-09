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
    int terminalHeigth, terminalWidth;
    getmaxyx(stdscr, terminalHeigth, terminalWidth);
    wattron(stdscr, A_REVERSE);
    mvprintw(terminalHeigth - 1, 0, "<-");
    mvprintw(terminalHeigth - 1, 7, "->");
    mvprintw(terminalHeigth - 1, terminalWidth - 15, "F1");
    mvprintw(terminalHeigth - 1, terminalWidth - 9, "ESC");
    wattroff(stdscr, A_REVERSE);
    mvprintw(terminalHeigth-1, 3, "and");
    mvprintw(terminalHeigth-1, 10, "CHOOSE PAGE");
    mvprintw(terminalHeigth-1, terminalWidth - 12, "or");
    mvprintw(terminalHeigth-1, terminalWidth - 5, "CLOSE");
}

void CInterfaceHelp::display() {
    clear();
    renderHeader();
    renderBody();
    renderFooter();
}

