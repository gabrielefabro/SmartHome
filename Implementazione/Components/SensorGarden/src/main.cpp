#include <iostream>
#include <random>
#include <hiredis/hiredis.h>
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

    printf("Start light with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());

    /* init traffic light state */
    SensorGarden sensorGarden = initSensorGarden();

    redisReply *reply = (redisReply *)redisCommand(context, "SUBSCRIBE userInput_channel");
    freeReplyObject(reply);

    while (true)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 100);
        int humidity, temperature;
        sensorGarden_type state;

        if (dis(gen) > 5)
        {
             if (redisGetReply(context, (void **)&reply) != REDIS_OK)
            {
                std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                exit(1);
            }
            else
            {
                std::cout << "ehehehehhe: SIUUUUUUUUUUUUUUUu " << std::endl;
            }
            if (reply->type == REDIS_REPLY_ARRAY && strcmp(reply->element[0]->str, "message") == 0)
            {
                std::cout << "coddio3" << std::endl;
                response = "ok";

                if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                {
                    std::string received_message = reply->element[2]->str;
                    std::cout << "Receiver: Messaggio ricevuto da Redis: " << received_message << std::endl;

                    state = static_cast<sensorGarden_type>(atoi(reply->element[2]->str));

                    freeReplyObject(reply);

                    if (state == SensorGardenON)
                    {
                        humidity = std::rand() % 101;
                        temperature = std::rand() % 46;
                    }
                    else if (state == SensorGardenOFF)
                    {
                        humidity = 0;
                        temperature = 0;
                    }

                    log2sensorGardendb(db1, sensorGarden.getId(), pid, sensorGarden.getState(), sensorGarden.getHumidity(), sensorGarden.getTemperature());
                }

                // Scriviamo una risposta sulla stessa stream
                redisReply *publish_reply = (redisReply *)redisCommand(context, "PUBLISH sensorGardenChannel %s", response);
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
            freeReplyObject(reply);
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
