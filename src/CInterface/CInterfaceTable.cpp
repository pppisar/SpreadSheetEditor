#include "CInterfaceTable.h"

CInterfaceTable::CInterfaceTable(CTable *table) {
    m_table = table;
}

void CInterfaceTable::action(int actKey) {
    switch (actKey) {
        case 'a':
            break;
        case 'b':
            break;
        // TODO: Navigating the table and calling other menus
    }
}

void CInterfaceTable::render() const {
    header(); // render header(value and expression of the selected cell)
    content(); // render table
    footer(); // render (keys that allow to call other menus);
}

bool CInterfaceTable::changePosition(int x, int y) {
    if (m_posX + x > 0 and m_posY + y > 0) {
        m_posX += x;
        m_posY += y;
        return true;
    }
    return false;
}

void CInterfaceTable::header() {
    //TODO: Render the form where the cell will be edited
}

void CInterfaceTable::content() {
    // TODO: Render table with selected cell
}

void CInterfaceTable::footer() {
    // TODO: Render additional controls that can be called
}