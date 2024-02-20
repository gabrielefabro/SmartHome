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
#include "../../Command/src/command.h"
std::string componentToString(components comp);
void log2db(Con2DB db1, std::string comp, const char *state);

#endif