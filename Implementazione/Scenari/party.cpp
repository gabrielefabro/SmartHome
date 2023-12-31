#include <iostream>
#include <string>
#include "../Components/device.cpp"
#include "../Components/camera.cpp"
#include "../Components/light.cpp"
#include "../Components/sensor.cpp"
#include <vector>
#include <thread>
#include <chrono>
class Party
{
private:
    std::vector<Camera> cameras;
    std::vector<Sensor> sensors;
    std::vector<Device> devices;
    std::vector<Light> lights;

public:
    Party(const std::vector<Light> &lightsList, const std::vector<Camera> &camerasList, const std::vector<Sensor> &sensorsList, const std::vector<Device> &devicesList) : lights(lightsList), cameras(camerasList), sensors(sensorsList), devices(devicesList) {}

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

    void changeColorLights(std::string color)
    {
        for (Light &light : lights)
        {
            //  Change the color of the light of interest
            light.changeColor(color);
        }
    }

    void turnOnCameras()
    {
        for (Camera &camera : cameras)
        {
            // Accendi ogni telecamera
            camera.startRecording();
        }
    }

    void disactivateSensors()
    {
        for (Sensor &sensor : sensors)
        {
            // Attiva ogni sensore
            sensor.stopChecking();
        }
    }

    void turnOnTv()
    {
        for (Device &device : devices)
        {
            // Spegni ogni persiana
            if (device.getNome() == "TV")
            {
                device.turnOn();
            }
        }
    }

    void makePopcorn()
    {
        for (Device &device : devices)
        {
            // Spegni ogni persiana
            if (device.getNome() == "Microwave")
            {
                device.turnOn();
                std::this_thread::sleep_for(std::chrono::seconds(180));
                device.turnOff();
            }
        }
    }

    void turnOnSpeackers()
    {
        for (Device &device : devices)
        {
            if (device.getNome() == "Speakers")
            {
                device.turnOn();
            }
        }
    }

    void partyTime(int timer)
    {
        std::string colors[] = {"Red", "Green", "Blu", "Yellow", "Orange", "White", "Purple"};
        turnOnSpeackers();
        int k = 0;
        while (k != 0)
        {
            turnOnLights();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            turnOffLights();
            for (std::string color : colors)
            {
                changeColorLights(color);
            }
            k--;
        }
    }
};
