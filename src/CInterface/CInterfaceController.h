#ifndef PYSAROLE_CINTERFACECONTROLLER_H
#define PYSAROLE_CINTERFACECONTROLLER_H

#include <ncurses.h>
#include <string>

class CInterfaceController {
public:
    CInterfaceController() = default;

    virtual ~CInterfaceController() = default;

    virtual void reset() = 0;

    // Standard navigation
    virtual void action(int actKey) = 0;

    // Function to display information to the console.
    virtual void display() = 0;

private:
    virtual void renderHeader() const = 0;
    virtual void renderBody() const = 0;
    virtual void renderFooter() const = 0;
};


#endif //PYSAROLE_CINTERFACECONTROLLER_H
