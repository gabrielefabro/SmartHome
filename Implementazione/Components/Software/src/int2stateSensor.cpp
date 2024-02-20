#include "command.h"

// Funzione che inserisce nel buffer la stringa che rappresenta lo stato del Sensore
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
}