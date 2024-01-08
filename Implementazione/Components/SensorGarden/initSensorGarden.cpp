#include "sensorGarden.h"
#include <cstdlib>

SensorGarden initSensorGarden()
{
    SensorGarden sensor(rand(), static_cast<sensor_Garden_type>(rand() % 4), rand() % 100, rand() % 45);
    return sensor;

}