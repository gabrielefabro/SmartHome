#include "main.h"

/* buy stock  */

void init_logdb(Con2DB db1, int pid, int id, conditioner_type state)
{

    PGresult *res;
    int rows, k;

    /*  init  */

    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
            "INSERT INTO Timevar VALUES (%d, %d, \'%s\', \'%d\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
            id, pid, "Conditioner", state, "discrete", "Values: ON, CHANGE_TEMPERATURE, OFF");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

} /*   init_logdb()  */