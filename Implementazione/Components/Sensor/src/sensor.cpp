#include "sensor.h"

// Costruttore
Sensor::Sensor(int id, sensor_type state) : state(state), id(id), movement(false) {}

sensor_type Sensor::next()
{
    state = static_cast<sensor_type>(rand() % 3);
    return state;
}

// Funzione per controllare lo stato del sensore
sensor_type Sensor::getState() const
{
    return state;
}

int Sensor::getId() const
{
    return id;
}

void Sensor::setMovement(bool value)
{
    movement = value;
}

bool Sensor::getMovement() const
{
    return movement;
}

void Sensor::setState(sensor_type newState)
{
    state = newState;
}
