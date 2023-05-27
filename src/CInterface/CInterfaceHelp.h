#ifndef PYSAROLE_CINTERFACEHELP_H
#define PYSAROLE_CINTERFACEHELP_H

#include "../CConstants.h"
#include "CInterfaceController.h"

class CInterfaceHelp : public CInterfaceController {
public:
    CInterfaceHelp() = default;

    virtual ~CInterfaceHelp() = default;

    void reset() override;

    // Navigating the start menu
    void action(int actKey) override;

    // Render screen with information on how to use the application
    void display() override;

private:
    int m_selected = 0;

    void renderHeader() const override;
    void renderBody() const override;
    void renderFooter() const override;
};


#endif //PYSAROLE_CINTERFACEHELP_H
