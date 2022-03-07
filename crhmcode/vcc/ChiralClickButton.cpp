#include "ChiralClickButton.h"
#include "../src/core/InstrumentLogger.h"

BEGIN_MESSAGE_MAP (ChiralClickButton, CButton)
    ON_WM_LBUTTONDOWN ()
    ON_WM_RBUTTONDOWN ()
END_MESSAGE_MAP ()

UINT ChiralClickButton :: getMessageCodeLeft ()
{
InstrumentLogger::instance()->log_instrument_log("<ChiralClickButton::getMessageCodeLeft()@@@ChiralClickButton.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ChiralClickButton::getMessageCodeLeft()@@@ChiralClickButton.cpp>");
    return this -> messageCodeLeft;
InstrumentLogger::instance()->log_instrument_log("</ChiralClickButton::getMessageCodeLeft()@@@ChiralClickButton.cpp>");
}
void ChiralClickButton :: setMessageCodeLeft (UINT code)
{
InstrumentLogger::instance()->log_instrument_log("<ChiralClickButton::setMessageCodeLeft(UINT code)@@@ChiralClickButton.cpp>");
    this -> messageCodeLeft = code;
InstrumentLogger::instance()->log_instrument_log("</ChiralClickButton::setMessageCodeLeft(UINT code)@@@ChiralClickButton.cpp>");
}
UINT ChiralClickButton :: getMessageCodeRight ()
{
InstrumentLogger::instance()->log_instrument_log("<ChiralClickButton::getMessageCodeRight()@@@ChiralClickButton.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ChiralClickButton::getMessageCodeRight()@@@ChiralClickButton.cpp>");
    return this -> messageCodeRight;
InstrumentLogger::instance()->log_instrument_log("</ChiralClickButton::getMessageCodeRight()@@@ChiralClickButton.cpp>");
}
void ChiralClickButton :: setMessageCodeRight (UINT code)
{
InstrumentLogger::instance()->log_instrument_log("<ChiralClickButton::setMessageCodeRight(UINT code)@@@ChiralClickButton.cpp>");
    this -> messageCodeRight = code;
InstrumentLogger::instance()->log_instrument_log("</ChiralClickButton::setMessageCodeRight(UINT code)@@@ChiralClickButton.cpp>");
}
void ChiralClickButton :: OnLButtonDown (UINT nFlags, CPoint point)
{
InstrumentLogger::instance()->log_instrument_log("<ChiralClickButton::OnLButtonDown(UINT nFlags, CPoint point)@@@ChiralClickButton.cpp>");
    GetParent () -> SendMessage (this -> messageCodeLeft, nFlags, 0);
    CButton :: OnRButtonDown (nFlags, point);
InstrumentLogger::instance()->log_instrument_log("</ChiralClickButton::OnLButtonDown(UINT nFlags, CPoint point)@@@ChiralClickButton.cpp>");
}
void ChiralClickButton :: OnRButtonDown (UINT nFlags, CPoint point)
{
InstrumentLogger::instance()->log_instrument_log("<ChiralClickButton::OnRButtonDown(UINT nFlags, CPoint point)@@@ChiralClickButton.cpp>");
    GetParent () -> SendMessage (this -> messageCodeRight, nFlags, 0);
    CButton :: OnRButtonDown (nFlags, point);
InstrumentLogger::instance()->log_instrument_log("</ChiralClickButton::OnRButtonDown(UINT nFlags, CPoint point)@@@ChiralClickButton.cpp>");
}