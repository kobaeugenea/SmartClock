#ifndef KEA_SC_2X4MAX7219DISAPLYC_H
#define KEA_SC_2X4MAX7219DISAPLYC_H

#include "component/display/kea_sc_DisplayC.h"

kea_sc_DisplayC_Id kea_sc_Display2x4Max7219C_init(kea_sc_ComponentS_Id componentsId);
void kea_sc_Display2x4Max7219C_displayDate(kea_sc_ComponentS_Id componentsId, kea_sc_DateS_Date date);

#endif