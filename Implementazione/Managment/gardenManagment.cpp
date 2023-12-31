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
        // Spegni ogni luce
        sprinkler.turnOff();
    }
}

void turnOnSprinklers(std::vector<Device> sprinklers)
{
    for (Device &sprinkler : sprinklers)
    {
        // Spegni ogni luce
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

void openGate(Device gate)
{
    if (gate.getNome() == "Gate")
    {
        gate.turnOn();
    }
}

void controlLights(SensorGarden sensor)
    {
        double humidity = sensor.getHumidity();
        double temperature = sensor.getTemperature();

        // Adjust the lights based on humidity and temperature conditions
        if (humidity > 50 && temperature > 25)
        {
            turnOnLights();
            std::cout << "Turning on lights." << std::endl;
        }
        else
        {
            turnOffLights();
            std::cout << "Turning off lights." << std::endl;
        }
    }

// Function to control irrigation based on humidity
void controlIrrigation(SensorGarden sensor)
{
    double humidity = sensor.getHumidity();

    // Adjust irrigation based on humidity conditions
    if (humidity < 30)
    {
        turnOnSprinklers();
        std::cout << "Turning on irrigation." << std::endl;
    }
    else
    {
        turnOffSprinklers();
        std::cout << "Turning off irrigation." << std::endl;
    }
}