#ifndef PYSAROLE_CINTERFACEHELP_H
#define PYSAROLE_CINTERFACEHELP_H

#include "../CConstants.h"
#include "CInterfaceController.h"

/**
 * A class that represents a page with information on how to use the application
*/
class CInterfaceHelp : public CInterfaceController {
public:
    /* Default constructor */
    CInterfaceHelp();

    /* Default destructor */
    virtual ~CInterfaceHelp() = default;

    /**
     * Resets the selected help page menu item
    */
    void reset() override;

    /**
     * Navigating the help page
     * @param[in] actKey - Symbol (button) pressed by the user
    */
    void action(int actKey) override;

    /**
     * Render screen with information on how to use the application
    */
    void display() override;

protected:
    /**
     * Display help screen menu items
    */
    void renderHeader() const override;

    /**
     * Display the information of the selected help menu item
    */
    void renderBody() const override;

    /**
     * Display the footer of the help screen
    */
    void renderFooter() const override;

    int m_selected = 0;
};


#endif //PYSAROLE_CINTERFACEHELP_H
