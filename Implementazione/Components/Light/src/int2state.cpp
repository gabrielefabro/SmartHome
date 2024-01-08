#include "main.h"

/* compute next state  */

void int2state(char *buf, light_type x)
{

  if (x == ON)
  {
    sprintf(buf, "ON");
  }
  else if (x == OFF)
  {
    sprintf(buf, "OFF");
  }
  else if (x == change_intensity)
  {
    sprintf(buf, "change_intensity");
  }
  else
  {
    sprintf(buf, "change_color");
  }

} /*   int2color()  */