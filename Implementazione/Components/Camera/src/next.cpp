#include "main.h"

/* compute next state  */

camera_type next(camera_type x)
{

  return ((camera_type) ((x + rand()%2)%3));
  
}  /*   next()  */