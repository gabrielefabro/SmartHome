#include "light.h"
#include <cstring>


// Funzione per registrare i dati della luce nel database.
void log2lightdb(Con2DB db1, int id, int pid, light_type state, light_color color, int intensity, int64_t tempo_trascorso)
{
    // Dichiarazione di variabili locali per la gestione dei risultati delle query.
    PGresult *res;
    char cstate[20];
    char c[20];
    char sqlcmd[1000];
    char timeString[25];

    // Converti lo stato numerico della luce in una stringa descrittiva.
    int2stateLight(cstate, state);

    // Ottieni la rappresentazione di stringa del colore della luce.
    strcpy(c, colorToString(color));

    // Ottieni la rappresentazione del timestamp attuale.
    timeFlies(timeString);

    // Avvia una transazione nel database.
    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Esegui l'inserimento dei dati della luce nel database.
    sprintf(sqlcmd,
            "INSERT INTO Light VALUES (%ld, %d, '%s', '%s', %d, %d, '%s') ON CONFLICT DO NOTHING",
            tempo_trascorso,
            id,
            cstate,
            c,
            intensity,
            pid,
            timeString);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Concludi la transazione nel database.
    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}
