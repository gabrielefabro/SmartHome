#include "../../Components/Camera/src/camera.h"
#include "../../Components/Device/src/device.h"
#include "../../Components/Light/src/light.h"
#include "../../Components/Conditioner/src/conditioner.h"
#include "../../Components/Sensor/src/sensor.h"
#include "../../Components/SensorGarden/src/sensorGarden.h"
#include "global.h"
#include "main.h"
#include <hiredis/hiredis.h>

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

    // inizializzo le componenti
    Camera camera = initCamera();
    log2cameradb(db1, camera.getId(), pid, nanos, camera.getState(), camera.getRecording());

    Conditioner conditioner = initConditioner(); // gestione temperatura non può andare da 0 a 40
    log2conditionerdb(db1, conditioner.getId(), pid, nanos, conditioner.getState(), conditioner.getTemperature());

    Device device = initDevice();
    log2devicedb(db1, device.getId(), pid, nanos, device.getState(), device.getNome());

    Light light = initLight();
    log2lightdb(db1, light.getId(), pid, nanos, light.getState(), light.getColor(), light.getIntensity());

    Sensor sensor = initSensor();
    log2sensordb(db1, sensor.getId(), pid, nanos, sensor.getState(), sensor.getMovement());

    SensorGarden sensorGarden = initSensorGarden();
    log2sensorGardendb(db1, sensorGarden.getId(), pid, nanos, sensorGarden.getState(), sensorGarden.getHumidity(), sensorGarden.getTemperature());

    while (t < HORIZON)
    {

        nanos_day = nanos2day(buf, nanos);

        long long requestTime = get_current_time_ns();

        // Test sensor
        initTestSensor(sensor);
        logActivity(db1, "Test Sensor", pid);
        log2sensordb(db1, sensor.getId(), pid, nanos, sensor.getState(), sensor.getMovement());
        if (sensor.getMovement() == true) {
            securityRecap(db1, pid);
        }
        sensor.next();

        // Test Camera
        logActivity(db1, "Test Camera", pid);
        initTestCamera(camera);
        log2cameradb(db1, camera.getId(), pid, nanos, camera.getState(), camera.getRecording());
        camera.next();

        // Test Conditioner
        logActivity(db1, "Test Conditioner", pid);
        initTestConditioner(conditioner);
        log2conditionerdb(db1, conditioner.getId(), pid, nanos, conditioner.getState(), conditioner.getTemperature());
        conditioner.next();

        // Test Device
        logActivity(db1, "Test Device", pid);
        initTestDevice(device);
        log2devicedb(db1, device.getId(), pid, nanos, device.getState(), device.getNome());
        device.next();

        // Test luci
        logActivity(db1, "Test Light", pid);
        initTestLight(light);
        log2lightdb(db1, light.getId(), pid, nanos, light.getState(), light.getColor(), light.getIntensity());
        light.next();

        // Test sensorGarden
        logActivity(db1, "Test SensorGarden", pid);
        initTestSensorGarden(sensorGarden);
        log2sensorGardendb(db1, sensorGarden.getId(), pid, nanos, sensorGarden.getState(), sensorGarden.getHumidity(), sensorGarden.getTemperature());
        sensorGarden.next();

        monitorResponseTime(db1, pid, nanos, requestTime, 5000000000); // Limite di 5 secondi

        t++;
        std::cout << t << std::endl;
        /* sleep   */
        micro_sleep(500);

    }

    return 0;
}
