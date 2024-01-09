#include "main.h"

nome_type stringToNome(const char* nomeDev)
{

  if (strcmp(nomeDev, "TV") == 0)
  {
    return TV;
  }
  else if (strcmp(nomeDev, "DISHWASHER") == 0)
  {
    return DISHWASHER;
  }
  else if (strcmp(nomeDev, "WASHING_MACHINE") == 0)
  {
    return WASHING_MACHINE;
  }
  else if (strcmp(nomeDev, "COFFEE_MAKER") == 0)
  {
    return COFFEE_MAKER;
  }
  else if (strcmp(nomeDev, "MICROWAVE") == 0)
  {
    return MICROWAVE;
  }
  else if (strcmp(nomeDev, "HEATED_BLANKETS") == 0)
  {
    return HEATED_BLANKETS;
  }
  else if (strcmp(nomeDev, "SPEAKERS") == 0)
  {
    return SPEAKERS;
  }
  else
  {
    return LAWN_MOWER;
  }

}