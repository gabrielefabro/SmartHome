#include "main.h"

/* compute next state  */

void int2state(char *buf, sensor_type x)
{

  if (x == ON)
  {
    sprintf(buf, "ON");
  }
  else if (x == OFF)
  {
    sprintf(buf, "OFF");
  }
  else
  {
    sprintf(buf, "CHECKING");
  }

} /*   int2state()  */