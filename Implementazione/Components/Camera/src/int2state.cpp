#include "main.h"

/* compute next state  */

void int2state(char *buf, camera_type x)
{

  if (x == ON)
    {sprintf(buf, "ON");}
  else if (x == RECORDING)
    {sprintf(buf, "Recording");}
  else
    {sprintf(buf, "OFF");}
  

}  /*   int2color()  */