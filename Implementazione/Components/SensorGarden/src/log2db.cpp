#include "../../../main/main.h"

/* buy stock  */

void log2sensorGardendb(Con2DB db1, int id, int pid, long int nanosec, sensorGarden_type state, int humidity, int temperature)
{

  PGresult *res;
  int rows, k;
  char cstate[20];

  int2stateSensorGarden(cstate, state);

  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd,
          "INSERT INTO LogTable VALUES (%d, %s, %d, %d, %d, %ld) ON CONFLICT DO NOTHING",
          id,
          cstate,
          temperature,
          humidity,
          pid,
          nanosec);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

} /*   log2db()  */