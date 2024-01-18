#include "../../../main/global.h"
#include "../../../main/main.h"

/* buy stock  */

void log2sensordb(Con2DB db1, int id, int pid, long int nanosec, sensor_type state, bool movement)
{

  PGresult *res;
  int rows, k;
  char cstate[20];
  int vid = 0;
  long int dbnanosec, nsafters;
  char datebuf[1000];

  int2stateSensor(cstate, state);

  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd,
          "INSERT INTO LogTable VALUES (%ld, %d, %d, \'%s\', %d) ON CONFLICT DO NOTHING",
          id,
          cstate,
          movement,
          pid,
          nanosec);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

} /*   log2db()  */