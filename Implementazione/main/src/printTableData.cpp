#include "main.h"
#include <iomanip>


void printTableData(PGresult *res)
{
    int rows = PQntuples(res);
    int columns = PQnfields(res);

    // Determine the maximum width for each column
    std::vector<int> columnWidths(columns, 0);

    // Print column names and determine the maximum width for each column
    for (int j = 0; j < columns; j++)
    {
        int nameWidth = strlen(PQfname(res, j));
        if (nameWidth > columnWidths[j])
            columnWidths[j] = nameWidth;
    }

    // Print column names with proper indentation
    for (int j = 0; j < columns; j++)
    {
        std::cout << std::setw(columnWidths[j] + 2) << std::left << PQfname(res, j);
    }
    std::cout << "\n";

    // Determine the maximum width for each column based on values
    for (int j = 0; j < columns; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            int valueWidth = strlen(PQgetvalue(res, i, j));
            if (valueWidth > columnWidths[j])
                columnWidths[j] = valueWidth;
        }
    }

    // Print the data with proper indentation
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
