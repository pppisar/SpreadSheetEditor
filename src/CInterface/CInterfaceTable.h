#ifndef PYSAROLE_CINTERFACETABLE_H
#define PYSAROLE_CINTERFACETABLE_H

#include "../CConstants.h"
#include "../CTable.h"
#include "../CCell.h"
#include "CInterfaceController.h"


/**
 * Class that represents the table control page
*/
class CInterfaceTable : public CInterfaceController {
public:
    /* Constructor */
    CInterfaceTable(CTable * table);

    /* Default destructor */
    virtual ~CInterfaceTable() = default;

    /**
     * Resetting the current cells positions
    */
    void reset() override;

    /**
     * Table navigation with the ability to edit it
     * @param[in] actKey - Symbol (button) pressed by the user
    */
    void action(int actKey) override;

    /**
     * Fully display the page with the table
    */
    void display() override;
protected:
    /**
     * Display information about the selected cell
    */
    void renderHeader() const override;

    /**
     * Display the table
    */
    void renderBody() const override;

    /**
     * Display the table name and auxiliary controls
    */
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
    /**
     * Change the selected cell
     * @param[in] x - Horizontal shift
     * @param[in] y - Vertical shift
    */
    void changePosition(int x, int y);

    /**
     * Display the table markup
    */
    void renderGrid() const;

    /**
     * Additionally highlight the selected cell
    */
    void higlightSelected() const;

    /**
     * Render Rows and Colums title
    */
    void renderRCTitle() const;

    /**
     * Display the values of the cells in the table
    */
    void renderCells() const;

    /**
     * Editing the selected cell
     * @param[in] startY - Starting vertical point in the terminal for entering an expression
     * @param[in] startX - Starting horizontal point in the terminal for entering an expression
    */
    void editCell(unsigned startY, unsigned startX);

    /**
     * A method for converting a horizontal position into the corresponding letter
     * @param[in] num
     * @return Returns the converted number to the corresponding letter
    */
    std::string numToAlpha(int num) const;
};


#endif //PYSAROLE_CINTERFACETABLE_H
