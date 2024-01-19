#include "../../../main/src/main.h"

/* compute next state  */

void int2stateDevice(char *buf, device_type x)
{

  if (x == ON)
  {
    sprintf(buf, "ON");
  }
  else if (x == OFF)
  {
    sprintf(buf, "OFF");
  }
  else if (x == programmed)
  {
    sprintf(buf, "change_intensity");
  }
  else
  {
    sprintf(buf, "change_color");
  }

} 