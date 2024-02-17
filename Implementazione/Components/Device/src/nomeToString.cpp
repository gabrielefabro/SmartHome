#include "device.h"

// Funzione che ritorna la stringa rappresentate il nome del device passato come argomento
const char* nomeToString(nome_type nomeDev)
{
  switch (nomeDev)
  {
    case TV:
      return "TV";
    case DISHWASHER:
      return "DISHWASHER";
    case WASHING_MACHINE:
      return "WASHING_MACHINE";
    case COFFEE_MAKER:
      return "COFFEE_MAKER";
    case MICROWAVE:
      return "MICROWAVE";
    case HEATED_BLANKETS:
      return "HEATED_BLANKETS";
    case SPEAKERS:
      return "SPEAKERS";
    case LAWN_MOWER:
      return "LAWN_MOWER";
    default:
      return "UNKNOWN_DEVICE";
  }
}
