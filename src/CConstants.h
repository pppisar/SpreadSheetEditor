#ifndef PYSAROLE_CCONSTANTS_H
#define PYSAROLE_CCONSTANTS_H

#include <vector>
#include <string>
#include <map>

// Own types
typedef std::pair<int, int> Position;
//                         isNum, isErr,      value
typedef std::pair<std::pair<bool, bool>, std::string> ParseResult;
//               isNum,      value
typedef std::pair<bool, std::string> Value;
//                priority, operator
typedef std::pair<unsigned, char> Operator;
//               isErr,      value
typedef std::pair<bool, std::string> execRes;

// Screens constants
const unsigned SCREEN_WELCOME = 0;
const unsigned SCREEN_HELP = 1;
const unsigned SCREEN_TABLE = 2;
const unsigned SCREEN_MENU = 3;

// Menu constants
const unsigned MENU_CREATE = 0;
const unsigned MENU_LOAD = 1;
const unsigned MENU_SAVE = 2;
const unsigned MENU_SAVE_AS = 3;
const unsigned MENU_EXIT = 4;

// Table constants
const unsigned CELL_WIDTH = 10;
const unsigned CELL_HEIGHT = 2;
const unsigned HEADER_HEIGHT = 5;
const unsigned FOOTER_HEIGHT = 2;
const unsigned TABLE_START_POSITION_X = CELL_WIDTH / 2;
const unsigned TABLE_START_POSITION_Y = HEADER_HEIGHT + CELL_HEIGHT;

// Welcome screen choises
const std::string CHOICES_WELCOME[3] = {
    "CREATE NEW TABLE",
    "OPEN EXISTING TABLE",
    "EXIT APPLICATION"
};

// Menu screen choises
const std::string CHOICES_MENU[5] = {
    "CREATE NEW TABLE",
    "OPEN TABLE",
    "SAVE TABLE",
    "SAVE TABLE AS",
    "EXIT"
};

const std::string CHOISE_HELP[3] = {
    "NAVIGATION",
    "EDITING",
    "FUNCTIONS"
};

const std::string TEXT_HELP[3] = {
    "Some text about NAVIGATION",
    "Some text about EDITING",
    "Some text about FUNCTIONS"
};

#endif //PYSAROLE_CCONSTANTS_H