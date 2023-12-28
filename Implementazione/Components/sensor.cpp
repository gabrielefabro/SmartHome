#include <iostream>
#include <cstdlib>
#include <ctime>

class Sensor
{
private:
    bool movement;
    int id;

public:
    // Constructor
    Sensor(int sensorId) : movement(false), id(sensorId) {}


    // Simula il rilevamento del movimento
    bool simulateMotionDetection() {
        // Genera un numero casuale per simulare il rilevamento del movimento
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Genera un numero casuale compreso tra 0 e RAND_MAX
        int randomValue = std::rand() % 100;

        std::cout << randomValue << std::endl;

        // Simuliamo che il movimento sia rilevato se il numero casuale è inferiore a 30 (30% di probabilità)
        movement = (randomValue < 30);

        // Stampa un messaggio di debug
        if (movement) {
            std::cout << "Movement detected!" << std::endl;
            return true;
        } else {
            std::cout << "No movement detected." << std::endl;
            return false;
        }
    }

    // Getter function for movement
    bool hasMovement() const
    {
        return movement;
    }
};
