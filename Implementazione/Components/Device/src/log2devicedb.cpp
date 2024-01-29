#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

// Funzione per registrare le informazioni di un dispositivo nel database.
void log2devicedb(Con2DB db1, int id, int pid, device_type state, nome_type nome, int t, int inizio, int fine)
{
  // Dichiarazioni di variabili locali
  PGresult *res;
  char cstate[20];
  char sqlcmd[1000];
  char n[20];
  char timeString[25];

  // Converti lo stato del dispositivo in una rappresentazione di stringa.
  int2stateDevice(cstate, state);

  // Converti il nome del dispositivo in una rappresentazione di stringa.
  nomeToString(nome);
  strcpy(n, nomeToString(nome));

  // Ottieni una stringa rappresentante il timestamp corrente.
  timeFlies(timeString);

  // Inizia una transazione nel database PostgreSQL.
  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Esegui l'inserimento dei dati nel database.
  sprintf(sqlcmd,
          "INSERT INTO Device VALUES (%d, %d, '%s', '%s', %d, %d, %d, '%s') ON CONFLICT DO NOTHING",
          t,
          id,
          cstate,
          n,
          inizio,
          fine,
          pid,
          timeString);

  // Esegui il comando SQL e verifica se ci sono conflitti.
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Concludi la transazione nel database PostgreSQL.
  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);
}
