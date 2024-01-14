#include "main.h"

/* buy stock  */

void init_logdb(Con2DB db1, int pid, int id, device_type state, nome_type nome)
{

 PGresult *res;
 int rows, k;
 
 
 /*  init  */
 
      sprintf(sqlcmd, "BEGIN"); 
      res = db1.ExecSQLcmd(sqlcmd);
      PQclear(res);

  sprintf(sqlcmd,
"INSERT INTO Timevar VALUES (%d, %d, \'%s\', \'%d\', \'%s\', \'%s\', \'%d\') ON CONFLICT DO NOTHING",
	  id, pid, "Device", state, "discrete", "Values: ON, Programmed, OFF", nome);

  res = db1.ExecSQLcmd(sqlcmd);
     PQclear(res);
     
 sprintf(sqlcmd, "COMMIT"); 
      res = db1.ExecSQLcmd(sqlcmd);
      PQclear(res);

     
 }  /*   init_logdb()  */