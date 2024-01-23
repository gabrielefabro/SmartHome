#include "conditioner.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int changeRandomTemperature()
{
    // Genera un numero casuale tra 1 e 10 (inclusi)
    return (std::rand() % 40) + 1;
}