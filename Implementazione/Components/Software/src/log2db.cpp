#include "pgsql.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <string.h>
#include "software.h"

void log2db(Con2DB db1, const char *comp, const char *state)
{
    PGresult *res;
    char sqlcmd[1000];
    char timeString[25];

    // Ottieni la rappresentazione del timestamp attuale.
    timeFlies(timeString);

    // Avvia una transazione nel database.
    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Esegui l'inserimento dei dati della luce nel database.
    sprintf(sqlcmd,
            "INSERT INTO LogDb VALUES ('%s', '%s', '%s') ON CONFLICT DO NOTHING",
            comp,
            state,
            timeString);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Concludi la transazione nel database.
    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}