#include <iostream>
#include <string>
#include <cstdlib>
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

    sensor_type Sensor::next()
    {
        state = static_cast<sensor_type>(rand() % 3);
        return state;
    }

    // Funzione per controllare lo stato del sensore
    sensor_type getState() const
    {
        return state;
    }

    int getId() const
    {
        return id;
    }

    void setMovement(bool value)
    {
        movement = value;
    }

    bool getMovement() const
    {
        return movement;
    }
};
