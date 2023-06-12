#include "CInterfaceHelp.h"

CInterfaceHelp::CInterfaceHelp() 
:CInterfaceController() { }

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
            if (m_selected + 1 <= 3)
                m_selected += 1;
            renderHeader();
            renderBody();
            break;
        default:
            break;
    }
}

void CInterfaceHelp::display() {
    updateTerminalSize();
    clear();
    reset();
    renderHeader();
    renderBody();
    renderFooter();
}

void CInterfaceHelp::renderHeader() const {
    int startPos = 1;
    for (int i = 0; i < 4; i++) {
        if (i == m_selected)
            wattron(stdscr, A_REVERSE);
        mvprintw(0, startPos, "%s", CHOISE_HELP[i].c_str());
        wattroff(stdscr, A_REVERSE);
        startPos += CHOISE_HELP[i].size() + 2;
    }
}

void CInterfaceHelp::renderBody() const {
    for (int i = 1; i < m_terminalHeight - 2; i++) {
        move(i, 0);
        clrtoeol();
    }
    if (m_selected == 0) {
        mvprintw(2, 0 , " - Use the arrow keys to navigate");
        mvprintw(4, 0 , " - To select a menu item or cell, use Enter");
        mvprintw(6, 0 , " - To open the menu while editing a table,");
        mvprintw(7, 0 , "   press Esc");
        mvprintw(9, 0 , " - Pay attention to the tips in the footer");
    }
    else if (m_selected == 1) {
        mvprintw(2, 0 , " - To start editing a cell, press Enter");
        mvprintw(4, 0 , " - Use the <- and -> keys to navigate");
        mvprintw(5, 0 , "   through the text while editing");
        mvprintw(7, 0 , " - You can delete a specific character and");
        mvprintw(8, 0 , "   insert a character at a specific position");
        mvprintw(10, 0 , " - To save the edited string, press Enter");
    }
    else if (m_selected == 2) {
        mvprintw(2, 0 , " - The application implements the following");
        mvprintw(3, 0 , "   arithmetic functions:");
        mvprintw(4, 0 , "    - sin()");
        mvprintw(5, 0 , "    - cos()");
        mvprintw(6, 0 , "    - ln()");
        mvprintw(7, 0 , "    - exp()");
        mvprintw(8, 0 , "    - sqrt()");
        mvprintw(9, 0 , "    - abs()");
        mvprintw(11, 0 , " - The application implements the following");
        mvprintw(12, 0 , "   arithmetic operations:");
        mvprintw(13, 0 , "    - (+) Numbers and Strings");
        mvprintw(14, 0 , "    - (-) Numbers");
        mvprintw(15, 0 , "    - (*) Numbers and Number with strings");
        mvprintw(16, 0 , "    - (/) Numbers");
        mvprintw(17, 0 , "    - (^) Numbers");
        mvprintw(18, 0 , "    - (%%) Numbers(Integers)");
    }
    else {
        mvprintw(2, 0 , "You may encounter the following errors while");
        mvprintw(3, 0 , "working with the application:");
        mvprintw(4, 0 , " - BadSyntax");
        mvprintw(5, 0 , "    - Entering an invalid number");
        mvprintw(6, 0 , "    - Entering an invalid cell");
        mvprintw(7, 0 , "    - Two operands in a row");
        mvprintw(8, 0 , "    - Two numbers/strings in a row");
        mvprintw(9, 0 , "    - The presence of extra brackets");
        mvprintw(10, 0 , "    - Unknown character");
        mvprintw(11, 0 , " - BadLogic");
        mvprintw(12, 0 , "    - Reference to a non-existent");
        mvprintw(13, 0 , "      or invalid cell");
        mvprintw(14, 0 , " - BadOpArgs");
        mvprintw(15, 0 , "    - Invalid argument type");
        mvprintw(16, 0 , " - Expected\"");
        mvprintw(17, 0 , "    - A string that did not end with \"");
        mvprintw(18, 0 , " - BigNumErr");
        mvprintw(19, 0 , "    - Number is too large");
        mvprintw(20, 0 , " - LoopError");
        mvprintw(21, 0 , "    - Looping between cells occurs");
    }
}

void CInterfaceHelp::renderFooter() const {
    move(m_terminalHeight-2, 0);
    hline(0, m_terminalWidth);

    wattron(stdscr, A_REVERSE);
    mvprintw(m_terminalHeight - 1, 0, "<-");
    mvprintw(m_terminalHeight - 1, 7, "->");
    mvprintw(m_terminalHeight - 1, m_terminalWidth - 15, "F1");
    mvprintw(m_terminalHeight - 1, m_terminalWidth - 9, "ESC");
    wattroff(stdscr, A_REVERSE);
    mvprintw(m_terminalHeight-1, 3, "and");
    mvprintw(m_terminalHeight-1, 10, "CHOOSE PAGE");
    mvprintw(m_terminalHeight-1, m_terminalWidth - 12, "or");
    mvprintw(m_terminalHeight-1, m_terminalWidth - 5, "CLOSE");
}