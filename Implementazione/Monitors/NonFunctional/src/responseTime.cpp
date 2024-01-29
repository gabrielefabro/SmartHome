#include <iostream>
#include "../../../main/src/main.h"

// Monitor per il requisito non funzionale di tempestività nella risposta
void monitorResponseTime(const Con2DB& db, int pid, long nanos, long long requestTime, long responseTimeLimit) {

    long elapsedTime = nanos - requestTime;
    if (elapsedTime > responseTimeLimit) {
        std::cout << "Warning: Response time exceeded the limit at time " << nanos << std::endl;
    }
}