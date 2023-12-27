#include <iostream>

class SensorGarden {
private:
    double humidity;     // Humidity of the ground
    double temperature;  // Garden's temperature

public:
    // Constructor
    Sensor() : humidity(0.0), temperature(0.0) {}

    // Function to check and calculate humidity based on input
    void checkHumidity(double temperature, double moisture) {
        // Simulate a basic humidity calculation (replace this with actual implementation)
        humidity = moisture - (0.1 * temperature);

        std::cout << "Humidity calculated: " << humidity << "%" << std::endl;
    }

    // Function to check temperature
    double checkTemperature(double newTemperature) {
        temperature = newTemperature;
        return temperature;
    }

    // Getter functions for humidity and temperature
    double getHumidity() const {
        return humidity;
    }

    double getTemperature() const {
        return temperature;
    }
};
