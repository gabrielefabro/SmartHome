#include <iostream>
#include <string>
#include "Components/camera.cpp"
#include "Components/light.cpp"
#include "Components/stove.cpp"
#include "Components/conditioner.cpp"
#include "Components/sensor.cpp"



class OutOfHome {
    private: 
        Camera securityCamera;
        Sensor motionSensor;
        Light homeLights;

    public:
        OutOfHome(int cameraId, std::string lightName, int lightId, int sensorId) : securityCamera(cameraId), motionSensor(sensorId), homeLights(lightName, lightId) {}


        
};