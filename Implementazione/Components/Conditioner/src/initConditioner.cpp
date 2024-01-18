#include "conditioner.h"
#include "../../../main/global.h"
#include <cstdlib>

Conditioner initConditioner()
{
    Conditioner conditioner(rand(), rand(), static_cast<conditioner_type>(rand() % 2));
    return conditioner;
}