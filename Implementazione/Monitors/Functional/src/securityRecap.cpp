#include <ctime>
#include "../../../con2db/src/pgsql.h"


// Monitor per il requisito funzionale per registrare un riassunto di sicurezza nel database
void securityRecap(Con2DB db1, int pid)
{
    char sqlcmd[100];
    time_t currentTime;
    struct tm localTime;
    PGresult *res;
    char timeString[20];

    // Ottieni l'orario attuale
    //timeFlies(timeString);

    // Inizia una transazione SQL
    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Utilizza la stringa formattata nell'inserimento SQL
    sprintf(sqlcmd, "INSERT INTO SecurityRecap VALUES('%s', %d) ON CONFLICT DO NOTHING",
            timeString,
            pid);

    // Esegui la query SQL
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Concludi la transazione SQL
    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}
