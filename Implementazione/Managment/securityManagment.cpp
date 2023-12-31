
#include <iostream>
#include <string>
#include "../Components/camera.cpp"
#include "../Components/sensor.cpp"
#include <vector>

void turnOnCameras(std::vector<Camera> cameras)
{
    for (Camera &camera : cameras)
    {
        // Accendi ogni telecamera
        camera.startRecording();
    }
}

void turnOffCameras(std::vector<Camera> cameras)
{
    for (Camera &camera : cameras)
    {
        // Spegni ogni telecamera
        camera.stopRecording();
    }
}

void disactivateSensors(std::vector<Sensor> sensors)
{
    for (Sensor &sensor : sensors)
    {
        // Disattiva ogni sensore
        sensor.stopChecking();
    }
}

void activateSensors(std::vector<Sensor> sensors)
{
    for (Sensor &sensor : sensors)
    {
        // Attiva ogni sensore
        sensor.startChecking();
    }
}

void allarmNotification(std::vector<Sensor> sensors)
{
    for (Sensor &sensor : sensors)
    {
        if (sensor.simulateMotionDetection())
        {
            std::cout << "ALLARM BIP BIP" << std::endl;
        }
    }
}

void securityCheck(std::vector<Camera> cameras)
{
    bool check = false;
    for (Camera &camera : cameras)
    {
        if (camera.isRecording() == false)
        {
            std::cout << "CAMERA " << camera.getId() << ", PLS TURN ON!!!" << std::endl;
            check = true;
        }
    }
    if (check == false)
    {
        std::cout << "todo ok chicos!" << std::endl;
    }
}