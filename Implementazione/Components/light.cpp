#include <iostream>
#include <string>
#include <chrono>

class Device
{
private:
    std::string nome;
    bool state;
    int id;
    RedisManager &redisManager;

public:
    // Constructor
    Device::Device(std::string deviceName, int deviceId, RedisManager &redisManager) : nome(deviceName), state(false), id(deviceId), redisManager(redisManager) {}

    // Functions
    void turnOn()
    {
        state = true;
        std::cout << nome << " is turned on." << std::endl;
        redisManager.sendCommand("LPUSH device_events:turning_on " + std::to_string(getId()) + " " + getCurrentTimestamp());
        redisManager.sendCommand("SET device_state:" + std::to_string(getId()) + " on");
    }

    void turnOff()
    {
        state = false;
        std::cout << nome << " is turned off." << std::endl;
        redisManager.sendCommand("LPUSH device_events:turning_off " + std::to_string(getId()) + " " + getCurrentTimestamp());
        redisManager.sendCommand("SET device_state:" + std::to_string(getId()) + " off");
    }

    int getId()
    {
        return id;
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
    Light::Light(std::string deviceName, int lightId, RedisManager &redisManager) : Device(deviceName, lightId, redisManager), color("White"), intensity(50) {}
    // Function to change the color of the light
    void changeColor(std::string newColor)
    {
        color = newColor;
        std::cout << "light color changed to " << color << std::endl;
        redisManager.sendCommand("LPUSH light_events:change_color " + std::to_string(getId()) + " " + getCurrentTimestamp());
        redisManager.sendCommand("SET light_color:" + std::to_string(getId()) + " " + std::to_string(getColor()));
    }

    // Function to change the intensity of the light
    void changeIntensity(int newIntensity)
    {
        if (newIntensity >= 1 && newIntensity <= 100)
        {
            intensity = newIntensity;
            std::cout << "light intensity changed to " << intensity << std::endl;
            redisManager.sendCommand("LPUSH light_events:change_intensity " + std::to_string(getId()) + " " + getCurrentTimestamp());
            redisManager.sendCommand("SET light_intensity:" + std::to_string(getId()) + " " + std::to_string(getIntensity()));
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
