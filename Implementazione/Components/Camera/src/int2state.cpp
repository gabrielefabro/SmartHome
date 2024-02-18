#include "camera.h"
<<<<<<< HEAD
#include <cstdio>

=======
>>>>>>> fb0c8a55095d71fc9ac088a9472b5b9a211a07d2
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