#include "main.h"
#include <iostream>

int log2stdout(Con2DB db1, int pid)
{
    PGresult *res;
// Table names
    const char *tableNames[] = {
        "Light", "Camera", "Conditioner", "Device", "Sensor", "SensorGarden", "LogActivity"};

    for (const auto &tableName : tableNames)
    {
        // Construct the SQL query to select all rows from the current table
        char sqlcmd[1000];
        sprintf(sqlcmd, "SELECT * FROM %s", tableName);

        // Execute the SQL query
        PGresult *res = db1.ExecSQLtuples(sqlcmd);

        // Process and print the data for the current table
        std::cout << "Table: " << tableName << "\n";
        printTableData(res);

        // Clear the result
        PQclear(res);
    }

    return 0;
}


