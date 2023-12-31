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

class Stove : public Device
{
private:
    int level;
    int id;

public:
    // Constructor
    Stove(std::string deviceName, int stoveId) : Device(deviceName, stoveId), level(0), id(stoveId) {}

    // Function to modify the power level of the stove
    void modifyTheLevel(int newLevel)
    {
        if (getState())
        {
            level = newLevel;
            std::cout << getNome() << " stove power level modified to " << level << std::endl;
        }
        else
        {
            std::cout << "Error: " << getNome() << " stove is turned off. Turn it on first." << std::endl;
        }
    }

    // Getter function for the level
    int getLevel() const
    {
        return level;
    }
};
