#include "../../../main/src/main.h"

/* compute next state  */

void int2stateLight(char *buf, light_type x)
{

  if (x == LightON)
  {
    sprintf(buf, "LightON");
  }
  else if (x == LightOFF)
  {
    sprintf(buf, "LightOFF");
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