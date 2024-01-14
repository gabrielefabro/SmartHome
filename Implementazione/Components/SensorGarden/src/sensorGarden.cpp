#include "sensorGarden.h"

// Costruttore
SensorGarden::SensorGarden(int id, sensorGarden_type state, int humidity, int temperature) : id(id), state(state), humidity(humidity), temperature(temperature) {}

sensorGarden_type SensorGarden::next()
{
    state = static_cast<sensorGarden_type>((state + rand() % 2) % 4);
    return state;
}

// Funzione per controllare lo stato del sensoreGarden
sensorGarden_type SensorGarden::getState() const
{
    return state;
}

int SensorGarden::getId() const
{
    return id;
}

int SensorGarden::getHumidity() const
{
    return humidity;
}

int SensorGarden::getTemperature() const
{
    return temperature;
}
