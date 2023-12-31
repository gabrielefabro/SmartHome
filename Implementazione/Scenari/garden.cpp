#include <iostream>
#include <string>
#include "../Components/device.cpp"
#include "../Components/sensorGarden.cpp"
#include "../Components/light.cpp"
#include <vector>
#include <thread>
#include <chrono>

class Garden {
private:
    std::vector<Device> sprinklers;
    std::vector<SensorGarden> sensors;
    std::vector<Light> lights;

public:
    Garden(const std::vector<Light> &lightsList, const std::vector<SensorGarden> &sensorGardenList, const std::vector<Device> &sprinklersList) : lights(lightsList), sprinklers(sprinklersList), sensors(sensorGardenList) {}

    // Metodi per controllare i dispositivi
    void turnOnLights()
    {
        for (Light &light : lights)
        {
            // Spegni ogni luce
            light.turnOn();
        }
    }

    void turnOffLights()
    {
        for (Light &light : lights)
        {
            // Spegni ogni luce
            light.turnOff();
        }
    }

    void turnOffSprinklers()
    {
        for (Device &sprinkler : sprinklers)
        {
            // Spegni ogni luce
            sprinkler.turnOff();
        }
    }

    void turnOnSprinklers()
    {
        for (Device &sprinkler : sprinklers)
        {
            // Spegni ogni luce
            sprinkler.turnOn();
        }
    }

    void irrigationManagment(int hours) 
    {
        turnOnSprinklers();
        std::this_thread::sleep_for(std::chrono::seconds(hours*60));
        turnOnSprinklers();
    }
    
};