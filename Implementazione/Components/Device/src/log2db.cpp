#include "../../../main/main.h"

/* buy stock  */

void log2devicedb(Con2DB db1, int id, int pid, long int nanosec, device_type state, nome_type nome)
{

  PGresult *res;
  int rows, k;
  char cstate[20];

  int2stateDevice(cstate, state);

  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd,
          "INSERT INTO LogTable VALUES (%d, %s, %s, %d, %ld) ON CONFLICT DO NOTHING",
          id,
          cstate,
          nome,
          pid,
          nanosec);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

} /*   log2db()  */