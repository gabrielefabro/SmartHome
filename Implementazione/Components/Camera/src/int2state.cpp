#include "../../../main/src/main.h"

/* compute next state  */

void int2stateCamera(char *buf, camera_type x)
{

  if (x == ON)
  {
    sprintf(buf, "ON");
  }
  else if (x == WAITING)
  {
    sprintf(buf, "Waiting");
  }
  else
  {
    sprintf(buf, "OFF");
  }

} /*   int2color()  */