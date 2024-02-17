#include "light.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Funzione che genera un colore casuale per la luce
light_color getRandomColor() {    
    return static_cast<light_color>(rand() % 7);
}