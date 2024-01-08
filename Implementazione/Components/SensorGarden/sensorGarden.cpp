#include <iostream>
#include <string>
#include <cstdlib>
#include "main.h"
#include "sensorGarden.h"

class SensorGarden
{
private:
    sensor_Garden_type state;
    int id;
    int humidity;  
    int temperature;

public:
    // Costruttore
    SensorGarden(int id, sensor_Garden_type state, int humidity, int temperature) : id(id), state(state), humidity(humidity), temperature(temperature) {}

    sensor_Garden_type next(SensorGarden sensor)
    {
        sensor.state = static_cast<sensor_Garden_type>((state + rand() % 2) % 4);
        return state;
    }

    // Funzione per controllare lo stato di registrazione
    sensor_Garden_type getState() const
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
