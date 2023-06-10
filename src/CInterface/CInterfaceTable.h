#ifndef PYSAROLE_CINTERFACETABLE_H
#define PYSAROLE_CINTERFACETABLE_H

#include "../CConstants.h"
#include "../CTable.h"
#include "../CCell.h"
#include "CInterfaceController.h"

class CInterfaceTable : public CInterfaceController {
public:
    CInterfaceTable(CTable * table);

    virtual ~CInterfaceTable() = default;

    void reset() override;

    // void setTable();

    // Table navigation with the ability to edit it
    void action(int actKey) override;

    // Render table with all auxiliary controls
    void display() override;
protected:
    void renderHeader() const override;

    // (re)render table
    void renderBody() const override;

    // render footer of the application
    void renderFooter() const override;
private:
    CTable * m_table;

    int m_posX;
    int m_posY;

    int m_startX;
    int m_startY;

    int m_realX;
    int m_realY;
    
    unsigned m_tableHeight;

    int m_rowCount;
    int m_columnCount;

private:
    void changePosition(int x, int y);

    void renderGrid() const;

    void higlightSelected() const;

    // Render Rows and Colums title
    void renderRCTitle() const;

    void renderCells() const;

    void editCell(unsigned startY, unsigned startX);

    std::string numToAlpha(int num) const;
};


#endif //PYSAROLE_CINTERFACETABLE_H
