#include "camera.h"
#include "conditioner.h"
#include "device.h"
#include "light.h"
#include "sensor.h"
#include "sensorGarden.h"
#include "globalCa.h"
#include "globalCo.h"
#include "globalDe.h"
#include "globalLi.h"
#include "globalSe.h"
#include "globalSg.h"





int main()
{
    Camera camera = initCamera();
    Conditioner conditioner = initConditioner();
    Device device = initDevice();
    Light light = initLight();
    Sensor sensor = initSensor();
    SensorGarden SensorGarden = initSensorGarden();

    // Itero su ogni elemento e controllo lo stato, in base allo stato gli faccio fare qualcosa
    
    return 0;
}
