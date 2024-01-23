#include "light.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../../../main/src/main.h"

light_color getRandomColor() {
    // Inizializza il seme per la generazione casuale
    std::srand(std::time(0));
    
    // Converti l'indice casuale in un valore di enumerazione
    return static_cast<light_color>(rand() % 7);
}