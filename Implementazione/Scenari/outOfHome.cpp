#include <iostream>
#include <string>
#include "../Components/camera.cpp"
#include "../Components/light.cpp"
#include "../Components/stove.cpp"
#include "../Components/conditioner.cpp"
#include "../Components/sensor.cpp"
#include <vector>

class OutOfHome
{
private:
    std::vector<Light> lights;
    std::vector<Camera> cameras;
    std::vector<Sensor> sensors;
    std::vector<Stove> stoves;
    std::vector<Conditioner> conditioners;
    std::vector<Device> shutters;

public:
     OutOfHome(const std::vector<Light> &lightsList, const std::vector<Camera> &camerasList, const std::vector<Sensor> &sensorsList,const std::vector<Stove> &stovesList, const std::vector<Conditioner> &conditionersList, const std::vector<Device> &shuttersList):lights(lightsList), cameras(camerasList), sensors(sensorsList), stoves(stovesList), conditioners(conditionersList), shutters(shuttersList) {}
    
    // Metodi per controllare i dispositivi
    void turnOffLights() {
        for (Light &light : lights) {
            // Spegni ogni luce
            light.turnOff();
        }
    }

    void turnOnCameras() {
        for (Camera &camera : cameras) {
            // Accendi ogni telecamera
            camera.turnOn();
        }
    }

    void activateSensors() {
        for (Sensor &sensor : sensors) {
            // Attiva ogni sensore
            sensor.activate();
        }
    }

    void turnOffStoves() {
        for (Stove &stove : stoves) {
            // Spegni ogni stufa
            stove.turnOff();
        }
    }

    void turnOffConditioners() {
        for (Conditioner &conditioner : conditioners) {
            // Spegni ogni condizionatore
            conditioner.turnOff();
        }
    }

    void turnOffShutters() {
        for (Device &shutter : shutters) {
            // Spegni ogni persiana
            shutter.turnOff();
        }
    }
};

int main() {
    // Creazione di alcune istanze di luci, telecamere, sensori, stufe, condizionatori, persiane
    std::vector<Light> lights{
        Light("LivingRoomLight", 2),
        Light("BedroomLight", 4),
        // ... aggiungi altre luci se necessario
    };

    std::vector<Camera> cameras{
        Camera(6),
        Camera(10),
        // ... aggiungi altre telecamere se necessario
    };

    std::vector<Sensor> sensors{
        Sensor(8),
        Sensor(99),
        // ... aggiungi altri sensori se necessario
    };

    std::vector<Stove> stoves{
        Stove("stove", 86),
        Stove("stove", 65),
        // ... aggiungi altre stufe se necessario
    };

    std::vector<Conditioner> conditioners{
        Conditioner("conditioner", 11),
        Conditioner("conditioner", 63),
        // ... aggiungi altri condizionatori se necessario
    };

    std::vector<Device> shutters{
        Device("shutter", 92),
        Device("shutter", 32),
        // ... aggiungi altre persiane se necessario
    };

    // Creazione dell'istanza di OutOfHome con le liste di dispositivi
    OutOfHome myHome(lights, cameras, sensors, stoves, conditioners, shutters);

    // Test delle funzioni di controllo dei dispositivi
    myHome.turnOffLights();
    myHome.turnOnCameras();
    myHome.activateSensors();
    myHome.turnOffStoves();
    myHome.turnOffConditioners();
    myHome.turnOffShutters();

    return 0;
}

