#include "CInterfaceWelcome.h"

void CInterfaceWelcome::reset() {
    m_selected = 0;
}

void CInterfaceWelcome::action(int actKey) {
    switch (actKey) {
        case KEY_UP:
            if ((int)(m_selected - 1) >= 0)
                m_selected -= 1;
            renderBody();
            break;
        case KEY_DOWN:
            if (m_selected + 1 <= 2)
                m_selected += 1;
            renderBody();
            break;
        default:
            break;
    }
}


void CInterfaceWelcome::renderHeader() const {
    mvprintw(0, 0, "Welcome to the Simple Sheets");
}

void CInterfaceWelcome::renderBody() const {
    for (unsigned i = 0; i < 3; i++) {
        if (i == m_selected)
            wattron(stdscr, A_REVERSE);
        mvprintw(i + 2, 0, "%s", CHOICES_WELCOME[i].c_str());
        wattroff(stdscr, A_REVERSE);
    }
}

void CInterfaceWelcome::renderFooter() const {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    wattron(stdscr, A_REVERSE);
    mvprintw(yMax - 1, 0, "F1");
    wattroff(stdscr, A_REVERSE);
    mvprintw(yMax-1, 3, "HELP");
    mvprintw(yMax-1, xMax - 36, "Made by Pysarenko Oleksii (pysarole)");
}


void CInterfaceWelcome::display() {
    clear();
    renderHeader();
    renderBody();
    renderFooter();
}

unsigned CInterfaceWelcome::getSelected() const {
    switch (m_selected) {
        case 0:
            return MENU_CREATE;
        case 1:
            return MENU_LOAD;
        case 2:
            return MENU_EXIT;
        default:
            return MENU_CREATE;
    }
}