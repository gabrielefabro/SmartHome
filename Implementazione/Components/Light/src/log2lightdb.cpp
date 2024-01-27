#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

void log2lightdb(Con2DB db1, int id, int pid, light_type state, light_color color, int intensity, int t)
{

  PGresult *res;
  int rows, k;
  char cstate[20];
  char sqlcmd[1000];
  char c[20];
  char timeString[25];

  int2stateLight(cstate, state);
  timeFlies(timeString);
  strcpy(c, colorToString(color));

  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd,
          "INSERT INTO Light VALUES (%d, %d, '%s', '%s', %d, %d, '%s') ON CONFLICT DO NOTHING",
          t,
          id,
          cstate,
          c,
          intensity,
          pid,
          timeString);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

} /*   log2db()  */