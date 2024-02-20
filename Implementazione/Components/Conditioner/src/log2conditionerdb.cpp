#include "conditioner.h"
#include "../../../con2db/src/pgsql.h"

// Funzione per registrare informazioni sul condizionatore in un database PostgreSQL.
void log2conditionerdb(Con2DB db1, int id, int pid, conditioner_type state, int temperature, int64_t tempo_trascorso)
{
    PGresult *res;
    char cstate[20];
    char sqlcmd[1000];
    char timeString[25];

    // Converti lo stato del condizionatore in una rappresentazione di stringa.
    int2stateConditioner(cstate, state);

    // Ottieni la rappresentazione di stringa del timestamp corrente.
    timeFlies(timeString);

    // Inizia una transazione SQL.
    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Crea e esegui un comando SQL per inserire informazioni sul condizionatore nella tabella "Conditioner" del database.
    sprintf(sqlcmd,
            "INSERT INTO Conditioner VALUES ( %ld, %d, '%s', %d, %d, '%s') ON CONFLICT DO NOTHING",
            tempo_trascorso,
            id,
            cstate,
            temperature,
            pid,
            timeString);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Concludi la transazione SQL.
    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}
