#include "../../../main/src/main.h"

/* compute next state  */

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

} /*   int2state()  */