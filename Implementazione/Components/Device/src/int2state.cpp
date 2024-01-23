#include "../../../main/src/main.h"

/* compute next state  */

void int2stateDevice(char *buf, device_type x)
{

  if (x == DeviceON)
  {
    sprintf(buf, "DeviceON");
  }
  else if (x == DeviceOFF)
  {
    sprintf(buf, "DeviceOFF");
  }
  else if (x == programmed)
  {
    sprintf(buf, "programmed");
  }

} 