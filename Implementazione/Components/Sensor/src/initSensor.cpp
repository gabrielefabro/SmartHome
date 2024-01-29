#include "sensor.h"
#include <cstdlib>

// Funzione che inizializza l'oggetto Sensore
Sensor initSensor()
{
    Sensor sensor(rand(), static_cast<sensor_type>(rand() % 3));
    return sensor;

}