#include <iostream>
#include <string>
#include <cstdlib>
#include "light.h"

class Light
{
private:
    light_type state;
    light_color color;
    int intensity;
    int id;

public:
    // Costruttore
    Light(int id, light_type state, light_color color, int intensity) : id(id), state(state), color(color), intensity(intensity) {}

    light_type Light::next()
    {
        state = static_cast<light_type>(rand() % 4);
        return state;
    }

    // Funzione per controllare lo stato delle luci
    light_type getState() const
    {
        return state;
    }

    int getId() const
    {
        return id;
    }

    void setColor(light_color newColor)
    {
        color = newColor;
    }

    void setIntensity(int newIntensity)
    {
        intensity = newIntensity;
    }
};