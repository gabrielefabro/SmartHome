#include "main.h"

/* buy stock  */

void log2db(Con2DB db1, int pid, long int nanosec, conditioner_type state, int temperature)
{

    PGresult *res;
    int rows, k;
    char cstate[20];
    int vid = 0;
    long int dbnanosec, nsafters;
    char datebuf[1000];

    int2state(cstate, state);

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'state\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    vid = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);

    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
            "INSERT INTO LogTable VALUES (%ld, %d, %d, \'%s\', %d) ON CONFLICT DO NOTHING",
            nanosec,
            vid,
            state,
            cstate,
            temperature);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

} /*   log2db()  */