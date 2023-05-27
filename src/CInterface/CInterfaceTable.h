#ifndef PYSAROLE_CINTERFACETABLE_H
#define PYSAROLE_CINTERFACETABLE_H

#include "CInterfaceController.h"
#include "../CTable.h"

class CInterfaceTable : public CInterfaceController {
public:
    CInterfaceTable(CTable * table);

    ~CInterfaceTable() = default;

    // Table navigation with the ability to edit it
    void action(int actKey) override;

    // Render table with all auxiliary controls
    void render() const override;
private:
    CTable * m_table;

    int m_posX = 1;
    int m_posY = 1;

    bool changePosition(int x, int y);

    // (re)render header of the application
    void header();

    // (re)render table
    void content();

    // render footer of the application
    void footer();
};


#endif //PYSAROLE_CINTERFACETABLE_H
