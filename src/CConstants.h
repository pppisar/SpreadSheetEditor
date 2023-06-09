#ifndef PYSAROLE_CCONSTANTS_H
#define PYSAROLE_CCONSTANTS_H

#include <vector>
#include <string>
#include <map>

// Own types
typedef std::pair<int, int> Position;

// Types of cell value
enum class DataType {
    String,
    Integer,
    Double
};

enum class Screen {
    Welcome,
    Alert,
    Help,
    Table,
    Menu
};

enum class MenuOption {
    Create,
    Load,
    Save,
    Save_as,
    Exit
};

const int MIN_WIDTH = 45;
const int MIN_HEIGTH = 18;

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