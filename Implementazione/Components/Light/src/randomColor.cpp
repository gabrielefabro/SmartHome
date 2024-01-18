#include "light.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../../../main/main.h"

light_color getRandomColor() {
    // Inizializza il seme per la generazione casuale
    std::srand(std::time(0));

    // Ottieni un numero casuale tra 0 e il numero massimo di colori
    int randomIndex = std::rand() % (PURPLE + 1);

    // Converti l'indice casuale in un valore di enumerazione
    return static_cast<light_color>(randomIndex);
}