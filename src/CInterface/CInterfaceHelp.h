#ifndef PYSAROLE_CINTERFACEHELP_H
#define PYSAROLE_CINTERFACEHELP_H

#include "CInterfaceController.h"

class CInterfaceHelp : public CInterfaceController {
public:
    CInterfaceHelp() = default;

    ~CInterfaceHelp() = default;

    // Render screen with information on how to use the application
    void render() const override;

private:

};


#endif //PYSAROLE_CINTERFACEHELP_H
