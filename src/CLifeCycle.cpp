#include "CLifeCycle.h"

CLifeCycle::CLifeCycle() {
    // Initialize the screen
    initscr();
    cbreak();
    noecho();

    // If terminal can change color => turn on this function
    if (has_colors())
        start_color();

    // Enable the ability to read function keys
    keypad(stdscr, true);

    // Make the cursor invisible
    curs_set(0);

    // Get terminal width and height
    getmaxyx(stdscr, m_terminalHeight, m_terminalWidth);

    // Create all possible screens
    m_welcomeInterface = new CInterfaceWelcome();
    m_alertInterface = new CInterfaceAlert();
    m_helpInterface = new CInterfaceHelp();
    m_menuInterface = new CInterfaceMenu();
    m_table = new CTable();
    m_tableInterface = new CInterfaceTable(m_table);
    m_allScreens.emplace(Screen::Welcome, m_welcomeInterface);
    m_allScreens.emplace(Screen::Alert, m_alertInterface);
    m_allScreens.emplace(Screen::Help, m_helpInterface);
    m_allScreens.emplace(Screen::Menu, m_menuInterface);
    m_allScreens.emplace(Screen::Table, m_tableInterface);

    // Set welcome screen
    m_previousScreen = m_currentScreen = Screen::Welcome;
    changeScreen(m_currentScreen);
    m_welcomeInterface->display();
}

CLifeCycle::~CLifeCycle() {
    for (auto screen: m_allScreens)
        delete screen.second;

    delete m_table;
    endwin();
}

void CLifeCycle::run() {
    int inpChar;
    int terminalWidth, terminalHeight;

    while (true) {
        getmaxyx(stdscr, terminalHeight, terminalWidth);

        if (terminalHeight != m_terminalHeight || terminalWidth != m_terminalWidth) {
            m_terminalWidth = terminalWidth;
            m_terminalHeight = terminalHeight;
            m_allScreens[m_currentScreen]->display();
        }
        
        if (m_terminalWidth < MIN_WIDTH || m_terminalHeight < MIN_HEIGTH) {
            m_allScreens[Screen::Alert]->display();
            getch();
        }
        else {
            // Get the key that the user pressed.
            inpChar = getch();

            switch(inpChar) {
                case KEY_F(1): // show help page
                    if (m_currentScreen == Screen::Help)
                        changeScreen(m_previousScreen);
                    else {
                        m_allScreens[Screen::Help]->reset();
                        changeScreen(Screen::Help);
                    }
                    break;
                case 27: // Esc button => menu page
                    if (m_currentScreen != Screen::Welcome) {
                        if (m_currentScreen == Screen::Help)
                            changeScreen(m_previousScreen);
                        else if (m_currentScreen == Screen::Menu)
                            changeScreen(Screen::Table);
                        else {
                            m_allScreens[Screen::Menu]->reset();
                            changeScreen(Screen::Menu);
                        }
                    }
                    break;
                case '\n':
                case KEY_ENTER:
                    if (m_currentScreen == Screen::Table)
                        m_allScreens[m_currentScreen]->action(inpChar);
                    else {
                        if (m_currentScreen == Screen::Welcome) {
                            switch (m_welcomeInterface->getSelected()) {
                                case MenuOption::Create:
                                    changeScreen(Screen::Table);
                                    break;
                                case MenuOption::Load:
                                    m_fileName = m_welcomeInterface->getFileName("Load");
                                    if (validateFileName() && loadFile()) {
                                        m_table->setName(m_fileName);
                                        changeScreen(Screen::Table);
                                    }
                                    else
                                        errorMessage("Can't load the file");
                                    break;
                                case MenuOption::Exit:
                                    return;
                                default:
                                    break;
                            }
                        }
                        else if (m_currentScreen == Screen::Menu) {
                            switch (m_menuInterface->getSelected()) {
                                case MenuOption::Create:
                                    if (m_table->isChanged() && !m_table->isNamed()) 
                                        m_fileName = m_welcomeInterface->getFileName("Save");
                                    if ((m_table->isChanged() && validateFileName() && saveFile())
                                        || !m_table->isChanged()) {
                                        m_table->reset();
                                        m_tableInterface->reset();
                                        changeScreen(Screen::Table);
                                    }
                                    else
                                        errorMessage("Can't save previous file");
                                    break;
                                case MenuOption::Load:
                                    if(m_table->isChanged() &&  !m_table->isNamed())
                                        m_fileName = m_menuInterface->getFileName("Save");
                                    if((m_table->isChanged() && validateFileName() && saveFile())
                                        || !m_table->isChanged()) {
                                        m_table->setName(m_fileName);
                                        m_fileName = m_welcomeInterface->getFileName("Load");
                                        if (validateFileName() && loadFile()) {
                                            m_table->setName(m_fileName);
                                            changeScreen(Screen::Table);
                                        }
                                        else
                                            errorMessage("Can't load the file");
                                    }
                                    else
                                        errorMessage("Can't previous the file");
                                    break;
                                case MenuOption::Save:
                                    if (m_table->isChanged() && !m_table->isNamed()) 
                                        m_fileName = m_welcomeInterface->getFileName("Save");
                                    if ((m_table->isChanged() && validateFileName() && saveFile())
                                        || !m_table->isChanged()) {
                                        m_table->setName(m_fileName);
                                        changeScreen(Screen::Table);
                                    }
                                    else
                                        errorMessage("Can't save previous file");
                                    break;
                                case MenuOption::Save_as:
                                    m_fileName = m_welcomeInterface->getFileName("Save");
                                    if ((validateFileName() && saveFile())
                                        || !m_table->isChanged()) {
                                        m_table->setName(m_fileName);
                                        changeScreen(Screen::Table);
                                    }
                                    else
                                        errorMessage("Can't save previous file");
                                    break;
                                case MenuOption::Exit:
                                    if (m_table->isChanged() && !m_table->isNamed()) 
                                        m_fileName = m_welcomeInterface->getFileName("Save");
                                    if ((m_table->isChanged() && validateFileName() && saveFile())
                                        || !m_table->isChanged()) {
                                        return;
                                    }
                                    else
                                        errorMessage("Can't save previous file");
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                    break;
                default:
                    m_allScreens[m_currentScreen]->action(inpChar);
                    break;
            }
        }
    }
}

void CLifeCycle::changeScreen(Screen screen) {
    m_previousScreen = m_currentScreen;
    m_currentScreen = screen;
    m_allScreens[screen]->display();
}

const bool CLifeCycle::validateFileName() const {
    std::string invalidChars = "(\\/*:?<>|\"')";
    for (char c : m_fileName.first) {
        if (invalidChars.find(c) != std::string::npos)
            return false;
    }
    if (std::filesystem::path(m_fileName.first).has_extension())
        return false;

    if (std::filesystem::path(m_fileName.first).has_parent_path())
        return false;

    return true;
}

const bool CLifeCycle::saveFile() {
    if (m_fileName.second == FileType::Binary) {
        CStateBinary stateManager(m_table, m_fileName.first, m_path);
        if (!stateManager.save())
            return false;
    }
    else {
        CStateTxt stateManager(m_table, m_fileName.first, m_path);
        if (!stateManager.save())
            return false;
    }
    return true;
}

const bool CLifeCycle::loadFile() {
    if (m_fileName.second == FileType::Binary) {
        CStateBinary stateManager(m_table, m_fileName.first, m_path);
        if (!stateManager.load())
            return false;
    }
    else {
        CStateTxt stateManager(m_table, m_fileName.first, m_path);
        if (!stateManager.load())
            return false;
    }
    return true;
}

void CLifeCycle::errorMessage(std::string message) {
        move(m_terminalHeight - 2, 0);
        clrtoeol();
        mvprintw(m_terminalHeight - 2, 0, "%s", message.c_str());

        move(m_terminalHeight - 1, 0);
        clrtoeol();
        mvprintw(m_terminalHeight - 1, 0, "Press any button to continue");

        getch();
        m_allScreens[m_currentScreen]->display();
}