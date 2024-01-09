#include "main.h"

/* compute next state  */

void int2state(char *buf, sensorGarden_type x)
{

  if (x == ON)
  {
    sprintf(buf, "ON");
  }
  else if (x == change_light)
  {
    sprintf(buf, "change_light");
  }
  else if (x == set_sprinklers)
  {
    sprintf(buf, "set_sprinklers");
  }
  else
  {
    sprintf(buf, "OFF");
  }

} /*   int2state()  */