#ifndef PYSAROLE_CINTERFACEWELCOME_H
#define PYSAROLE_CINTERFACEWELCOME_H

#include "../CConstants.h"
#include "CInterfaceController.h"

/**
 * A class that represents the application's start menu
 * It appears only when the application is launched
*/
class CInterfaceWelcome : public CInterfaceController {
public:
    /* Default constructor */
    CInterfaceWelcome();

    /* Default destructor */
    virtual ~CInterfaceWelcome() = default;

    /**
     * Resets the selected start menu item
    */
    void reset() override;

    /**
     * Selecting menu items
     * @param[in] actKey - Symbol (button) pressed by the user
    */
    void action(int actKey) override;

    /**
     * Full display of the welcome page
    */
    void display() override;

    /**
     * A method to return the selected menu item
     * @return Returns the selected menu item 
    */
    MenuOption getSelected() const;
protected:
    /**
     * Display the header of the welcome screen
    */
    void renderHeader() const override;

    /**
     * Display menu items
    */
    void renderBody() const override;

    /**
     * Display the footer of the welcome screen
    */
    void renderFooter() const override;

    int m_selected = 0;
};


#endif //PYSAROLE_CINTERFACEWELCOME_H
