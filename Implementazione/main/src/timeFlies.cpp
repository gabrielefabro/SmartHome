#include "main.h"
#include <ctime>
#include <cstdio>

void timeFlies(char *buf)
{
    time_t currentTime;
    struct tm *localTime;

    // Ottenere l'orario corrente
    time(&currentTime);
    localTime = localtime(&currentTime);

    // Converti l'orario in un formato leggibile per la stringa SQL
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", localTime);
}
