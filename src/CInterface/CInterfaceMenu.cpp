#include "CInterfaceMenu.h"

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
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    wattron(stdscr, A_REVERSE);
    mvprintw(yMax - 1, 0, "F1");
    wattroff(stdscr, A_REVERSE);
    mvprintw(yMax-1, 3, "HELP");
}


void CInterfaceMenu::display() {
    clear();
    renderHeader();
    renderBody();
    renderFooter();
}

unsigned CInterfaceMenu::getSelected() const {
    switch (m_selected) {
        case 0:
            return MENU_CREATE;
        case 1:
            return MENU_LOAD;
        case 2:
            return MENU_SAVE;
        case 3:
            return MENU_SAVE_AS;
        case 4:
            return MENU_EXIT;
        default:
            return MENU_EXIT;
    }
}