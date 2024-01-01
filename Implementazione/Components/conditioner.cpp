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

class Conditioner : public Device
{
private:
    int level;
    int id;

public:
    // Constructor
    Conditioner(std::string deviceName, int conditionerId) : Device(deviceName, conditionerId), level(0), id(conditionerId) {}

    // Function to modify the power level of the conditioner
    void modifyTheLevel(int newLevel)
    {
        if (getState())
        {
            level = newLevel;
            std::cout << getNome() << " power level modified to " << level << std::endl;
        }
        else
        {
            std::cout << "Error: " << getNome() << " is turned off. Turn it on first." << std::endl;
        }
    }

    // Function to get the current power level
    int getLevel() const
    {
        return level;
    }

    // Simula il rilevamento della temperatura
    int simulateTempearature()
    {
        // Genera un numero casuale per simulare il rilevamento del movimento
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Genera un numero casuale compreso tra 0 e RAND_MAX 
        int randomValue = std::rand() % 40;

        std::cout << randomValue << std::endl;

        return randomValue;
    }

};
