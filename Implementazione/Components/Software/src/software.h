#ifndef SOFTWARE_H
#define SOFTWARE_H

#include <cstdlib>
#include <iostream>
#include <random>
#include "pgsql.h"
#include <unistd.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include <chrono>



void timeFlies(char *buf);
void fail(Con2DB db1, int pid, char *component);


#endif