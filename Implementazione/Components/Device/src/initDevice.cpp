#include "device.h"
#include <cstdlib>


Device initDevice()
{
    Device device(rand(), static_cast<device_type>(rand() % 3), static_cast<nome_type>(rand() % 8));
    return device;
}