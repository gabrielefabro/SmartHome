#include "../../../main/src/main.h"

// Definizione della funzione per il logging delle attività
void logActivity(Con2DB db1, const char *functionName, int pid)
{
    char sqlcmd[200]; // Dimensione dell'array aumentata per gestire la stringa SQL più lunga
    PGresult *res;
    char timeString[25];

    // Ottieni la stringa formattata per l'orario attuale
    timeFlies(timeString);

    // Inizia una transazione SQL
    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Utilizza la stringa formattata per l'inserimento SQL
    sprintf(sqlcmd, "INSERT INTO LogActivity VALUES ('%s', '%s', %d) ON CONFLICT DO NOTHING", functionName, timeString, pid);

    // Esegui la query SQL
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Concludi la transazione SQL
    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}
