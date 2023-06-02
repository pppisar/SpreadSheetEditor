#ifndef PYSAROLE_CINTERFACEMENU_H
#define PYSAROLE_CINTERFACEMENU_H

#include "../CConstants.h"
#include "CInterfaceController.h"

class CInterfaceMenu : public CInterfaceController {
public:
    CInterfaceMenu() = default;

    virtual ~CInterfaceMenu() = default;

    void reset() override;

    // Navigating the start menu
    void action(int actKey) override;

    // (re)Render welcome page
    void display() override;

    // Get selected item
    unsigned getSelected() const;
private:
    void renderHeader() const override;
    void renderBody() const override;
    void renderFooter() const override;

    int m_selected = 0;
};


#endif //PYSAROLE_CINTERFACEMENU_H
