#ifndef PYSAROLE_CINTERFACECONTROLLER_H
#define PYSAROLE_CINTERFACECONTROLLER_H

#include <ncurses.h>

class CInterfaceController {
public:
    CInterfaceController() = default;

    ~CInterfaceController() = default;

    // Standard navigation
    virtual void action(int actKey);

    // Function to display information to the console.
    virtual void render() const = 0;

private:
    int m_screenWidth;
    int m_screenHeight;
    int m_contentHeight;
};


#endif //PYSAROLE_CINTERFACECONTROLLER_H
