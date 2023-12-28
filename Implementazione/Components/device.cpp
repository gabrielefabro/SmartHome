#include <iostream>
#include <string>

class Device {
private:
    std::string nome;
    bool state;
    int id;

public:
    // Constructor
    Device(std::string deviceName,int deviceId) : nome(deviceName), state(false),id(deviceId) {}

    // Functions
    void turnOn() {
        state = true;
        std::cout << nome << " is turned on." << std::endl;
    }

    void turnOff() {
        state = false;
        std::cout << nome << " is turned off." << std::endl;
    }

    // Getter functions
    bool getState() const {
        return state;
    }

    std::string getNome() const {
        return nome;
    }
};