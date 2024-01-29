#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

// Funzione per registrare i dati del sensore da giardino nel database
void log2sensorGardendb(Con2DB db1, int id, int pid, sensorGarden_type state, int humidity, int temperature, int t)
{
  PGresult *res;
  char cstate[20];
  char sqlcmd[1000];
  char descr[20];
  char timeString[25];

  // Converte il tipo di stato del sensore da giardino in una stringa
  int2stateSensorGarden(cstate, state);

  // Determina la descrizione in base allo stato del sensore da giardino
  if (strcmp(cstate, "change_light") == 0)
  {
    // Regola le luci in base alle condizioni di umidità e temperatura
    if (humidity > 50 && temperature > 25)
    {
      sprintf(descr, "luci_spente");
    }
    else
    {
      sprintf(descr, "luci_accese");
    }
  }
  else if (strcmp(cstate, "set_sprinklers") == 0)
  {
    // Regola l'irrigazione in base alle condizioni di umidità
    if (humidity < 30)
    {
      sprintf(descr, "irrigatori_accesi");
    }
    else
    {
      sprintf(descr, "irrigatori_spenti");
    }
  }
  else
  {
    // Nessun cambiamento rilevante
    sprintf(descr, "nothing_happened");
  }

  // Ottiene la data e l'ora correnti
  timeFlies(timeString);

  // Inizia una transazione nel database
  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Inserisce i dati nel database
  sprintf(sqlcmd,
          "INSERT INTO SensorGarden VALUES (%d, %d, '%s', %d, %d, '%s', %d, '%s') ON CONFLICT DO NOTHING",
          t,
          id,
          cstate,
          temperature,
          humidity,
          descr,
          pid,
          timeString);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Conclude la transazione nel database
  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);
}
