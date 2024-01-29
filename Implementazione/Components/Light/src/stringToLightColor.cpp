#include "../../../main/src/main.h"

// Funzione che inserisce nel buffer la stringa che rappresenta il colore della luce
light_color stringToLightColor(const char* colorStr)
{

  if (strcmp(colorStr, "RED") == 0)
  {
    return RED;
  }
  else if (strcmp(colorStr, "BLUE") == 0)
  {
    return BLUE;
  }
  else if (strcmp(colorStr, "YELLOW") == 0)
  {
    return YELLOW;
  }
  else if (strcmp(colorStr, "PINK") == 0)
  {
    return PINK;
  }
  else if (strcmp(colorStr, "ORANGE") == 0)
  {
    return ORANGE;
  }
  else if (strcmp(colorStr, "WHITE") == 0)
  {
    return WHITE;
  }
  else
  {
    return PURPLE;
  }

}