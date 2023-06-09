#include "CInterfaceWelcome.h"

void CInterfaceWelcome::reset() {
    m_selected = 0;
}

void CInterfaceWelcome::action(int actKey) {
    switch (actKey) {
        case KEY_UP:
            if (m_selected - 1 >= 0)
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
    for (int i = 0; i < 3; i++) {
        if (i == m_selected)
            wattron(stdscr, A_REVERSE);
        mvprintw(i + 2, 0, "%s", CHOICES_WELCOME[i].c_str());
        wattroff(stdscr, A_REVERSE);
    }
}

void CInterfaceWelcome::renderFooter() const {
    int terminalHeigth, terminalWidth;
    getmaxyx(stdscr, terminalHeigth, terminalWidth);

    mvprintw(terminalHeigth-1, 0, "Made by Pysarenko Oleksii (pysarole)");

    wattron(stdscr, A_REVERSE);
    mvprintw(terminalHeigth - 1, terminalWidth - 7, "F1");
    wattroff(stdscr, A_REVERSE);
    mvprintw(terminalHeigth-1, terminalWidth - 4, "HELP");
}


void CInterfaceWelcome::display() {
    clear();
    renderHeader();
    renderBody();
    renderFooter();
}

MenuOption CInterfaceWelcome::getSelected() const {
    switch (m_selected) {
        case 0:
            return MenuOption::Create;
        case 1:
            return MenuOption::Load;
        case 2:
            return MenuOption::Exit;
        default:
            return MenuOption::Create;
    }
}