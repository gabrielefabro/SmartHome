#include "main.h"

/* buy stock  */

void log2db(Con2DB db1, int pid, long int nanosec, camera_type state, bool recording)
{

  PGresult *res;
  int rows, k;
  char cstate[20];
  int vid = 0;
  long int dbnanosec, nsafters;
  char datebuf[1000];

  int2state(cstate, state);

#if (DEBUG > 1000000)
  fprintf(stderr, "log2db(): pid = %d, varname = %s\n", pid, "state");
#endif

  sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'state\'))", pid);
  res = db1.ExecSQLtuples(sqlcmd);
  vid = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
  PQclear(res);

#if (DEBUG > 1000000)
  fprintf(stderr, "log2db(): vid = %d\n", vid);
#endif

  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd,
          "INSERT INTO LogTable VALUES (%ld, %d, %d, \'%s\', %s) ON CONFLICT DO NOTHING",
          nanosec,
          vid,
          state,
          cstate,
          recording);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

#if (DEBUG > 0)

  // fprintf(stderr, "log2db(): check insertion\n");

  sprintf(sqlcmd, "SELECT * FROM LogTable where (nanosec = %ld)", nanosec);

  res = db1.ExecSQLtuples(sqlcmd);
  rows = PQntuples(res);

  dbnanosec = strtol(PQgetvalue(res, 0, PQfnumber(res, "nanosec")), NULL, 10);

  fprintf(stderr, "log2db(): inserted in LogTable (%ld, %d, %d, \'%s\')\n",
          dbnanosec,
          atoi(PQgetvalue(res, 0, PQfnumber(res, "vid"))),
          atoi(PQgetvalue(res, 0, PQfnumber(res, "varvalue"))),
          PQgetvalue(res, 0, PQfnumber(res, "loginfo")));
  PQclear(res);

  nsafters = nanos2day(datebuf, dbnanosec);

  fprintf(stderr, "log2db(): ns = %ld = TIME_UTC = %s + %ld ns\n", dbnanosec, datebuf, nsafters);
#endif

} /*   log2db()  */