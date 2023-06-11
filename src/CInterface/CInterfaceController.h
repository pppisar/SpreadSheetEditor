#ifndef PYSAROLE_CINTERFACECONTROLLER_H
#define PYSAROLE_CINTERFACECONTROLLER_H

#include "../CConstants.h"
#include <ncurses.h>
#include <string>

/**
 * A template class that implements auxiliary methods 
 * and declares abstract methods for interface output
*/
class CInterfaceController {
public:
    /* Default constructor */
    CInterfaceController() = default;

    /* Default destructor */
    virtual ~CInterfaceController() = default;

    /**
     * Method for user to specify the name of the table (file) and select the extension
     * @param[in] forWhat - For what enter the name of the file (Save/Load)
     * @return Returns the entered file name and its extension
    */
    virtual FileName getFileName(std::string forWhat) const;

    /**
     * Resets the selected items on the screen
    */
    virtual void reset() = 0;

    /**
     * Determines the interaction with the screen relative to the pressed button
     * @param[in] actKey - Symbol (button) pressed by the user
    */
    virtual void action(int actKey) = 0;

    /**
     * Displays all screen elements
    */
    virtual void display() = 0;

protected:
    /**
     * Display the header of the interface
    */
    virtual void renderHeader() const = 0;

    /**
     * Display the main part (body) of the interface
    */
    virtual void renderBody() const = 0;

    /**
     * Display the footer of the interface
    */
    virtual void renderFooter() const = 0;
protected:
    int m_terminalWidth;
    int m_terminalHeight;
protected:
    /**
     * Updates the current terminal dimensions
    */
    virtual void updateTerminalSize();

    /**
     * A function that reads a string from the user in the specified location
     * @param[in] startY - Initial vertical position
     * @param[in] startX - Initial horizontal position
     * @return Returns the string that was entered by the user
    */
    virtual std::string readInputString(unsigned startY, unsigned startX, std::string buffer) const;
};


#endif //PYSAROLE_CINTERFACECONTROLLER_H
