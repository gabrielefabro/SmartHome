#include <iostream>
#include <random>
#include <hiredis/hiredis.h>
#include <postgresql/libpq-fe.h>
#include <unistd.h>
#include "sensorGarden.h"
#include <string.h>

int main()
{
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
    PGresult *res;
    char buf[200];
    int pid;
    int t = 0;
    const char *response;

    /* init random number generator  */
    srand((unsigned)time(NULL));

    pid = getpid();

    printf("Start sensorGarden with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());

    /* init sensor state */
    SensorGarden sensorGarden = initSensorGarden();

    redisReply *reply = (redisReply *)redisCommand(context, "SUBSCRIBE sensorGardenChannel");
    freeReplyObject(reply);

    while (true)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 100);
        sensorGarden_type state;

        if (true)
        {

            response = "ok";
            if (redisGetReply(context, (void **)&reply) != REDIS_OK)
            {
                std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                exit(1);
            }
            if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
            {
                std::string received_message = reply->element[2]->str;
                std::cout << "Receiver: Messaggio ricevuto da Redis: " << received_message << std::endl;

                state = static_cast<sensorGarden_type>(atoi(reply->element[2]->str));

                freeReplyObject(reply);

                if (state == SensorGardenOFF)
                {
                    sensorGarden.setHumidity(0);
                    sensorGarden.setTemperature(0);
                }
                else if (state == SensorGardenON)
                {
                    sensorGarden.setHumidity(rand() % 100);
                    sensorGarden.setTemperature(rand() % 46);
                }
                std::cout << "tempeartura: " << sensorGarden.getTemperature() << " umidità: " << sensorGarden.getHumidity() << std::endl;
                log2sensorGardendb(db1, sensorGarden.getId(), pid, sensorGarden.getState(), sensorGarden.getTemperature(), sensorGarden.getHumidity());

                // Scriviamo una risposta sulla stessa stream
                redisReply *publish_reply = (redisReply *)redisCommand(context, "PUBLISH sensorChannel %s", response);
                if (publish_reply == NULL)
                {
                    std::cerr << "Errore nella pubblicazione della risposta su Redis." << std::endl;
                }
                else
                {
                    std::cout << "Publisher: Risposta pubblicata su Redis." << std::endl;
                    freeReplyObject(publish_reply);
                }
            }
        }
        else
        {
            response = "no";
            // Scriviamo una risposta sulla stessa stream
            redisReply *publish_reply = (redisReply *)redisCommand(context, "PUBLISH response_channel %s", response);
            if (publish_reply == NULL)
            {
                std::cerr << "Errore nella pubblicazione della risposta su Redis." << std::endl;
            }
            else
            {
                std::cout << "Publisher: Risposta pubblicata su Redis." << std::endl;
                freeReplyObject(publish_reply);
            }
        }
    }
    redisFree(context);
    return 0;
}
