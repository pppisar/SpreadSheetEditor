#ifndef PYSAROLE_CLIFECYCLE_H
#define PYSAROLE_CLIFECYCLE_H

#include "CConstants.h"
#include "CTable.h"
#include "CInterface/CInterfaceController.h"
#include "CInterface/CInterfaceWelcome.h"
#include "CInterface/CInterfaceAlert.h"
#include "CInterface/CInterfaceHelp.h"
#include "CInterface/CInterfaceMenu.h"
#include "CInterface/CInterfaceTable.h"
#include "CState/CStateBinary.h"
#include "CState/CStateTxt.h"

#include <map>
#include <string>
#include <ncurses.h>
#include <filesystem>

/**
 * Responsible for managing the entire program. 
 * It changes the interface, saves tables, and accepts input from the user.
*/

class CLifeCycle {
public:
    CLifeCycle();

    ~CLifeCycle();

    /**
     * Method with the main loop of the program.
    */
    void run();
private:
    std::string m_path = "examples/";
    FileName m_fileName;
    CTable* m_table;

    CInterfaceWelcome * m_welcomeInterface;
    CInterfaceAlert * m_alertInterface;
    CInterfaceHelp * m_helpInterface;
    CInterfaceMenu * m_menuInterface;
    CInterfaceTable * m_tableInterface;

    std::map<Screen, CInterfaceController*> m_allScreens;

    Screen m_currentScreen;
    Screen m_previousScreen;

    int m_terminalWidth;
    int m_terminalHeight;
private:
    /**
     * Changes the display of the interface according to the user's selection.
     * @param[in] screen - The corresponding screen that was selected
    */
    void changeScreen(Screen screen);

    /**
     * Checks if the entered file name is correct
     * @return Returns the result of the check (true/false)
    */
    const bool validateFileName() const;

    /**
     * Saves the table to the specified file
     * The specified file is completely overwritten
     * @return Returns true if overwritten successfully, false otherwise
    */
    const bool saveFile();

    /**
     * Loads a table from the specified file
     * @return Returns true if the table is loaded successfully, otherwise - false
    */
    const bool loadFile();

    /**
     * Writes an error message to the footer
    */
    void errorMessage(std::string message);
};
#endif //PYSAROLE_CLIFECYCLE_H