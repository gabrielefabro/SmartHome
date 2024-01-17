#ifndef main_h
#define main_h

#include <hiredis/hiredis.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stddef.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/times.h>
#include <cassert>
#include <cerrno>
#include "../con2db/pgsql.h"
#include "camera.h"
#include "device.h"
#include "light.h"
#include "conditioner.h"
#include "sensor.h"
#include "sensorGarden.h"

#define DEBUG 1000

#define HORIZON 10 // TICKS

int changeRandomTemperature();

int initTestLight(Light light, Con2DB db1, int pid);
int testLight();

int msleep(long msec);
int micro_sleep(long usec);
int long get_nanos(void);
void init_time();
void update_time();

long int get_day_nanos(char *buf);
void int2state(char *buf, conditioner_type x);
void init_logdb(Con2DB db1, int pid, int id, conditioner_type state);
void log2db(Con2DB db1, int pid, long int nanos_day, conditioner_type state, int temperature);
long int nanos2day(char *buf, long int nanosec);
void log2stdout(Con2DB db1, int pid);

using namespace std;

#endif