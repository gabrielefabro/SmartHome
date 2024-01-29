#include "conditioner.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Funzione che genera un numero casuale per modificare la temperatura
int changeRandomTemperature()
{
    return (std::rand() % 40) + 1;
}