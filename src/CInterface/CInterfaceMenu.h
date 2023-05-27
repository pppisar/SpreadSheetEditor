#ifndef PYSAROLE_CINTERFACEMENU_H
#define PYSAROLE_CINTERFACEMENU_H

#include "CInterfaceController.h"

class CInterfaceMenu : public CInterfaceController {
public:
    CInterfaceMenu() = default;

    ~CInterfaceMenu() = default;

    // Navigating the menu
    void action(int actKey) override;

    // (re)Render menu
    void render() const override;
private:
    int m_SAVE_TABLE = 0;
    int m_SAVE_TABLE_AND_CLOSE = 1;
    int m_SAVE_AND_OPEN_TABLE = 2;
    int m_OPEN_TABLE_WITHOUT_SAVING = 3;
    int m_CLOSE_WITHOUT_SAVING = 4;

    int m_selectedElement = m_SAVE_TABLE;

};


#endif //PYSAROLE_CINTERFACEMENU_H
