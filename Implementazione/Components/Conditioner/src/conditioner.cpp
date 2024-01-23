#include "conditioner.h"

Conditioner::Conditioner(int id, int temperature, conditioner_type state) : id(id), temperature(temperature), state(state) {}

conditioner_type Conditioner::next()
{
    state = static_cast<conditioner_type>(rand() % 3);
    return state;
}

// Funzione per controllare lo stato della temperatura
conditioner_type Conditioner::getState() const
{
    return state;
}

// Modificare la temperatura
void Conditioner::modifyTemperature(int newTemperature)
{
    if (getState() == ConditionerON)
    {
        temperature = newTemperature;
        std::cout << " power temperature modified to " << temperature << std::endl;
    }
    else
    {
        std::cout << "Error: turned off. Turn it on first." << std::endl;
    }
}

int Conditioner::getId() const
{
    return id;
}

int Conditioner::getTemperature() const
{
    return temperature;
}

void Conditioner::setState(conditioner_type newState)
{
    state = newState;
}
