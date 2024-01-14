#include <cstdlib>
#include <ctime>
#include <iostream>

int changeInt()
{
    // Inizializza il seme per la generazione casuale
    std::srand(std::time(0));

    // Genera un numero casuale tra 1 e 24 (inclusi)
    return (std::rand() % 24) + 1;
}