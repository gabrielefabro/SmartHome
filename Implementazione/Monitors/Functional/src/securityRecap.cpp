#include "../../../main/src/main.h"

void securityRecap(Con2DB db1, int pid)
{
    char sqlcmd[100];
    time_t currentTime;
    struct tm localTime;
    PGresult *res;
    char timeString[20];

    timeFlies(timeString);

    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Utilizza la stringa formattata nell'inserimento SQL
    sprintf(sqlcmd, "INSERT INTO SecurityRecap VALUES('%s' , %d) ON CONFLICT DO NOTHING",
            timeString,
            pid);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}