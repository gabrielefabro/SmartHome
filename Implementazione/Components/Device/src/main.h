#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <cassert>
#include <cerrno>
#include "device.h"
#include "global.h"
#include "initDevice.cpp"
#include "../../../con2db/pgsql.h"

#define DEBUG 1000

#define HORIZON 10 // TICKS

int msleep(long msec);
int micro_sleep(long usec);
int long get_nanos(void);
void init_time();
void update_time();

long int get_day_nanos(char *buf);
void int2state(char *buf, device_type x);
nome_type stringToNome(const char* nomeDev);
void init_logdb(Con2DB db1, int pid);
void log2db(Con2DB db1, int pid, long int nanos_day, device_type x);
long int nanos2day(char *buf, long int nanosec);
void log2stdout(Con2DB db1, int pid);

using namespace std;

#endif
