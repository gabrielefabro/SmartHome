#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../Components/device.cpp"
#include "../Components/sensorGarden.cpp"
#include "lightManagment.cpp"
#include <vector>

void turnOffSprinklers(std::vector<Device> sprinklers)
{
    for (Device &sprinkler : sprinklers)
    {
        // Spegni ogni irrigatore
        sprinkler.turnOff();
    }
}

void turnOnSprinklers(std::vector<Device> sprinklers)
{
    for (Device &sprinkler : sprinklers)
    {
        // Spegni ogni irrigatore
        sprinkler.turnOn();
    }
}

void irrigationManagment(std::vector<Device> sprinklers, int hours)
{
    for (Device &sprinkler : sprinklers)
    {
        sprinkler.turnOn();
    }

    std::this_thread::sleep_for(std::chrono::hours(hours));

    for (Device &sprinkler : sprinklers)
    {
        sprinkler.turnOff();
    }
}

void openGate(Device gate, bool key)
{
    if (key == true)
    {
        gate.turnOn();
    }
}

void controlLights(std::vector<Light> lights, SensorGarden sensor)
    {
        double humidity = sensor.getHumidity();
        double temperature = sensor.getTemperature();

        // Adjust the lights based on humidity and temperature conditions
        if (humidity > 50 && temperature > 25)
        {
            turnOnLights(lights);
            std::cout << "Turning on lights." << std::endl;
        }
        else
        {
            turnOffLights(lights);
            std::cout << "Turning off lights." << std::endl;
        }
    }

// Function to control irrigation based on humidity
void controlIrrigation(std::vector<Device> sprinklers, SensorGarden sensor)
{
    double humidity = sensor.getHumidity();

    // Adjust irrigation based on humidity conditions
    if (humidity < 30)
    {
        turnOnSprinklers(sprinklers);
        std::cout << "Turning on irrigation." << std::endl;
    }
    else
    {
        turnOffSprinklers(sprinklers);
        std::cout << "Turning off irrigation." << std::endl;
    }
}