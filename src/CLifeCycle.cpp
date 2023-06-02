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
    m_helpInterface = new CInterfaceHelp();
    m_menuInterface = new CInterfaceMenu();
    m_table = new CTable();
    m_tableInterface = new CInterfaceTable(m_table);
    m_allScreens.emplace(SCREEN_WELCOME, m_welcomeInterface);
    m_allScreens.emplace(SCREEN_HELP, m_helpInterface);
    m_allScreens.emplace(SCREEN_MENU, m_menuInterface);
    m_allScreens.emplace(SCREEN_TABLE, m_tableInterface);

    // Set welcome screen
    m_previousScreen = m_currentScreen = SCREEN_WELCOME;
    changeScreen(m_currentScreen);
}

CLifeCycle::~CLifeCycle() {
    for (auto screen: m_allScreens)
        delete screen.second;

    delete m_table;
    endwin();
}

void CLifeCycle::changeScreen(const int screen) {
    m_previousScreen = m_currentScreen;
    m_currentScreen = screen;
    m_allScreens[screen]->display();
}

void CLifeCycle::run() {
    int inpChar;
    int terminalWidth, terminalHeight;

    while (true) {
        // Get the key that the user pressed.
        inpChar = getch();

        getmaxyx(stdscr, terminalHeight, terminalWidth);

        if (terminalHeight != m_terminalHeight || terminalWidth != m_terminalWidth) {
            m_terminalWidth = terminalWidth;
            m_terminalHeight = terminalHeight;
            m_allScreens[m_currentScreen]->display();
        }

        switch(inpChar) {
            case KEY_F(1): // show help page
                if (m_currentScreen == SCREEN_HELP)
                    changeScreen(m_previousScreen);
                else {
                    m_allScreens[SCREEN_HELP]->reset();
                    changeScreen(SCREEN_HELP);
                }
                break;
            case 27: // Esc button => menu page
                if (m_currentScreen != SCREEN_WELCOME) {
                    if (m_currentScreen == SCREEN_HELP)
                        changeScreen(m_previousScreen);
                    else if (m_currentScreen == SCREEN_MENU)
                        changeScreen(SCREEN_TABLE);
                    else {
                        m_allScreens[SCREEN_MENU]->reset();
                        changeScreen(SCREEN_MENU);
                    }
                }
                break;
            case '\n':
            case KEY_ENTER:
                if (m_currentScreen == SCREEN_TABLE) {
                    m_allScreens[m_currentScreen]->action(inpChar);
                }
                else {
                    if (m_currentScreen == SCREEN_WELCOME) {
                        switch (m_welcomeInterface->getSelected()) {
                            case MENU_CREATE:
                                changeScreen(SCREEN_TABLE);
                                break;
                            case MENU_LOAD:
                                break;
                            case MENU_EXIT:
                                return;
                        }
                    }
                    else if (m_currentScreen == SCREEN_MENU) {
                        switch (m_menuInterface->getSelected()) {
                        case MENU_CREATE:
                            break;
                        case MENU_LOAD:
                            break;
                        case MENU_SAVE:
                            break;
                        case MENU_SAVE_AS:
                            break;
                        case MENU_EXIT:
                            return;
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