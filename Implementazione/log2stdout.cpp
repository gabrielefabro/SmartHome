#include "./con2db/src/pgsql.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <libpq-fe.h>
// Funzione per stampare i dati di una tabella PostgreSQL
void printTableData(PGresult *res)
{
    // Ottieni il numero di righe e colonne nel risultato della query
    int rows = PQntuples(res);
    int columns = PQnfields(res);

    // Determina la larghezza massima per ogni colonna
    std::vector<int> columnWidths(columns, 0);

    // Stampa i nomi delle colonne e determina la larghezza massima per ogni colonna
    for (int j = 0; j < columns; j++)
    {
        int nameWidth = strlen(PQfname(res, j));
        if (nameWidth > columnWidths[j])
            columnWidths[j] = nameWidth;
    }

    // Stampa i nomi delle colonne con la giusta indentazione
    for (int j = 0; j < columns; j++)
    {
        std::cout << std::setw(columnWidths[j] + 2) << std::left << PQfname(res, j);
    }
    std::cout << "\n";

    // Determina la larghezza massima per ogni colonna basandosi sui valori
    for (int j = 0; j < columns; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            int valueWidth = strlen(PQgetvalue(res, i, j));
            if (valueWidth > columnWidths[j])
                columnWidths[j] = valueWidth;
        }
    }

    // Stampa i dati con la giusta indentazione
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << std::setw(columnWidths[j] + 2) << std::left << PQgetvalue(res, i, j);
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}

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


