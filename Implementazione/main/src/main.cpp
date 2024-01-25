#include "../../Components/Camera/src/camera.h"
#include "../../Components/Device/src/device.h"
#include "../../Components/Light/src/light.h"
#include "../../Components/Conditioner/src/conditioner.h"
#include "../../Components/Sensor/src/sensor.h"
#include "../../Components/SensorGarden/src/sensorGarden.h"
#include "global.h"
#include "main.h"

int main()
{
    // variabili
    int t = 0;
    int pid;
    char buf[200];

    // Inizializza database
    Con2DB db1("localhost", "5432", "smarthome", "12345", "logdb_smarthome");

    // pid processo
    pid = getpid();

    // Init time
    init_time();

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::srand(static_cast<unsigned>(seed));

    nanos = get_nanos();

    // inizializzo le componenti
    Camera camera = initCamera();
    log2cameradb(db1, camera.getId(), pid, nanos, camera.getState(), camera.getRecording(), t);

    Conditioner conditioner = initConditioner(); // gestione temperatura non può andare da 0 a 40
    log2conditionerdb(db1, conditioner.getId(), pid, nanos, conditioner.getState(), conditioner.getTemperature(), t);

    Device device = initDevice();
    std::tuple<int, int> risultato = device.getProgrammed();
    int inizio = std::get<0>(risultato);
    int fine = std::get<1>(risultato);
    log2devicedb(db1, device.getId(), pid, nanos, device.getState(), device.getNome(), t, inizio, fine);

    Light light = initLight();
    log2lightdb(db1, light.getId(), pid, nanos, light.getState(), light.getColor(), light.getIntensity(), t);

    Sensor sensor = initSensor();
    log2sensordb(db1, sensor.getId(), pid, nanos, sensor.getState(), sensor.getMovement(), t);

    SensorGarden sensorGarden = initSensorGarden();
    log2sensorGardendb(db1, sensorGarden.getId(), pid, nanos, sensorGarden.getState(), sensorGarden.getHumidity(), sensorGarden.getTemperature(), t);

    while (t < HORIZON)
    {
        long long requestTime = get_current_time_ns();

        // Test sensor
        initTestSensor(sensor);
        logActivity(db1, "Test Sensor", pid);
        log2sensordb(db1, sensor.getId(), pid, nanos, sensor.getState(), sensor.getMovement(), t);
        if (sensor.getMovement() == true)
        {
            securityRecap(db1, pid, nanos);
        }
        sensor.setState(sensor.next());

        // Test Camera
        logActivity(db1, "Test Camera", pid);
        initTestCamera(camera);
        log2cameradb(db1, camera.getId(), pid, nanos, camera.getState(), camera.getRecording(), t);
        camera.setState(camera.next());

        // Test Conditioner
        logActivity(db1, "Test Conditioner", pid);
        initTestConditioner(conditioner);
        log2conditionerdb(db1, conditioner.getId(), pid, nanos, conditioner.getState(), conditioner.getTemperature(), t);
        conditioner.setState(conditioner.next());

        // Test Device
        logActivity(db1, "Test Device", pid);
        initTestDevice(device);
        std::tuple<int, int> risultato = device.getProgrammed();
        inizio = std::get<0>(risultato);
        fine = std::get<1>(risultato);
        log2devicedb(db1, device.getId(), pid, nanos, device.getState(), device.getNome(), t, inizio, fine);
        device.setState(device.next());

        // Test luci
        logActivity(db1, "Test Light", pid);
        initTestLight(light);
        log2lightdb(db1, light.getId(), pid, nanos, light.getState(), light.getColor(), light.getIntensity(), t);
        light.setState(light.next());

        // Test sensorGarden
        logActivity(db1, "Test SensorGarden", pid);
        initTestSensorGarden(sensorGarden);
        log2sensorGardendb(db1, sensorGarden.getId(), pid, nanos, sensorGarden.getState(), sensorGarden.getHumidity(), sensorGarden.getTemperature(), t);
        sensorGarden.setState(sensorGarden.next());

        monitorResponseTime(db1, pid, nanos, requestTime, 5000000000); // Limite di 5 secondi

        t++;
        /* sleep   */
        micro_sleep(500);
        update_time();
    }

    // log2stdout(db1,pid); Va rifatta

    return 0;
}
