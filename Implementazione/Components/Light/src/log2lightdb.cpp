#include "../../../main/src/main.h"
#include "../../../main/src/global.h"


void log2lightdb(Con2DB db1, int id, int pid, long int nanosec, light_type state, light_color color, int intensity)
{

  PGresult *res;
  int rows, k;
  char cstate[20];
  char sqlcmd[1000];

  int2stateLight(cstate, state);

  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd,
          "INSERT INTO Light VALUES (%d, %s, %s, %d, %d, %ld) ON CONFLICT DO NOTHING",
          id,
          cstate,
          color,
          intensity,
          pid,
          nanosec);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

} /*   log2db()  */