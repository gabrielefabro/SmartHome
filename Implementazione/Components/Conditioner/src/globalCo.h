#ifndef globalco_h
#define globalco_h

#include "main.h"

extern long int nanos;
extern long int last_nanos;
extern long int start;
extern long int nanos_day;
extern double global_time_sec, timeadvance;
extern char sqlcmd[1000];

Conditioner initConditioner();

#endif