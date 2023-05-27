#ifndef PYSAROLE_CINTERFACEWELCOME_H
#define PYSAROLE_CINTERFACEWELCOME_H

#include "CInterfaceController.h"

class CInterfaceWelcome : public CInterfaceController {
public:
    CInterfaceWelcome() = default;

    ~CInterfaceWelcome() = default;

    // Navigating the start menu
    void action(int actKey) override;

    // (re)Render welcome page
    void render() const override;
private:
    int m_CREATE_NEW_TABLE = 0;
    int m_OPEN_EXISTING_TABLE = 1;
    int m_EXIT_APPLICATION = 2;

    int m_selectedElement = m_CREATE_NEW_TABLE;
};


#endif //PYSAROLE_CINTERFACEWELCOME_H
