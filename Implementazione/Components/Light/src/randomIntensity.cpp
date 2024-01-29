#include "light.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../../../main/src/main.h"

// Funzione che genera un valore casuale per l'intensità della luce
int changeIntensity()
{
    return (rand() % 10) + 1;
}