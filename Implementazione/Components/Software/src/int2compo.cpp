#include <string>
#include "software.h"

const char* componentToString(components comp) {
    switch (comp) {
        case Camera:
            return "Camera";
        case Conditioner:
            return "Conditioner";
        case Device:
            return "Device";
        case Light:
            return "Light";
        case Sensor:
            return "Sensor";
        case SensorGarden:
            return "SensorGarden";
        default:
            return "Unknown";
    }
}
