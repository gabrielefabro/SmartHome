#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

/* buy stock  */

void log2devicedb(Con2DB db1, int id, int pid, long int nanosec, device_type state, nome_type nome, int t)
{
  PGresult *res;
  int rows, k;
  char cstate[20];
  char sqlcmd[1000];
  char n[20];

  int2stateDevice(cstate, state);
  nomeToString(nome);
  strcpy(n, nomeToString(nome));

  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd,
          "INSERT INTO Device VALUES (%d, %d, '%s', '%s', %d, %ld) ON CONFLICT DO NOTHING",
          t,
          id,
          cstate,
          n,
          pid,
          nanosec);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

} /*   log2db()  */