#ifndef main_h
#define main_h

#include <hiredis/hiredis.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include "../con2db/pgsql.h"
#include "camera.h"
#include "device.h"
#include "light.h"
#include "conditioner.h"
#include "sensor.h"
#include "sensorGarden.h"
#include "global.h"

#define DEBUG 1000

#define HORIZON 10 // TICKS



// LIGHT FUNCTION
int initTestLight(Light light);
int testLight();
void log2lightdb(Con2DB db1, int id, int pid, long int nanosec, light_type state, light_color color, int intensity);
light_color stringToLightColor(const char* colorStr);
void int2stateLight(char *buf, light_type x);
light_color getRandomColor();
int changeIntensity();

// CAMERA FUNCTION
void int2stateCamera(char *buf, camera_type x);
void log2cameradb(Con2DB db1, int id, int pid, long int nanosec, camera_type state, bool recording);
int initTestCamera(Camera camera);

// CONDITIONER FUNCTION
int changeRandomTemperature();
void int2stateConditioner(char *buf, conditioner_type x);
int testConditioner();
int initTestConditioner(Conditioner conditioner);
void log2conditionerdb(Con2DB db1, int id, int pid, long int nanosec, conditioner_type state, int temperature);

// DEVICE FUNCTION
void int2stateDevice(char *buf, device_type x);
void log2devicedb(Con2DB db1, int id, int pid, long int nanosec, device_type state, nome_type nome);
int changeInt();
nome_type stringToNome(const char* nomeDev);
int testDevice();
int initTestDevice(Device device);

// SENSOR FUNCTION
void int2stateSensor(char *buf, sensor_type x);
void log2sensordb(Con2DB db1, int id, int pid, long int nanosec, sensor_type state, bool movement);
int testSensor();
int initTestSensor(Sensor sensor);

// SENSORGARDEN FUNCTION
void int2stateSensorGarden(char *buf, sensorGarden_type x);
void log2sensorGardendb(Con2DB db1, int id, int pid, long int nanosec, sensorGarden_type state, int humidity, int temperature);
int testSensorGarden();
int initTestSensorGarden(SensorGarden sensorGarden);


int msleep(long msec);
int micro_sleep(long usec);
int long get_nanos(void);
void init_time();
void update_time();

long int get_day_nanos(char *buf);
long int nanos2day(char *buf, long int nanosec);
void log2stdout(Con2DB db1, int pid);

using namespace std;

#endif