#include "../../../main/src/global.h"
#include "../../../main/src/main.h"

/* buy stock  */

void log2cameradb(Con2DB db1, int id, int pid, camera_type state, bool recording, int t)
{
  int x;
  PGresult *res;
  int rows, k;
  char cstate[20];
  char sqlcmd[1000];
  char timeString[25];

  int2stateCamera(cstate, state);
  if (recording == true)
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
          "INSERT INTO Camera VALUES (%d, %d, '%s', %d, %d, '%s') ON CONFLICT DO NOTHING",
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