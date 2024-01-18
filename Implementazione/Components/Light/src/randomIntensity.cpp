#include "light.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../../../main/main.h"


int changeIntensity()
{
    // Inizializza il seme per la generazione casuale
    std::srand(std::time(0));

    // Genera un numero casuale tra 1 e 10 (inclusi)
    return (std::rand() % 10) + 1;
}