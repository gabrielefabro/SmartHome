#include <iostream>
#include <string>
#include "../Components/camera.cpp"
#include "../Components/light.cpp"
#include "../Components/stove.cpp"
#include "../Components/conditioner.cpp"
#include "../Components/sensor.cpp"
#include <vector>

class OutOfHome
{
private:
    std::vector<Light> lights;
    std::vector<Camera> cameras;
    std::vector<Stove> stoves;

public:
    OutOfHome(const std::vector<Light> &lightsList, const std::vector<Camera> &camerasList, const std::vector<Stove> &stovesList) : lights(lightsList), cameras(camerasList), stoves(stovesList) {}
};