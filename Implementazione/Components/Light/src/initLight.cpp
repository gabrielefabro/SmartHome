#include "light.h"
#include <cstdlib>

Light initLight()
{
    Light light(rand(), static_cast<light_type>(rand() % 4), static_cast<light_color>(rand() % 7), (rand() % 100));
    return light;
}