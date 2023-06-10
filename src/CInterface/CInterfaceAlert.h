#ifndef PYSAROLE_CINTERFACEALERT_H
#define PYSAROLE_CINTERFACEALERT_H

#include "../CConstants.h"
#include "CInterfaceController.h"

class CInterfaceAlert : public CInterfaceController {
public:
    CInterfaceAlert() = default;

    virtual ~CInterfaceAlert() = default;

    void reset() override;

    // Navigating the start menu
    void action(int actKey) override;

    // (re)Render welcome page
    void display() override;
protected:
    void renderHeader() const override;
    void renderBody() const override;
    void renderFooter() const override;
};


#endif //PYSAROLE_CINTERFACEALERT_H
