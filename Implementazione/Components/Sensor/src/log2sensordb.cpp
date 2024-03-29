#include "sensor.h"


// Funzione per registrare i dati di un sensore nel database.
void log2sensordb(Con2DB db1, int id, int pid, sensor_type state, bool check, int64_t tempo_trascorso)
{
  int x;
  PGresult *res;
  char cstate[20];
  char sqlcmd[1000];
  char timeString[25];

  // Converti lo stato numerico del sensore in una stringa descrittiva.
  int2stateSensor(cstate, state);

  // Converte il flag di movimento in una variabile numerica (0 o 1).
  x = check ? 1 : 0;

  // Ottieni il timestamp corrente come stringa.
  timeFlies(timeString);

  // Inizia una transazione nel database.
  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Inserisce i dati del sensore nel database.
  sprintf(sqlcmd,
          "INSERT INTO Sensor VALUES (%ld, %d, '%s', %d, %d, '%s') ON CONFLICT DO NOTHING",
          tempo_trascorso,
          id,
          cstate,
          x,
          pid,
          timeString);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Concludi la transazione nel database.
  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);
}
