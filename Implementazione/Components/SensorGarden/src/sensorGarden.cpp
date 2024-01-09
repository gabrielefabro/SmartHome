#include <iostream>
#include <string>
#include <cstdlib>
#include "main.h"
#include "sensorGarden.h"

class SensorGarden
{
private:
    sensorGarden_type state;
    int id;
    int humidity;  
    int temperature;

public:
    // Costruttore
    SensorGarden(int id, sensorGarden_type state, int humidity, int temperature) : id(id), state(state), humidity(humidity), temperature(temperature) {}

    sensorGarden_type next()
    {
        state = static_cast<sensorGarden_type>((state + rand() % 2) % 4);
        return state;
    }

    // Funzione per controllare lo stato del sensoreGarden
    sensorGarden_type getState() const
    {
        return state;
    }

    int getId() const
    {
        return id;
    }

    double getHumidity() const
    {
        return humidity;
    }

    double getTemperature() const
    {
        return temperature;
    }
};
