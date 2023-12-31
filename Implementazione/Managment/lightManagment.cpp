#include <iostream>
#include <string>
#include "../Components/light.cpp"
#include "../Components/device.cpp"
#include <vector>

void turnOnLights(std::vector<Light> lights)
{
    for (Light &light : lights)
    {
        // Spegni ogni luce
        light.turnOn();
    }
}

void turnOffLights(std::vector<Light> lights)
{
    for (Light &light : lights)
    {
        // Spegni ogni luce
        light.turnOff();
    }
}

void turnOffShutter(std::vector<Device> shutters)
{
    for (Device &shutter : shutters)
    {
        // Spegni ogni luce
        shutter.turnOff();
    }
}

void turnOnshutter(std::vector<Device> shutters)
{
    for (Device &shutter : shutters)
    {
        // Accendi ogni luce
        shutter.turnOn();
    }
}

void changeColorLights(std::vector<Light> lights, std::string color)
{
    for (Light &light : lights)
    {
        light.changeColor(color);
    }
}

void changeIntensityLights(std::vector<Light> lights, int intensity)
{
    if ( intensity > 0 && intensity <= 100)
    {
        for (Light &light : lights)
            {
                light.changeIntensity(intensity);
            }
    }
    else
    {
        std::cout << "light intensity should be between 0 and 100" << std::endl;
    }
        
}