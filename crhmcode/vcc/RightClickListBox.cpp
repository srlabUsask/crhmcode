#include "RightClickListBox.h"
#include "../src/core/InstrumentLogger.h"

BEGIN_MESSAGE_MAP (RightClickListBox, CListBox)
    ON_WM_RBUTTONDOWN ()
END_MESSAGE_MAP ()

UINT RightClickListBox :: getMessageCode ()
{
InstrumentLogger::instance()->log_instrument_log("<RightClickListBox::getMessageCode()@@@RightClickListBox.cpp>");

InstrumentLogger::instance()->log_instrument_log("</RightClickListBox::getMessageCode()@@@RightClickListBox.cpp>");
    return this -> messageCode;
InstrumentLogger::instance()->log_instrument_log("</RightClickListBox::getMessageCode()@@@RightClickListBox.cpp>");
}
void RightClickListBox :: setMessageCode (UINT code)
{
InstrumentLogger::instance()->log_instrument_log("<RightClickListBox::setMessageCode(UINT code)@@@RightClickListBox.cpp>");
    this -> messageCode = code;
InstrumentLogger::instance()->log_instrument_log("</RightClickListBox::setMessageCode(UINT code)@@@RightClickListBox.cpp>");
}
void RightClickListBox :: OnRButtonDown (UINT nFlags, CPoint point)
{
InstrumentLogger::instance()->log_instrument_log("<RightClickListBox::OnRButtonDown(UINT nFlags, CPoint point)@@@RightClickListBox.cpp>");
    GetParent () -> SendMessage (this -> messageCode, nFlags, 0);
    CListBox :: OnRButtonDown (nFlags, point);
InstrumentLogger::instance()->log_instrument_log("</RightClickListBox::OnRButtonDown(UINT nFlags, CPoint point)@@@RightClickListBox.cpp>");
}