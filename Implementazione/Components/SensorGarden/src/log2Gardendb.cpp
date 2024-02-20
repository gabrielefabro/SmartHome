#include <ctime>
#include "sensorGarden.h"

void log2Gardendb(Con2DB db1, char *messaggio, int64_t tempo_trascorso, int id,  int humidity, int temperature)
{
    char timeString[25];
    char sqlcmd[1000];
    PGresult *res;
    
    // Inizia una transazione nel database
    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Ottiene la data e l'ora correnti
    timeFlies(timeString);

    // Inserisce i dati nel database
    sprintf(sqlcmd,
            "INSERT INTO Garden VALUES (%ld, %d, %d, %d, '%s', '%s') ON CONFLICT DO NOTHING",
            tempo_trascorso,
            id,
            temperature,
            humidity,
            messaggio,
            timeString);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Conclude la transazione nel database
    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}