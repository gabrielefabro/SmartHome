#include <iostream>
#include <cstdlib>
#include <ctime>

class Sensor
{
private:
    bool movement;
    int id;
    bool checking;
    RedisManager &redisManager;

public:
    // Constructor
    Sensor::Sensor(int sensorId, RedisManager &redisManager) : movement(false), id(sensorId), checking(false), redisManager(redisManager) {}
    // Simula il rilevamento del movimento
    bool simulateMotionDetection()
    {
        // Genera un numero casuale per simulare il rilevamento del movimento
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Genera un numero casuale compreso tra 0 e RAND_MAX
        int randomValue = std::rand() % 100;

        std::cout << randomValue << std::endl;

        // Simuliamo che il movimento sia rilevato se il numero casuale è inferiore a 30 (30% di probabilità)
        movement = (randomValue < 30);

        // Stampa un messaggio di debug
        if (movement)
        {
            std::cout << "Movement detected!" << std::endl;
            redisManager.sendCommand("LPUSH sensor_events:motion_detection " + std::to_string(getId()) + " " + getCurrentTimestamp());
            return true;
        }
        else
        {
            std::cout << "No movement detected." << std::endl;
            return false;
        }
    }

    // Getter function for movement
    bool hasChecking() const
    {
        return checking;
    }

    void startChecking()
    {
        if (!checking)
        {
            checking = true;
            std::cout << "Checking started." << std::endl;
            redisManager.sendCommand("LPUSH sensor_events:start_checking " + std::to_string(getId()) + " " + getCurrentTimestamp());
            redisManager.sendCommand("SET sensor_checking:" + std::to_string(getId()) + " " + std::to_string(isChecking()));
        }
    }

    // Funzione per fermare la registrazione
    void stopChecking()
    {
        if (checking)
        {
            checking = false;
            std::cout << "Checking stopped." << std::endl;
            redisManager.sendCommand("LPUSH sensor_events:stop_checking " + std::to_string(getId()) + " " + getCurrentTimestamp());
            redisManager.sendCommand("SET sensor_checking:" + std::to_string(getId()) + " " + std::to_string(isChecking()));
        }
    }

    // Funzione per controllare lo stato di registrazione
    bool isChecking() const
    {
        return checking;
    }
};
