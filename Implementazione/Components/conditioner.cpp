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

class Conditioner : public Device
{
private:
    int level;
    int id;

public:
    // Constructor
    Conditioner::Conditioner(std::string deviceName, int conditionerId, RedisManager &redisManager) : Device(deviceName, conditionerId, redisManager), level(0) {}

    // Function to modify the power level of the conditioner
    void modifyTheLevel(int newLevel)
    {
        if (getState())
        {
            level = newLevel;
            std::cout << getNome() << " power level modified to " << level << std::endl;
            redisManager.sendCommand("SET conditioner_level:" + std::to_string(getId()) + std::to_string(newLevel));
            redisManager.sendCommand("LPUSH conditioner_events:modify_level " + std::to_string(getId()) + " " + getCurrentTimestamp());
            
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
        redisManager.sendCommand("LPUSH conditioner_events:simulate_temperature " + std::to_string(getId()) + " " + getCurrentTimestamp());
        return randomValue;
    }

};
