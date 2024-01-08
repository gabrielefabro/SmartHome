#include "sensor.h"
#include <cstdlib>

Sensor initSensor()
{
    Sensor sensor(rand(), static_cast<sensor_type>(rand() % 3));
    return sensor;

}