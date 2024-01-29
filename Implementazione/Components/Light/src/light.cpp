#include "light.h"
#include "main.h"

// Costruttore della classe Light.
Light::Light(int id, light_type state, light_color color, int intensity) : id(id), state(state), color(color), intensity(intensity) {}

// Funzione per ottenere il prossimo stato casuale della luce.
light_type Light::next()
{
    int number = rand() % 4;
    state = static_cast<light_type>(number);
    return state;
}

// Funzione per ottenere lo stato attuale della luce.
light_type Light::getState() const
{
    return state;
}

// Funzione per ottenere l'ID della luce.
int Light::getId() const
{
    return id;
}

// Funzione per impostare il colore della luce.
void Light::setColor(light_color newColor)
{
    color = newColor;
}

// Funzione per impostare l'intensità della luce.
void Light::setIntensity(int newIntensity)
{
    intensity = newIntensity;
}

// Funzione per ottenere il colore attuale della luce.
light_color Light::getColor() const
{
    return color;
}

// Funzione per ottenere l'intensità attuale della luce.
int Light::getIntensity() const
{
    return intensity;
}

// Funzione per impostare lo stato della luce.
void Light::setState(light_type newState)
{
    state = newState;
}
