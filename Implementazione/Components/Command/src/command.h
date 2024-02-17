#include <iostream>
#include <random>
#include <hiredis/hiredis.h>
#include "../../con2db/src/pgsql.h"
#include <postgresql/libpq-fe.h>
#include <unistd.h>
#include "camera.h"
#include "device.h"
#include "light.h"
#include "sensor.h"
#include "sensorGarden.h"
#include "conditioner.h"
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