#include <iostream>
#include <string>
#include "device.cpp"

class Light : public Device
{
private:
    std::string color;
    int intensity;
    int id;

public:
    // Constructor
    Light(std::string deviceName, int lightId) : Device(deviceName, lightId), color("White"), intensity(50), id(lightId) {}

    // Function to change the color of the light
    void changeColor(std::string newColor)
    {
        color = newColor;
        std::cout << "light color changed to " << color << std::endl;
    }

    // Function to change the intensity of the light
    void changeIntensity(int newIntensity)
    {
        if (newIntensity >= 1 && newIntensity <= 100)
        {
            intensity = newIntensity;
            std::cout << "light intensity changed to " << intensity << std::endl;
        }
        else
        {
            std::cout << "Error: Intensity value must be between 1 and 100." << std::endl;
        }
    }

    // Getter functions
    std::string getColor() const
    {
        return color;
    }

    int getIntensity() const
    {
        return intensity;
    }
};

