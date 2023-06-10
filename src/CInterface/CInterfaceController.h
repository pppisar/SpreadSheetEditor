#ifndef PYSAROLE_CINTERFACECONTROLLER_H
#define PYSAROLE_CINTERFACECONTROLLER_H

#include "../CConstants.h"
#include <ncurses.h>
#include <string>

class CInterfaceController {
public:
    CInterfaceController() = default;

    virtual ~CInterfaceController() = default;

    virtual FileName getFileName(std::string forWhat) const;

    virtual void reset() = 0;

    // Standard navigation
    virtual void action(int actKey) = 0;

    // Function to display information to the console.
    virtual void display() = 0;

protected:
    virtual void renderHeader() const = 0;
    virtual void renderBody() const = 0;
    virtual void renderFooter() const = 0;
protected:
    int m_terminalWidth;
    int m_terminalHeight;
protected:
    virtual void updateTerminalSize();
    virtual std::string readInputString(unsigned startY, unsigned startX, std::string buffer) const;
};


#endif //PYSAROLE_CINTERFACECONTROLLER_H
