#include <iostream>
#include <string>
#include "Components/camera.cpp"
#include "Components/light.cpp"
#include "Components/stove.cpp"
#include "Components/conditioner.cpp"



class OutOfHome {
    private: 
        Camera securityCamera;
        Sensor motionSensor;
        Light homeLights;

    public:
        OutOfHome(std::string cameraName, std::string lightName) : securityCamera(), motionSensor(), homeLights(lightName) {}
        
}