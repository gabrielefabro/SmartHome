#include <iostream>
#include <string>

class Conditioner : public Device {
private:
    int level;

public:
    // Constructor
    Conditioner(std::string deviceName) : Device(deviceName), level(0) {}

    // Function to modify the power level of the conditioner
    void modifyTheLevel(int newLevel) {
        if (getState()) {
            level = newLevel;
            std::cout << getNome() << " power level modified to " << level << std::endl;
        } else {
            std::cout << "Error: " << getNome() << " is turned off. Turn it on first." << std::endl;
        }
    }

    // Function to get the current power level
    int getLevel() const {
        return level;
    }
};
