#include "sensor.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <ctime>
#include <cstdlib>

int main()
{

    int t = 0;

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Inizializza un oggetto Sensor
    Sensor sensor = initSensor();

    while (t < HORIZON)
    {
        // Invia ID e STATE a Redis
        redisReply *reply = (redisReply *)redisCommand(context, "SET sensor_id %d", sensor.getId());
        freeReplyObject(reply);

        reply = (redisReply *)redisCommand(context, "SET sensor_state %d", sensor.getState());
        freeReplyObject(reply);

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
            }
        }

        // Chiudi la connessione a Redis
        redisFree(context);

        sensor.next();

        t++;

        /* sleep   */
        micro_sleep(500);
    }

    return 0;
}
