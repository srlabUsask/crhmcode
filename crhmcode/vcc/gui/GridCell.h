#pragma once

#include <afxwin.h>
#include "../../src/core/ClassPar.h"

/**
* Extension of CEdit that changes colour when the value is changed from that of the assocated parameter.
*/
class GridCell : public CEdit
{
public:

    /**
    * Constructor
    * 
    * @param par - ClassPar* The parameter associated with this cell
    * @param row - int the row of the value associated with this cell
    * @param col - int the column of the value associated with this cell
    */
    GridCell(ClassPar* par, int row, int col);

    /**
    * Sets the internal colour value for the cell to yellow.
    */
    void setColourToYellow();

private:

    /**
    * Reference to the current color of the cell background
    */
    COLORREF currentColour;

    /**
    * Reference to black color
    */
    COLORREF black;

    /**
    * Reference to white color
    */
    COLORREF white;

    /**
    * Refference to yellow color
    */
    COLORREF yellow;

    /**
    * Brush to change the background color to white
    */
    CBrush background_brush_white;

    /**
    * Brush to change the background color to yellow
    */
    CBrush background_brush_yellow;

    /**
    * Reference to the parameter associated with this grid cell
    */
    ClassPar * param;

    /**
    * The row of the value associated with this cell
    */
    int row;

    /**
    * The column of the value associated with this cell
    */
    int col;

    /**
    * Reflected message handler that triggers when the cell's color is about to be rendered.
    * 
    * @return HBRUSH - safe handler for a brush to use when rendering the cells background colour.
    */
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

    /**
    * Calculates the colour that should be used for this cell based on its current value 
    * and the value from the assocated parameter. 
    * 
    * If the value has changed from that stored in the parameter the cell should render with yellow background
    * or white otherwise.
    * 
    * @return COLORREF - reference to the colour the cell should be set two.
    */
    COLORREF calculateColour();

    DECLARE_MESSAGE_MAP()
};

