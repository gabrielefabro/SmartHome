#ifndef global_h
#define global_h

#include "main.h"

extern long int nanos;
extern long int last_nanos;
extern long int start;
extern double global_time_sec, timeadvance;


Camera initCamera();
Device initDevice();
Light initLight();
Sensor initSensor();
SensorGarden initSensorGarden();
Conditioner initConditioner();

#endif