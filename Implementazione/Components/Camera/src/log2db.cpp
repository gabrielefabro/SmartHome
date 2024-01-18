#include "../../../main/global.h"
#include "../../../main/main.h"

/* buy stock  */

void log2cameradb(Con2DB db1, int id, int pid, long int nanosec, camera_type state, bool recording)
{

  PGresult *res;
  int rows, k;
  char cstate[20];


  int2stateCamera(cstate, state);

  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd,
          "INSERT INTO Camera VALUES (%ld, %d, %d, \'%s\', %d) ON CONFLICT DO NOTHING",
          id,
          cstate,
          recording,
          pid,
          nanosec
          );

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);


} /*   log2db()  */