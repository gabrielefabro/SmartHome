#include "main.h"

/* buy stock  */

void init_logdb(Con2DB db1, int pid, int id, camera_type state)
{

 PGresult *res;
 int rows, k;
 
 
 /*  init  */
 
      sprintf(sqlcmd, "BEGIN"); 
      res = db1.ExecSQLcmd(sqlcmd);
      PQclear(res);

  sprintf(sqlcmd,
"INSERT INTO Timevar VALUES (%d, %d, \'%s\', \'%d\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	  id, pid, "Camera", state, "discrete", "Values: ON, Waiting, OFF");

  res = db1.ExecSQLcmd(sqlcmd);
     PQclear(res);
     
 sprintf(sqlcmd, "COMMIT"); 
      res = db1.ExecSQLcmd(sqlcmd);
      PQclear(res);

      
#if (DEBUG > 0)
      sprintf(sqlcmd, "SELECT * FROM Timevar where ((pid = %d) AND (varname = 'x'))", pid);

    res = db1.ExecSQLtuples(sqlcmd);
    rows = PQntuples(res);
      
    fprintf(stderr, "initdb(): inserted in Timevar (%d, %d, %s, %s, %s, %s)\n",
	    atoi(PQgetvalue(res, 0, PQfnumber(res, "vid"))),
	    atoi(PQgetvalue(res, 0, PQfnumber(res, "pid"))),
	    PQgetvalue(res, 0, PQfnumber(res, "sysname")),
	    PQgetvalue(res, 0, PQfnumber(res, "varname")),
	    PQgetvalue(res, 0, PQfnumber(res, "vardomain")),
	    PQgetvalue(res, 0, PQfnumber(res, "varinfo"))
	    );
#endif


     
 }  /*   init_logdb()  */