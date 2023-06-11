#ifndef PYSAROLE_CINTERFACEALERT_H
#define PYSAROLE_CINTERFACEALERT_H

#include "../CConstants.h"
#include "CInterfaceController.h"

/**
 * A class that reports a small terminal size
*/
class CInterfaceAlert : public CInterfaceController {
public:
    /* Default constructor */
    CInterfaceAlert();

    /* Default destructor */
    virtual ~CInterfaceAlert() = default;

    void reset() override;

    void action(int actKey) override;

    /**
     * Full display of the alert page
    */
    void display() override;
protected:
    /**
     * Display error text
    */
    void renderHeader() const override;

    /**
     * Displaying the cause of the error
    */
    void renderBody() const override;

    /**
     * Displaying the error correction algorithm
    */
    void renderFooter() const override;
};


#endif //PYSAROLE_CINTERFACEALERT_H
