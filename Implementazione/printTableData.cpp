#include "main.h"
#include <iomanip>

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
