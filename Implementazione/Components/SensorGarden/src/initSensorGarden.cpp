#include "sensorGarden.h"
#include <cstdlib>

// Funzione che inizializza l'oggetto SensoreGiardino
SensorGarden initSensorGarden()
{
    SensorGarden sensor(rand(), static_cast<sensorGarden_type>(rand() % 4), rand() % 100, rand() % 45);
    return sensor;

}