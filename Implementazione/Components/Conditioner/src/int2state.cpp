#include "main.h"

/* compute next state  */

void int2state(char *buf, conditioner_type x)
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
    sprintf(buf, "change_temperature");
  }

} /*   int2color()  */