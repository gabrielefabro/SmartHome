#include "light.h"
#include "main.h"

// Costruttore
Light::Light(int id, light_type state, light_color color, int intensity) : id(id), state(state), color(color), intensity(intensity) {}

light_type Light::next()
{
    
    int number = rand() % 4;
    std::cout << "ciao" << std::endl;
    std::cout << number << std::endl;
    state = static_cast<light_type>(number);
    std::cout << state << std::endl;
    return state;
}

// Funzione per controllare lo stato delle luci
light_type Light::getState() const
{
    return state;
}

int Light::getId() const
{
    return id;
}

void Light::setColor(light_color newColor)
{
    std::cout << "cambio colore" << std::endl;
    color = newColor;
}

void Light::setIntensity(int newIntensity)
{
    intensity = newIntensity;
}

light_color Light::getColor() const
{
    return color;
}

int Light::getIntensity() const
{
    return intensity;
}

void Light::setState(light_type newState)
{
    state = newState;
}
