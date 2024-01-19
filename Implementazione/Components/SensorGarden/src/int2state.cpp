#include "../../../main/src/main.h"

/* compute next state  */

void int2stateSensorGarden(char *buf, sensorGarden_type x)
{

  if (x == SensorGardenON)
  {
    sprintf(buf, "SensorGardenON");
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
    sprintf(buf, "SensorGardenOFF");
  }

} /*   int2state()  */