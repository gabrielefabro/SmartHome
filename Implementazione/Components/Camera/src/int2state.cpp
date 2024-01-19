#include "../../../main/src/main.h"

/* compute next state  */

void int2stateCamera(char *buf, camera_type x)
{

  if (x == CameraON)
  {
    sprintf(buf, "CameraON");
  }
  else if (x == WAITING)
  {
    sprintf(buf, "Waiting");
  }
  else
  {
    sprintf(buf, "CameraOFF");
  }

} /*   int2color()  */