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
        state = static_cast<light_type>((state + rand() % 2) % 4);
        return state;
    }

    void changeIntensity(int newIntensity)
    {
        if(getState() == ON)
        {
            if (newIntensity >= 1 && newIntensity <= 10)
            {
                intensity = newIntensity;
                std::cout << "light intensity changed to " << intensity << std::endl;
            }
            else
            {
                std::cout << "Error: Intensity value must be between 1 and 10." << std::endl;
            }
        }
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

};