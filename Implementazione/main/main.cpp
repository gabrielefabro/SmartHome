#include "camera.h"
#include "conditioner.h"
#include "device.h"
#include "light.h"
#include "sensor.h"
#include "sensorGarden.h"
#include "global.h"
#include <hiredis/hiredis.h>

//MODIFICARE CUERI

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

    Conditioner conditioner = initConditioner();
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

        // Test Camera
        initTestCamera(camera);
        log2cameradb(db1, camera.getId(), pid, nanos, camera.getState(), camera.getRecording());
        camera.next();

        // Test Conditioner
        initTestConditioner(conditioner);
        log2conditionerdb(db1, conditioner.getId(), pid, nanos, conditioner.getState(), conditioner.getTemperature());
        conditioner.next();

        // Test Device
        initTestDevice(device);
        log2devicedb(db1, device.getId(), pid, nanos, device.getState(), device.getNome());
        device.next();

        // Test luci
        initTestLight(light);
        log2lightdb(db1, light.getId(), pid, nanos, light.getState(), light.getColor(), light.getIntensity());
        light.next();

        // Test sensor
        initTestSensor(sensor);
        log2sensordb(db1, sensor.getId(), pid, nanos, sensor.getState(), sensor.getMovement());
        sensor.next();

        // Test sensorGarden
        initTestSensorGarden(sensorGarden);
        log2sensorGardendb(db1, sensorGarden.getId(), pid, nanos, sensorGarden.getState(), sensorGarden.getHumidity(), sensorGarden.getTemperature());
        sensorGarden.next();

        t++;

        /* sleep   */
        micro_sleep(500);
    }

    return 0;
}
