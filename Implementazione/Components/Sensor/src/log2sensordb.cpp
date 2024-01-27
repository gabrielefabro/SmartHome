#include "../../../main/src/global.h"
#include "../../../main/src/main.h"

/* buy stock  */

void log2sensordb(Con2DB db1, int id, int pid, sensor_type state, bool movement, int t)
{
  int x;
  PGresult *res;
  char cstate[20];
  char sqlcmd[1000];
  char timeString[25];

  int2stateSensor(cstate, state);
  if (movement == true)
  {
    x = 1;
  }
  else
  {
    x = 0;
  }

  timeFlies(timeString);

  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd,
          "INSERT INTO Sensor VALUES (%d, %d, '%s', %d, %d, '%s') ON CONFLICT DO NOTHING",
          t,
          id,
          cstate,
          x,
          pid,
          timeString);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

} /*   log2db()  */