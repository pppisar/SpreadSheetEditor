#ifndef PYSAROLE_CLIFECYCLE_H
#define PYSAROLE_CLIFECYCLE_H

#include <map>
#include <ncurses.h>
#include <string>

#include "CConstants.h"
#include "CTable.h"
#include "CInterface/CInterfaceController.h"
#include "CInterface/CInterfaceWelcome.h"
#include "CInterface/CInterfaceAlert.h"
#include "CInterface/CInterfaceHelp.h"
#include "CInterface/CInterfaceMenu.h"
#include "CInterface/CInterfaceTable.h"
#include "CState/CStateBinary.h"

class CLifeCycle {
public:
    CLifeCycle();

    ~CLifeCycle();

    void run();
private:
    std::string m_path = "examples/";
    FileName m_fileName;

    CInterfaceWelcome * m_welcomeInterface;
    CInterfaceAlert * m_alertInterface;
    CInterfaceHelp * m_helpInterface;
    CInterfaceMenu * m_menuInterface;
    CInterfaceTable * m_tableInterface;

    std::map<Screen, CInterfaceController*> m_allScreens;

    CTable* m_table;

    Screen m_currentScreen;
    Screen m_previousScreen;

    int m_terminalWidth;
    int m_terminalHeight;

    void changeScreen(const Screen screen);
};


#endif //PYSAROLE_CLIFECYCLE_H
