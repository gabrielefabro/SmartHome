#include <iostream>
#include <string>

class Stove : public Device {
private:
    int level;
    int id;

public:
    // Constructor
    Stove(std::string deviceName,int stoveId) : Device(deviceName), level(0),id(stoveId) {}

    // Function to modify the power level of the stove
    void modifyTheLevel(int newLevel) {
        if (getState()) {
            level = newLevel;
            std::cout << getNome() << " stove power level modified to " << level << std::endl;
        } else {
            std::cout << "Error: " << getNome() << " stove is turned off. Turn it on first." << std::endl;
        }
    }

    // Getter function for the level
    int getLevel() const {
        return level;
    }
};
