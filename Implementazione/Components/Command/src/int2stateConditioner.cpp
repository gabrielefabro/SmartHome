#include "command.h"

// Funzione che inserisce in un buffer la stringa che rappresenta lo stato dell'oggetto condizionatore
void int2stateConditioner(char *buf, conditioner_type x)
{

  if (x == ConditionerON)
  {
    sprintf(buf, "ConditionerON");
  }
  else if (x == ConditionerOFF)
  {
    sprintf(buf, "ConditionerOFF");
  }
  else
  {
    sprintf(buf, "change_temperature");
  }

}