#include <iostream>
#include <random>
#include <hiredis/hiredis.h>
#include "../../../con2db/src/pgsql.h"
#include <postgresql/libpq-fe.h>
#include <unistd.h>
#include "../../Camera/src/camera.h"
#include "../../Device/src/device.h"
#include "../../Light/src/light.h"
#include "../../Sensor/src/sensor.h"
#include "../../SensorGarden/src/sensorGarden.h"
#include "../../Conditioner/src/conditioner.h"
#include <string.h>

#define HORIZON 10

typedef enum
{
    Camera,
    Conditioner,
    Device,
    Light,
    Sensor,
    SensorGarden
} components;

std::string componentToString(components comp);
int changeRandomTemperature();
void int2stateCamera(char *buf, camera_type x);
int changeInt();
light_color getRandomColor();
const char* colorToString(light_color color);
int changeIntensity();