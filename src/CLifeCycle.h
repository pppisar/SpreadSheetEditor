#ifndef PYSAROLE_CLIFECYCLE_H
#define PYSAROLE_CLIFECYCLE_H

#include <map>
#include <ncurses.h>

#include "CConstants.h"
#include "CInterface/CInterfaceController.h"
#include "CInterface/CInterfaceWelcome.h"
#include "CInterface/CInterfaceHelp.h"
#include "CInterface/CInterfaceMenu.h"
#include "CInterface/CInterfaceTable.h"

class CLifeCycle {
public:
    

    CLifeCycle();

    ~CLifeCycle();

    void changeScreen(const int screen);

    void run();

private:
    CInterfaceWelcome * m_welcomeInterface;
    CInterfaceHelp * m_helpInterface;
    CInterfaceMenu * m_menuInterface;
    CInterfaceTable * m_tableInterface;

    std::map<int, CInterfaceController*> m_allScreens;

    int m_currentScreen;
    int m_previousScreen;

    int m_terminalWidth;
    int m_terminalHeight;
};


#endif //PYSAROLE_CLIFECYCLE_H
