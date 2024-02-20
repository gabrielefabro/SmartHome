#include "command.h"

// Funzione che inserisce in un buffer la stringa che rappresenta lo stato dell'oggetto Dispositivo
void int2stateDevice(char *buf, device_type x)
{
  if (x == DeviceON)
  {
    sprintf(buf, "DeviceON");
  }
  else if (x == DeviceOFF)
  {
    sprintf(buf, "DeviceOFF");
  }
  else if (x == programmed)
  {
    sprintf(buf, "programmed");
  }
}