#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

/* buy stock  */

void log2conditionerdb(Con2DB db1, int id, int pid, long int nanosec, conditioner_type state, int temperature, int t)
{

    PGresult *res;
    int rows, k;
    char cstate[20];
    char sqlcmd[1000];

    int2stateConditioner(cstate, state);

    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
            "INSERT INTO Conditioner VALUES (%d, %d, '%s', %d, %d, %ld) ON CONFLICT DO NOTHING",
            t,
            id,
            cstate,
            temperature,
            pid,
            nanosec);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

} /*   log2db()  */