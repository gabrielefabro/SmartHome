#include "main.h"

nome_type stringToNome(const char* nomeDev)
{

  if (strcmp(colorStr, "TV") == 0)
  {
    return TV;
  }
  else if (strcmp(colorStr, "DISHWASHER") == 0)
  {
    return DISHWASHER;
  }
  else if (strcmp(colorStr, "WASHING_MACHINE") == 0)
  {
    return WASHING_MACHINE;
  }
  else if (strcmp(colorStr, "COFFEE_MAKER") == 0)
  {
    return COFFEE_MAKER;
  }
  else if (strcmp(colorStr, "MICROWAVE") == 0)
  {
    return MICROWAVE;
  }
  else if (strcmp(colorStr, "HEATED_BLANKETS") == 0)
  {
    return HEATED_BLANKETS;
  }
  else if (strcmp(colorStr, "SPEAKERS") == 0)
  {
    return SPEAKERS;
  }
  else
  {
    return LAWN_MOWER;
  }

}