#include "../../../main/src/main.h"

/* compute next state  */

void int2stateSensor(char *buf, sensor_type x)
{

  if (x == SensorON)
  {
    sprintf(buf, "SensorON");
  }
  else if (x == SensorOFF)
  {
    sprintf(buf, "SensorOFF");
  }
  else
  {
    sprintf(buf, "CHECKING");
  }

} /*   int2state()  */