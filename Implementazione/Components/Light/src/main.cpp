#include <iostream>
#include <random>
#include <unistd.h>
#include "light.h"
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

    /* init light state */
    Light light = initLight();

    redisReply *reply = (redisReply *)redisCommand(context, "SUBSCRIBE userInput_channel");
    freeReplyObject(reply);

    while (true)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 100);
        int countMessage = 0;
        light_color color;
        light_type state;
        int intensity;

        if (dis(gen) > 5)
        {
            std::cout << "coddio2" << std::endl;
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

                // Utilizziamo redisGetReply per ottenere la risposta da Redis
                while (countMessage < 3)
                {
                    if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                    {
                        std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                        exit(1);
                    }
                    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                    {
                        std::string message = reply->element[2]->str;
                        std::cout << "Messaggio ricevuto da Redis: " << message << std::endl;

                        if (countMessage == 0)
                        {
                            state = static_cast<light_type>(atoi(reply->element[2]->str));
                            std::cout << countMessage << std::endl;
                        }
                        else if (countMessage == 1)
                        {
                            std::cout << countMessage << std::endl;  
                            color = static_cast<light_color>(atoi(reply->element[2]->str));
                        }
                        else if (countMessage == 2)
                        {
                            std::cout << countMessage << std::endl;  
                            intensity = (atoi(reply->element[2]->str));
                        }

                        freeReplyObject(reply);
                    }
                    countMessage++;
                }

            }

            if (state == change_color)
            {
                light.setColor(color);
            }
            else if (state == change_intensity)
            {
                light.setIntensity(intensity);
            }

            light.setState(state);
            log2lightdb(db1, light.getId(), pid, light.getState(), light.getColor(), light.getIntensity());

            // Scriviamo una risposta sulla stessa stream
            redisReply *publish_reply = (redisReply *)redisCommand(context, "PUBLISH lightChannel %s", response);
            if (publish_reply == NULL)
            {
                std::cerr << "Errore nella pubblicazione della risposta su Redis." << std::endl;
            }
            else
            {
                std::cout << "Publisher: Risposta pubblicata su Redis." << std::endl;
                freeReplyObject(publish_reply);
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
