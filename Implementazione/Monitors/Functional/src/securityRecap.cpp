#include "../../../main/src/main.h"

void securityRecap(Con2DB db1, int pid, long int nanos) {
    char sqlcmd[100];
    time_t currentTime;
    struct tm localTime;
    PGresult* res;


    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Utilizza la stringa formattata nell'inserimento SQL
    sprintf(sqlcmd, "INSERT INTO SecurityRecap VALUES(%ld , %d) ON CONFLICT DO NOTHING",
                    nanos,
                    pid);


    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}