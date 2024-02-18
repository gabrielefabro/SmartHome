#include "sensorGarden.h"

// Funzione che inserisce nel buffer la stringa che rappresenta lo stato del SensoreGiardino
void int2stateSensorGarden(char *buf, sensorGarden_type x)
{

  if (x == SensorGardenON)
  {
    sprintf(buf, "SensorGardenON");
  }
  else
  {
    sprintf(buf, "SensorGardenOFF");
  }

}