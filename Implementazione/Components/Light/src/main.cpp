#include "light.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <ctime>
#include <cstdlib>


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

    // Inizializza un oggetto Light
    Light light = initLight();

    init_logdb(db1, pid, light.getId(), light.getState());

    while (t < HORIZON)
    {

        nanos_day = nanos2day(buf, nanos);
        
        // Invia ID e STATE a Redis
        redisReply *reply = (redisReply *)redisCommand(context, "SET light_id %d", light.getId());
        freeReplyObject(reply);

        reply = (redisReply *)redisCommand(context, "SET light_state %d", light.getState());
        freeReplyObject(reply);

        test();

        // Aspetta una risposta dal tester
        reply = (redisReply *)redisCommand(context, "GET tester_response");

        char state[20];
        light_type lightState = static_cast<light_type>(atoi(reply->str));
        int2state(state, lightState);

        if (strcmp(state, "change_color") == 0)
        {
            char colorStr[20];
            sscanf(reply->str, "%s", colorStr);
            light_color newColor = stringToLightColor(colorStr);
            light.setColor(newColor);
        }
        else if (strcmp(state, "change_intensity") == 0)
        {
            int newIntensity = reply->integer;
            light.setIntensity(newIntensity);
        }

        log2db(db1, pid, nanos, light.getState(), light.getColor(), light.getIntensity());
        freeReplyObject(reply);

        // Chiudi la connessione a Redis
        redisFree(context);

        light.next();

        t++;

        /* sleep   */
        micro_sleep(500);
    }

    return 0;
}
