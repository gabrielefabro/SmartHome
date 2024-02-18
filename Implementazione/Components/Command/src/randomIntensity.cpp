#include "command.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Funzione che genera un valore casuale per l'intensità della luce
int changeIntensity()
{
    return (rand() % 10) + 1;
}