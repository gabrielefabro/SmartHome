#ifndef main_h
#define main_h

#include <hiredis/hiredis.h>
#include <postgresql/libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <ctime>
#include <chrono>
#include <vector>
#include "../../con2db/src/pgsql.h"
#include "../../Components/Camera/src/camera.h"
#include "../../Components/Device/src/device.h"
#include "../../Components/Light/src/light.h"
#include "../../Components/Conditioner/src/conditioner.h"
#include "../../Components/Sensor/src/sensor.h"
#include "../../Components/SensorGarden/src/sensorGarden.h"
#include "global.h"
#define DEBUG 1000

#define HORIZON 10 // TICKS



// LIGHT FUNCTIONS
int initTestLight(Light &light);
int testLight();
void log2lightdb(Con2DB db1, int id, int pid, light_type state, light_color color, int intensity, int t);
light_color stringToLightColor(const char* colorStr);
void int2stateLight(char *buf, light_type x);
light_color getRandomColor();
int changeIntensity();
const char* colorToString(light_color color);

// CAMERA FUNCTIONS
void int2stateCamera(char *buf, camera_type x);
void log2cameradb(Con2DB db1, int id, int pid, camera_type state, bool recording, int t);
int initTestCamera(Camera &camera);

// CONDITIONER FUNCTIONS
int changeRandomTemperature();
void int2stateConditioner(char *buf, conditioner_type x);
int testConditioner();
int initTestConditioner(Conditioner &conditioner);
void log2conditionerdb(Con2DB db1, int id, int pid, conditioner_type state, int temperature, int t);

// DEVICE FUNCTIONS
void int2stateDevice(char *buf, device_type x);
void log2devicedb(Con2DB db1, int id, int pid, device_type state, nome_type nome, int t, int inizio, int fine);
int changeInt();
const char* nomeToString(nome_type nomeDev);
int testDevice();
int initTestDevice(Device &device);

// SENSOR FUNCTIONS
void int2stateSensor(char *buf, sensor_type x);
void log2sensordb(Con2DB db1, int id, int pid, sensor_type state, bool movement, int t);
int testSensor();
int initTestSensor(Sensor &sensor);
void securityRecap(Con2DB db1, int pid);

// SENSORGARDEN FUNCTIONS
void int2stateSensorGarden(char *buf, sensorGarden_type x);
void log2sensorGardendb(Con2DB db1, int id, int pid, sensorGarden_type state, int humidity, int temperature, int t);
int testSensorGarden();
int initTestSensorGarden(SensorGarden &sensorGarden);

// MONITOR FUNCTIONS
int log2stdout(Con2DB db1, int pid);
void logActivity(Con2DB db1, const char *functionName, int pid);
void monitorResponseTime(const Con2DB& db, int pid, long nanos, long long requestTime, long responseTimeLimit);
void printTableData(PGresult *res);

// TIME FUNCTIONS
int msleep(long msec);
int micro_sleep(long usec);
int long get_nanos(void);
void init_time();
void update_time();
long long get_current_time_ns();
long int get_day_nanos(char *buf);
long int nanos2day(char *buf, long int nanosec);
void timeFlies(char *buf);


using namespace std;

#endif