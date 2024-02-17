#include "../../../main/src/main.h"

// Funzione che inserisce in un buffer la stringa che rappresenta lo stato dell'oggetto camera
void int2stateCamera(char *buf, camera_type x)
{

  if (x == CameraON)
  {
    sprintf(buf, "CameraON");
  }
  else
  {
    sprintf(buf, "CameraOFF");
  }
}