#ifndef PYSAROLE_CINTERFACEMENU_H
#define PYSAROLE_CINTERFACEMENU_H

#include "../CConstants.h"
#include "CInterfaceController.h"

/**
 * A class that represents the main menu for managing the application
 * It can be called when editing a table
*/
class CInterfaceMenu : public CInterfaceController {
public:
    /* Default constructor */
    CInterfaceMenu();

    /* Default destructor */
    virtual ~CInterfaceMenu() = default;

    /**
     * Resets the selected menu item
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
     * Display the header of the menu screen
    */
    void renderHeader() const override;

    /**
     * Display menu items
    */
    void renderBody() const override;

    /**
     * Display the footer of the menu screen
    */
    void renderFooter() const override;

    int m_selected = 0;
};


#endif //PYSAROLE_CINTERFACEMENU_H
