#include "main.h"
#include "global.h"

void log2stdout(Con2DB db1, int pid)
{
    PGresult *res;
    int rows, k;
    char cstate[20];
    long int dbnanosec, nsafters;
    char datebuf[1000];
    char sqlcmd[1000];

    // Array of table names
    const char *tableNames[] = {
        "Camera", "Conditioner", "Device", "Light", "Sensor", "SensorGarden", "LogActivity"};

    for (int i = 0; i < sizeof(tableNames) / sizeof(tableNames[0]); i++)
    {
        // Construct the SQL query for each table
        sprintf(sqlcmd, "SELECT * FROM %s WHERE pid = %d", tableNames[i], pid);

        // Execute the SQL query
        res = db1.ExecSQLtuples(sqlcmd);
        
        // Process the result if needed
        rows = PQntuples(res);
        // Add your code to process the result as needed

        // Clear the result
        PQclear(res);
    }
} /* log2stdout() */
