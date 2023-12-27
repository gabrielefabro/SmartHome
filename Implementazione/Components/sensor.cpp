#include <iostream>

class Sensor {
private:
    bool movement;

public:
    // Constructor
    Sensor() : movement(false) {}

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
