#include "sensor.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <ctime>
#include <cstdlib>
#include "global.h"

int main()
{

    int t = 0;
    int pid;
    char buf[200];

    // Inizializza database
    Con2DB db1("localhost", "5432", "smarthome", "12345", "logdb_smarthome");

    pid = getpid();

    /* init time */
    init_time();

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Inizializza un oggetto Sensor
    Sensor sensor = initSensor();

    init_logdb(db1, pid, sensor.getId(), sensor.getState());

    while (t < HORIZON)
    {

        nanos_day = nanos2day(buf, nanos);

        // Invia ID e STATE a Redis
        redisReply *reply = (redisReply *)redisCommand(context, "SET sensor_id %d", sensor.getId());
        freeReplyObject(reply);

        reply = (redisReply *)redisCommand(context, "SET sensor_state %d", sensor.getState());
        freeReplyObject(reply);

        test();

        // Aspetta una risposta dal tester
        reply = (redisReply *)redisCommand(context, "GET tester_response");
        if (reply != nullptr && reply->str != nullptr)
        {
            freeReplyObject(reply);
        }

        char state[20];
        sensor_type sensorState = static_cast<sensor_type>(atoi(reply->str));
        int2state(state, sensorState);
        if (strcmp(state, "CHECKING") == 0)
        {
            int movement;
            sscanf(reply->str, "%d", &movement); // converte reply in int
            if (movement == 0)
            {
                sensor.setMovement(false);
            }
            else
            {
                sensor.setMovement(true);
                std::string message = "movement detected";
                redisReply *reply = (redisReply *)redisCommand(context, "PUBLISH channel %s", message.c_str());
                log2db(db1, pid, nanos, sensor.getState(), sensor.getMovement());
                freeReplyObject(reply);
            }
        }

        // Chiudi la connessione a Redis
        redisFree(context);

        sensor.next();

        t++;

        /* sleep   */
        micro_sleep(500);
    }

    log2stdout(db1, pid);
    return 0;
}
