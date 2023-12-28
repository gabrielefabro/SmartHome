#include <iostream>

class Sensor {
private:
    bool movement;
    int id;

public:
    // Constructor
    Sensor(int sensorId) : movement(false),id(sensorId) {}

    // Function to check for movement
    void checkMovement() {
        if (detectMovment()) {
            movement = true;
            std::cout << "Movement detected!" << std::endl;
        } else {
            movement = false;
            std::cout << "No movement detected." << std::endl;
        }
    }

    // Getter function for movement
    bool hasMovement() const {
        return movement;
    }

    bool detectMovment(bool MV) {

        return MV

    }
};
