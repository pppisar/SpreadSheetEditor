#include "CInterfaceWelcome.h"

CInterfaceWelcome::CInterfaceWelcome()
: CInterfaceController() {}

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
    move(m_terminalHeight-2, 0);
    hline(0, m_terminalWidth);

    move(m_terminalHeight - 1, 0);
    clrtoeol();

    mvprintw(m_terminalHeight-1, 0, "Made by Pysarenko Oleksii (pysarole)");
    wattron(stdscr, A_REVERSE);
    mvprintw(m_terminalHeight - 1, m_terminalWidth - 7, "F1");
    wattroff(stdscr, A_REVERSE);
    mvprintw(m_terminalHeight-1, m_terminalWidth - 4, "HELP");
}


void CInterfaceWelcome::display() {
    clear();
    updateTerminalSize();
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