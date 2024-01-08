#include <iostream>
#include <string>
#include <cstdlib>
#include "main.h"
#include "sensor.h"

class Sensor
{
private:
    sensor_type state;
    int id;
    bool movement;

public:
    // Costruttore
    Sensor(int id, sensor_type state) : state(state), id(id), movement(false) {}

    sensor_type next(Sensor sensor)
    {
        sensor.state = static_cast<sensor_type>((state + rand() % 2) % 3);
        return state;
    }

    // Funzione per controllare lo stato di registrazione
    sensor_type getState() const
    {
        return state;
    }

    int getId() const
    {
        return id;
    }
};
