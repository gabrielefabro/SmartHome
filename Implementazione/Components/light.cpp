#include <iostream>
#include <string>
#include <chrono>

class Device
{
private:
    std::string nome;
    bool state;
    int id;

public:
    // Constructor
    Device(std::string deviceName, int deviceId) : nome(deviceName), state(false), id(deviceId) {}

    // Functions
    void turnOn()
    {
        state = true;
        std::cout << nome << " is turned on." << std::endl;
    }

    void turnOff()
    {
        state = false;
        std::cout << nome << " is turned off." << std::endl;
    }

    // Getter functions
    bool getState() const
    {
        return state;
    }

    std::string getNome() const
    {
        return nome;
    }

    void operateAtScheduledTimes(const std::chrono::system_clock::time_point &startTime, const std::chrono::duration<int> &duration)
    {
        auto endTime = startTime + duration;

        while (true)
        {
            auto currentTime = std::chrono::system_clock::now();

            if (currentTime > startTime && currentTime < endTime)
            {
                if (!state)
                {
                    turnOn();
                }
            }
            else
            {
                turnOff();
                break;
            }
        }
    }
};

class Light : public Device
{
private:
    std::string color;
    int intensity;
    int id;

public:
    // Constructor
    Light(std::string deviceName, int lightId) : Device(deviceName, lightId), color("White"), intensity(50), id(lightId) {}

    // Function to change the color of the light
    void changeColor(std::string newColor)
    {
        color = newColor;
        std::cout << "light color changed to " << color << std::endl;
    }

    // Function to change the intensity of the light
    void changeIntensity(int newIntensity)
    {
        if (newIntensity >= 1 && newIntensity <= 100)
        {
            intensity = newIntensity;
            std::cout << "light intensity changed to " << intensity << std::endl;
        }
        else
        {
            std::cout << "Error: Intensity value must be between 1 and 100." << std::endl;
        }
    }

    // Getter functions
    std::string getColor() const
    {
        return color;
    }

    int getIntensity() const
    {
        return intensity;
    }
};
