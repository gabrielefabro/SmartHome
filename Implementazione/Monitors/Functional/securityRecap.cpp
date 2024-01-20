#include "main.h"
void securityRecap(Con2DB db1, int pid) {
    char sqlcmd[100];
    time_t currentTime;
    struct tm *localTime;
    PGresult *res;

    // Ottenere l'orario corrente
    time(&currentTime);
    localTime = localtime(&currentTime);
    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
    sprintf(sqlcmd, "INSERT INTO SecurityRecap VALUES (%d, %d) ON CONFLICT DO NOTHING", localTime, pid);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}