#include <iostream>

class SensorGarden
{
private:
    double humidity;    // Humidity of the ground
    double temperature; // Garden's temperature
    int id;
    RedisManager &redisManager;

public:
    // Constructor
    SensorGarden::SensorGarden(int sensorGardenId, RedisManager &redisManager) : humidity(0.0), temperature(0.0), id(sensorGardenId), redisManager(redisManager) {}
    // Function to check and calculate humidity based on input
    void checkHumidity(double temperature, double moisture)
    {
        // Simulate a basic humidity calculation (replace this with actual implementation)
        humidity = moisture - (0.1 * temperature);

        std::cout << "Humidity calculated: " << humidity << "%" << std::endl;
        redisManager.sendCommand("LPUSH sensor_garden_events:check_humidity " + std::to_string(id) + " " + getCurrentTimestamp());
    }

    // Function to check temperature
    double checkTemperature(double newTemperature)
    {
        temperature = newTemperature;
        redisManager.sendCommand("LPUSH sensor_garden_events:check_temperature "  + getCurrentTimestamp());
        return temperature;
    }

    // Getter functions for humidity and temperature
    double getHumidity() const
    {
        return humidity;
    }

    double getTemperature() const
    {
        return temperature;
    }
};
