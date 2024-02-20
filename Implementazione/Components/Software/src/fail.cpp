#include "software.h"

void fail(Con2DB db1, int pid, char *component)
{
  int x;
  PGresult *res;
  char cstate[20];
  char sqlcmd[1000];
  char *message = "Failed";
  char timeString[25];
  // Ottieni la rappresentazione di stringa del timestamp corrente.
  timeFlies(timeString);

  // Inizia una transazione SQL.
  sprintf(sqlcmd, "BEGIN");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Crea e esegui un comando SQL per inserire informazioni sulla telecamera nella tabella "Camera" del database.
  sprintf(sqlcmd,
          "INSERT INTO Fail VALUES ('%s', %d, '%s', '%s') ON CONFLICT DO NOTHING",
          component,
          pid,
          timeString,
          message);

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Concludi la transazione SQL.
  sprintf(sqlcmd, "COMMIT");
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);
}
