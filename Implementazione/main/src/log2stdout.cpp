#include "main.h"
#include "global.h"

void log2stdout(Con2DB db1, int pid)
{

  PGresult *res;
  int rows, k;
  char cstate[20];
  long int dbnanosec, nsafters;
  char datebuf[1000];
  char sqlcmd[1000];

  sprintf(sqlcmd, "SELECT * FROM Camera where (pid = %d)", pid);
  sprintf(sqlcmd, "SELECT * FROM Conditioner where (pid = %d)", pid);
  sprintf(sqlcmd, "SELECT * FROM Device where (pid = %d)", pid);
  sprintf(sqlcmd, "SELECT * FROM Light where (pid = %d)", pid);
  sprintf(sqlcmd, "SELECT * FROM Sensor where (pid = %d)", pid);
  sprintf(sqlcmd, "SELECT * FROM SensorGarden where (pid = %d)", pid);
    sprintf(sqlcmd, "SELECT * FROM LogActivity where (pid = %d)", pid);


  res = db1.ExecSQLtuples(sqlcmd);
  rows = PQntuples(res);
  PQclear(res);

} /*   log2stdout()  */