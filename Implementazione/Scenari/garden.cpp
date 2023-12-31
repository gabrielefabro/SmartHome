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

    


    
};