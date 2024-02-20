#include <iostream>
#include <random>
#include <hiredis/hiredis.h>
#include <postgresql/libpq-fe.h>
#include <unistd.h>
#include "sensor.h"
#include <string.h>

int main()
{
    auto tempo_iniziale = std::chrono::steady_clock::now();
    // Connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == NULL || context->err)
    {
        if (context)
        {
            std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
            redisFree(context);
        }
        else
        {
            std::cerr << "Impossibile connettersi a Redis." << std::endl;
        }
        exit(1);
    }

    Con2DB db1("localhost", "5432", "smarthome", "12345", "logdb_smarthome");

    int pid;

    /* init random number generator  */
    srand((unsigned)time(NULL));

    pid = getpid();

    printf("Start sensor with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());

    /* init sensor state */
    Sensor sensor = initSensor();

    redisReply *reply = (redisReply *)redisCommand(context, "SUBSCRIBE sensorChannel");
    freeReplyObject(reply);

    while (true)
    {
        sensor_type state;

        if (redisGetReply(context, (void **)&reply) != REDIS_OK)
        {
            std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
            exit(1);
        }
        if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
        {
            std::string received_message = reply->element[2]->str;
            std::cout << "Receiver: Messaggio ricevuto da Redis: " << received_message << std::endl;

            state = static_cast<sensor_type>(atoi(reply->element[2]->str));

            freeReplyObject(reply);

            if (state == SensorOFF)
            {
                sensor.setCheck(false);
            }
            else if (state == SensorON)
            {
                sensor.setCheck(true);
            }
            auto tempo_corrente = std::chrono::steady_clock::now();
            auto tempo_trascorso = std::chrono::duration_cast<std::chrono::milliseconds>(tempo_corrente - tempo_iniziale).count();
            log2sensordb(db1, sensor.getId(), pid, sensor.getState(), sensor.getCheck(), tempo_trascorso);
        }
    }
    redisFree(context);
    return 0;
}
