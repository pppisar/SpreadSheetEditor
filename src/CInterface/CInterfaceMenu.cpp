#include "CInterfaceMenu.h"

CInterfaceMenu::CInterfaceMenu() 
: CInterfaceController() {}

void CInterfaceMenu::reset() {
    m_selected = 0;
}

void CInterfaceMenu::action(int actKey) {
    switch (actKey) {
        case KEY_UP:
            if (m_selected - 1 >= 0)
                m_selected -= 1;
            renderBody();
            break;
        case KEY_DOWN:
            if (m_selected + 1 <= 4)
                m_selected += 1;
            renderBody();
            break;
        default:
            break;
    }
}

void CInterfaceMenu::display() {
    updateTerminalSize();
    clear();
    reset();
    renderHeader();
    renderBody();
    renderFooter();
}

MenuOption CInterfaceMenu::getSelected() const {
    switch (m_selected) {
        case 0:
            return MenuOption::Create;
        case 1:
            return MenuOption::Load;
        case 2:
            return MenuOption::Save;
        case 3:
            return MenuOption::Save_as;
        case 4:
            return MenuOption::Exit;
        default:
            return MenuOption::Exit;
    }
}

void CInterfaceMenu::renderHeader() const {
    mvprintw(0, 0, "Create, Open or Save table!");
}

void CInterfaceMenu::renderBody() const {
    for (int i = 0; i < 5; i++) {
        if (i == m_selected)
            wattron(stdscr, A_REVERSE);
        mvprintw(i + 2, 0, "%s", CHOICES_MENU[i].c_str());
        wattroff(stdscr, A_REVERSE);
    }
}

void CInterfaceMenu::renderFooter() const {
    move(m_terminalHeight-2, 0);
    hline(0, m_terminalWidth);

    move(m_terminalHeight - 1, 0);
    clrtoeol();

    //FileName

    wattron(stdscr, A_REVERSE);
    mvprintw(m_terminalHeight - 1, m_terminalWidth - 7, "F1");
    wattroff(stdscr, A_REVERSE);
    mvprintw(m_terminalHeight-1, m_terminalWidth - 4, "HELP");
}