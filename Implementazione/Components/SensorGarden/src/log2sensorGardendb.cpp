#include "sensorGarden.h"
#include <cstring>

// Funzione per registrare i dati del sensore da giardino nel database
void log2sensorGardendb(Con2DB db1, int id, int pid, sensorGarden_type state, int humidity, int temperature, int64_t tempo_trascorso)
{
  PGresult *res;
  char cstate[20];
  char sqlcmd[1000];
  char descr[20];
  char timeString[25];

  // Converte il tipo di stato del sensore da giardino in una stringa
  int2stateSensorGarden(cstate, state);


  // Ottiene la data e l'ora correnti
  timeFlies(timeString);

  // Inizia una transazione nel database
  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Inserisce i dati nel database
  sprintf(sqlcmd,
          "INSERT INTO SensorGarden VALUES (%ld, %d, '%s', %d, %d, %d, '%s') ON CONFLICT DO NOTHING",
          tempo_trascorso,
          id,
          cstate,
          temperature,
          humidity,
          pid,
          timeString);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Conclude la transazione nel database
  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);
}
