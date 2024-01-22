#include "../../../main/src/global.h"
#include "../../../main/src/main.h"

/* buy stock  */

void log2sensordb(Con2DB db1, int id, int pid, long int nanosec, sensor_type state, bool movement)
{
  int x;
  PGresult *res;
  int rows, k;
  char cstate[20];
  int vid = 0;
  long int dbnanosec, nsafters;
  char datebuf[1000];
  char sqlcmd[1000];

  int2stateSensor(cstate, state);
  if (movement == true)
  {
    x = 1;
  }
  else
  {
    x = 0;
  }

  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd,
          "INSERT INTO Sensor VALUES (%d, '%s', %d, %d, %ld) ON CONFLICT DO NOTHING",
          id,
          cstate,
          x,
          pid,
          nanosec);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

} /*   log2db()  */