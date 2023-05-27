#ifndef PYSAROLE_CINTERFACETABLE_H
#define PYSAROLE_CINTERFACETABLE_H

#include "../CConstants.h"
#include "../CTable.h"
#include "CInterfaceController.h"

class CInterfaceTable : public CInterfaceController {
public:
//    CInterfaceTable(CTable * table);
    CInterfaceTable();

    virtual ~CInterfaceTable() = default;

    void reset() override;

    // void setTable();

    // Table navigation with the ability to edit it
    void action(int actKey) override;

    // Render table with all auxiliary controls
    void display() override;
private:
    CTable * m_table;

    int m_posX;
    int m_posY;

    int m_startX;
    int m_startY;

    int m_realX;
    int m_realY;
    
    unsigned m_tableHeight;

    int m_terminalWidth;
    int m_terminalHeight;

    int m_rowCount;
    int m_columnCount;


    void changePosition(int x, int y);

    void renderHeader() const override;

    void renderGrid() const;

    // Render Rows and Colums title
    void renderRCTitle() const;

    void renderCell() const;

    void renderCells() const;

    // (re)render table
    void renderBody() const override;

    // render footer of the application
    void renderFooter() const override;

    void editCell();

    std::string numToAlpha(int num) const;
};


#endif //PYSAROLE_CINTERFACETABLE_H
