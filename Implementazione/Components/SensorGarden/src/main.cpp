#include "sensorGarden.h"
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

    // Inizializza un oggetto SensorGarden
    SensorGarden sensorGarden = initSensorGarden();

    init_logdb(db1, pid, sensorGarden.getId(), sensorGarden.getState());

    while (t < HORIZON)
    {

        nanos_day = nanos2day(buf, nanos);

        // Invia ID e STATE a Redis
        redisReply *reply = (redisReply *)redisCommand(context, "SET sensorGarden_id %d", sensorGarden.getId());
        freeReplyObject(reply);

        reply = (redisReply *)redisCommand(context, "SET sensorGarden_state %d", sensorGarden.getState());
        freeReplyObject(reply);

        test();
        
        // Aspetta una risposta dal tester
        reply = (redisReply *)redisCommand(context, "GET humidity");
        if (reply != nullptr && reply->str != nullptr)
        {
            freeReplyObject(reply);
        }

        int humidity = reply->integer;

        char state[20];
        sensorGarden_type sensorState = static_cast<sensorGarden_type>(atoi(reply->str));
        int2state(state, sensorState);

        if (strcmp(state, "change_light") == 0)
        {
            // Aspetta una risposta dal tester
            reply = (redisReply *)redisCommand(context, "GET temperature");
            if (reply != nullptr && reply->str != nullptr)
            {
                freeReplyObject(reply);
            }

            int temperature = reply->integer;

            // Adjust the lights based on humidity and temperature conditions
            if (humidity > 50 && temperature > 25)
            {
                std::cout << "luci spente" << std::endl;
            }
            else
            {
                std::cout << "luci accese" << std::endl;
            }
            log2db(db1, pid, nanos, sensorGarden.getState(), sensorGarden.getHumidity(), sensorGarden.getTemperature());
        }
        else if (strcmp(state, "set_sprinklers") == 0)
        {
            // Adjust irrigation based on humidity conditions
            if (humidity < 30)
            {
                std::cout << "irrigatori accesi" << std::endl;
            }
            else
            {
                std::cout << "irrigatori spenti" << std::endl;
            }
            log2db(db1, pid, nanos, sensorGarden.getState(), sensorGarden.getHumidity(), sensorGarden.getTemperature());
        }

        // Chiudi la connessione a Redis
        redisFree(context);

        sensorGarden.next();

        t++;

        /* sleep   */
        micro_sleep(500);
    }

    log2stdout(db1, pid);
    return 0;
}
