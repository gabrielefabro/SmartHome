#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include "../Components/device.cpp"
#include "../Components/conditioner.cpp"


void turnOffConditioner(std::vector<Device> conditioner)
{
    for (Device &conditioner : conditioner)
    {
        // Spegni ogni condizionatore
        conditioner.turnOff();
    }
}

void turnOnConditioner(std::vector<Device> conditioner)
{
    for (Device &conditioner : conditioner)
    {
        // Spegni ogni condizionatore
        conditioner.turnOn();
    }
}

void operateConditionersAtScheduledTimes(const std::chrono::system_clock::time_point &startTime, const std::chrono::duration<int> &duration, std::vector<Device> conditioner)
{
    for (Device &conditioner : conditioner)
    {
        conditioner.operateAtScheduledTimes(startTime, duration);
    }
}

void modifyTemperature(std::vector<Conditioner> &conditioners, int newLevel)
{
    for (Conditioner &conditioner : conditioners)
    {
        conditioner.modifyTheLevel(newLevel);
    }
}


void autoTemperature(std::vector<Conditioner> &conditioners, Conditioner conditionerr)
{
    int temperature = conditionerr.simulateTempearature();

    if (temperature > 0 && temperature < 18 )
    {
        for (Conditioner &conditioner : conditioners)
        {
            conditioner.modifyTheLevel(26);
        }
    }
    else if (temperature > 18 && temperature < 35)
    {
        for (Conditioner &conditioner : conditioners)
        {
            conditioner.modifyTheLevel(22);
        }
    }
    else if (temperature <= 0)
    {
        for (Conditioner &conditioner : conditioners)
        {
            conditioner.modifyTheLevel(29);
        }
    }
    else
    {
        for (Conditioner &conditioner : conditioners)
        {
            conditioner.modifyTheLevel(19);
        }
    }
}