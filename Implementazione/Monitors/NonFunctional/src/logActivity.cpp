#include "../../../main/src/main.h"

// Definizione della funzione per il logging
void logActivity(Con2DB db1, const char *functionName, int pid)
{
    char sqlcmd[200]; // Aumentato la dimensione dell'array per gestire la stringa SQL più lunga
    PGresult *res;
    char timeString[25];

    timeFlies(timeString);

    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Utilizza la stringa formattata nell'inserimento SQL
    sprintf(sqlcmd, "INSERT INTO LogActivity VALUES ('%s', '%s', %d) ON CONFLICT DO NOTHING", functionName, timeString, pid);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}
