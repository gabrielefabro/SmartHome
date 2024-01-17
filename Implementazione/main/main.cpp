#include "camera.h"
#include "conditioner.h"
#include "device.h"
#include "light.h"
#include "sensor.h"
#include "sensorGarden.h"
#include "global.h"
#include <hiredis/hiredis.h>

int main()
{
    Camera camera = initCamera();
    Conditioner conditioner = initConditioner();
    Device device = initDevice();
    Light light = initLight();
    Sensor sensor = initSensor();
    SensorGarden SensorGarden = initSensorGarden();

    // Itero su ogni elemento e controllo lo stato, in base allo stato gli faccio fare qualcosa

    int t = 0;
    int pid;
    char buf[200];

    // Inizializza database
    Con2DB db1("localhost", "5432", "smarthome", "12345", "logdb_smarthome");

    pid = getpid();

    /* init time */
    init_time();

    while (t < HORIZON)
    {

        nanos_day = nanos2day(buf, nanos);
        init_logdb(db1, pid, light.getId(), light.getState());
        initTestLight(light,db1,pid);

        log2db(db1, pid, nanos, light.getState(), light.getColor(), light.getIntensity());

        light.next();

        t++;

        /* sleep   */
        micro_sleep(500);
    }

    return 0;
}
