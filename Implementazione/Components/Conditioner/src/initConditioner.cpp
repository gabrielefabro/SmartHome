#include "conditioner.h"
#include "../../../main/src/global.h"
#include <cstdlib>

// Funzione che inizializza l'oggetto condizionatore
Conditioner initConditioner()
{
    Conditioner conditioner(rand(), rand() % 45, static_cast<conditioner_type>(rand() % 3));
    return conditioner;
}