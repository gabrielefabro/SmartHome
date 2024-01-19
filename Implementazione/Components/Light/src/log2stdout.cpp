#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

void log2stdout(Con2DB db1, int pid)
{

  PGresult *res;
  int rows, k;
  char cstate[20];
  int id = 0;
  long int dbnanosec, nsafters;
  char datebuf[1000];

  /* prg */

  sprintf(sqlcmd,
          "SELECT id FROM TimeVar where ((pid = %d) AND (varname = \'x\'))", pid);
  res = db1.ExecSQLtuples(sqlcmd);
  id = atoi(PQgetvalue(res, 0, PQfnumber(res, "id")));
  PQclear(res);

  

  res = db1.ExecSQLtuples(sqlcmd);
  rows = PQntuples(res);

  for (k = 0; k < rows; k++)
  {

    /* string to long int  */
    dbnanosec = strtol(PQgetvalue(res, k, PQfnumber(res, "nanosec")), NULL, 10);
    nsafters = nanos2day(datebuf, dbnanosec);

    fprintf(stderr,
            "log2stdout(): LogTable (%ld, %d, %d, \'%s\') TIME_UTC = %s + %ld ns\n",
            dbnanosec,
            atoi(PQgetvalue(res, k, PQfnumber(res, "id"))),
            atoi(PQgetvalue(res, k, PQfnumber(res, "varvalue"))),
            PQgetvalue(res, k, PQfnumber(res, "loginfo")),
            datebuf, nsafters);
  }

  PQclear(res);

} /*   log2stdout()  */