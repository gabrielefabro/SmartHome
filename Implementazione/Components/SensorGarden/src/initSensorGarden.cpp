#include "sensorGarden.h"
#include "../../../main/src/global.h"
#include <cstdlib>

SensorGarden initSensorGarden()
{
    SensorGarden sensor(rand(), static_cast<sensorGarden_type>(rand() % 4), rand() % 100, rand() % 45);
    return sensor;

}