#include "main.h"
#include <iostream>

// Funzione che printa sul terminale tutte le tabelle alla fine dell'esecuzione del programma
int log2stdout(Con2DB db1, int pid)
{
    PGresult *res;
// Table names
    const char *tableNames[] = {
        "Light", "Camera", "Conditioner", "Device", "Sensor", "SensorGarden", "LogActivity", "SecurityRecap"};

    for (const auto &tableName : tableNames)
    {
        // Selezione tutte le tabelle nel database
        char sqlcmd[1000];
        sprintf(sqlcmd, "SELECT * FROM %s", tableName);

        // Esegui il comando per selezionare le tabelle
        PGresult *res = db1.ExecSQLtuples(sqlcmd);

        // Printa i dati delle tabelle
        std::cout << "Table: " << tableName << "\n";
        printTableData(res);

        PQclear(res);
    }

    return 0;
}


