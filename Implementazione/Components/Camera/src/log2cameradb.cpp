#include "camera.h"

// Funzione per registrare informazioni sulla telecamera in un database PostgreSQL.
void log2cameradb(Con2DB db1, int id, int pid, camera_type state, bool recording, int64_t tempo_trascorso)
{
  int x;
  PGresult *res;
  char cstate[20];
  char sqlcmd[1000];
  char timeString[25];

  // Converti lo stato della telecamera in formato stringa.
  int2stateCamera(cstate, state);

  // Imposta x in base allo stato della registrazione per inserirlo nel database.
  x = recording ? 1 : 0;

  // Ottieni la rappresentazione di stringa del timestamp corrente.
  timeFlies(timeString);

  // Inizia una transazione SQL.
  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Crea e esegui un comando SQL per inserire informazioni sulla telecamera nella tabella "Camera" del database.
  sprintf(sqlcmd,
          "INSERT INTO Camera VALUES (%ld, %d, '%s', %d, %d, '%s') ON CONFLICT DO NOTHING",
          tempo_trascorso,
          id,
          cstate,
          x,
          pid,
          timeString);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Concludi la transazione SQL.
  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);
}
