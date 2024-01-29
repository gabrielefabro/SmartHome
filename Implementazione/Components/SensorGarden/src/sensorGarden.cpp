#include "sensorGarden.h"

// Costruttore del sensore da giardino
SensorGarden::SensorGarden(int id, sensorGarden_type state, int humidity, int temperature) : id(id), state(state), humidity(humidity), temperature(temperature) {}

// Funzione per ottenere lo stato successivo del sensore da giardino
sensorGarden_type SensorGarden::next()
{
    state = static_cast<sensorGarden_type>(rand() % 4);
    return state;
}

// Funzione per ottenere lo stato attuale del sensore da giardino
sensorGarden_type SensorGarden::getState() const
{
    return state;
}

// Funzione per ottenere l'ID del sensore da giardino
int SensorGarden::getId() const
{
    return id;
}

// Funzione per ottenere l'umidità rilevata dal sensore da giardino
int SensorGarden::getHumidity() const
{
    return humidity;
}

// Funzione per ottenere la temperatura rilevata dal sensore da giardino
int SensorGarden::getTemperature() const
{
    return temperature;
}

// Funzione per impostare lo stato del sensore da giardino
void SensorGarden::setState(sensorGarden_type newState)
{
    state = newState;
}

// Funzione per impostare la temperatura rilevata dal sensore da giardino
void SensorGarden::setTemperature(int newTemperature)
{
    temperature = newTemperature;
}

// Funzione per impostare l'umidità rilevata dal sensore da giardino
void SensorGarden::setHumidity(int newHumidity)
{
    humidity = newHumidity;
}
