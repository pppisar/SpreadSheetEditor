#ifndef PYSAROLE_CINTERFACEWELCOME_H
#define PYSAROLE_CINTERFACEWELCOME_H

#include "../CConstants.h"
#include "CInterfaceController.h"

class CInterfaceWelcome : public CInterfaceController {
public:
    CInterfaceWelcome();

    virtual ~CInterfaceWelcome() = default;

    void reset() override;

    // Navigating the start menu
    void action(int actKey) override;

    // (re)Render welcome page
    void display() override;

    // Get selected item
    MenuOption getSelected() const;
protected:
    void renderHeader() const override;
    void renderBody() const override;
    void renderFooter() const override;

    int m_selected = 0;
};


#endif //PYSAROLE_CINTERFACEWELCOME_H
