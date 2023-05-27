#ifndef PYSAROLE_CLIFECYCLE_H
#define PYSAROLE_CLIFECYCLE_H

#include <map>

#include "CInterface/CInterfaceController.h"
#include "CInterface/CInterfaceWelcome.h"
#include "CInterface/CInterfaceHelp.h"
#include "CInterface/CInterfaceMenu.h"
#include "CInterface/CInterfaceTable.h"

class CLifeCycle {
public:
    CLifeCycle();

    ~CLifeCycle();

    void changeScreen();

    void runApplication();

private:
    std::map<int, CInterfaceController*> m_allScreens;

    int m_currentScreen;
    int m_previousScreen;
};


#endif //PYSAROLE_CLIFECYCLE_H