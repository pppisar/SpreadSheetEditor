#include "CInterfaceAlert.h"

void CInterfaceAlert::reset() { }

void CInterfaceAlert::action(int actKey) { }


void CInterfaceAlert::renderHeader() const {
    mvprintw(0, 0, "The terminal size is too small!");
}

void CInterfaceAlert::renderBody() const {
    int terminalHeigth, terminalWidth;
    getmaxyx(stdscr, terminalHeigth, terminalWidth);

    mvprintw(2, 0, "Minimal width: %d", MIN_WIDTH);
    mvprintw(3, 0, "Minimal heigth: %d", MIN_HEIGTH);

    mvprintw(5, 0, "Actual width: %d", terminalWidth);
    mvprintw(6, 0, "Actual heigth: %d", terminalHeigth);

}

void CInterfaceAlert::renderFooter() const {
    mvprintw(8, 0, "Change the size of the terminal");
    mvprintw(9, 0, "to the minimum allowable values!");
}


void CInterfaceAlert::display() {
    clear();
    renderHeader();
    renderBody();
    renderFooter();
}