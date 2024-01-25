#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

/* buy stock  */

void log2sensorGardendb(Con2DB db1, int id, int pid, long int nanosec, sensorGarden_type state, int humidity, int temperature, int t)
{

  PGresult *res;
  char cstate[20];
  char sqlcmd[1000];
  char descr[20];

  int2stateSensorGarden(cstate, state);

  if (strcmp(cstate, "change_light") == 0)
  {

    // Adjust the lights based on humidity and temperature conditions
    if (humidity > 50 && temperature > 25)
    {
      std::cout << "luci spente" << std::endl;
      sprintf(descr, "luci_spente");
    }
    else
    {
      std::cout << "luci accese" << std::endl;
      sprintf(descr, "luci_accese");
    }
  }
  else if (strcmp(cstate, "set_sprinklers") == 0)
  {
    // Adjust irrigation based on humidity conditions
    if (humidity < 30)
    {
      std::cout << "irrigatori accese" << std::endl;
      sprintf(descr, "irrigatori_accesi");
    }
    else
    {
      std::cout << "irrigatori spenti" << std::endl;
      sprintf(descr, "irrigatori_spenti");
    }
  }
  else{
    sprintf(descr, "nothing_happened");
  }

  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd,
          "INSERT INTO SensorGarden VALUES (%d, %d, '%s', %d, %d, '%s', %d, %ld) ON CONFLICT DO NOTHING",
          t,
          id,
          cstate,
          temperature,
          humidity,
          descr,
          pid,
          nanosec);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

} /*   log2db()  */