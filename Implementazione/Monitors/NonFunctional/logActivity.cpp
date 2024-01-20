#include "main.h"
// Definizione della funzione per il logging
void logActivity(Con2DB db1, const char *functionName, int pid)
{
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
    sprintf(sqlcmd, "INSERT INTO LogActivity VALUES (%s, %d, %d) ON CONFLICT DO NOTHING", functionName, localTime, pid);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}