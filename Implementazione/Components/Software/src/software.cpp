#include <iostream>
#include <hiredis/hiredis.h>
#include "../../Command/src/command.h"


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

    // Sottoscrizione al canale
    redisReply *reply = (redisReply *)redisCommand(context, "SUBSCRIBE userInput_channel");
    if (reply == NULL || context->err)
    {
        std::cerr << "Errore durante la sottoscrizione al canale." << std::endl;
        exit(1);
    }
    freeReplyObject(reply);

    // Ascolto dei messaggi
    while (true)
    {
        if (redisGetReply(context, (void **)&reply) != REDIS_OK)
        {
            std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
            exit(1);
        }

        if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
        {
            std::string received_message = reply->element[2]->str;
            std::cout << "Receiver: Messaggio ricevuto da Redis: " << received_message << std::endl;

            if (received_message == "yeahBAby")
            {
                freeReplyObject(reply);
                reply = (redisReply *)redisCommand(context, "GET comp");
                components comp = static_cast<components>(atoi(reply->str));
                freeReplyObject(reply);

                switch (comp)
                {
                case Camera: {
                    reply = (redisReply *)redisCommand(context, "GET comando");
                    camera_type state = static_cast<camera_type>(atoi(reply->str));
                    freeReplyObject(reply);

                    reply = (redisReply *)redisCommand(context, "PUBLISH cameraChannel %s", state);
                    freeReplyObject(reply);

                    // Ricevi i messaggi per un periodo di tempo
                    const int TIMEOUT_SECONDS = 1;
                    time_t startTime = time(NULL);
                    while (difftime(time(NULL), startTime) < TIMEOUT_SECONDS)
                    {
                        reply = (redisReply *)redisCommand(context, "GET cameraChannel");
                        if (reply != NULL && reply->type == REDIS_REPLY_ARRAY && strcmp(reply->element[0]->str, "message") == 0)
                        {
                            std::string message = reply->element[2]->str;
                            std::cout << "Messaggio ricevuto da Redis: " << message << std::endl;
                            freeReplyObject(reply);
                        }
                    }

                    break;
                }
                case Conditioner: {
                    reply = (redisReply *)redisCommand(context, "GET comando");
                    conditioner_type state = static_cast<conditioner_type>(atoi(reply->str));
                    freeReplyObject(reply);

                    reply = (redisReply *)redisCommand(context, "GET temperature");
                    int temperature = (atoi(reply->str));
                    freeReplyObject(reply);

                    // Definisci un array contenente i valori da inviare
                    int values[] = {state, temperature};
                    const int NUM_MESSAGES = sizeof(values) / sizeof(values[0]);

                    for (int i = 0; i < NUM_MESSAGES; ++i)
                    {
                        // Invia il messaggio a Redis
                        reply = (redisReply *)redisCommand(context, "PUBLISH conditionerChannel %d", values[i]);
                        if (reply != NULL)
                        {
                            freeReplyObject(reply);
                        }
                        else
                        {
                            std::cerr << "Errore nell'invio del messaggio " << i + 1 << " a Redis." << std::endl;
                        }

                        // Attendi un breve periodo di tempo tra l'invio dei messaggi
                        usleep(1000000); // Attendi 1 secondo (1000000 microsecondi)
                    }
                    freeReplyObject(reply);

                    // Ricevi i messaggi per un periodo di tempo
                    const int TIMEOUT_SECONDS = 1;
                    time_t startTime = time(NULL);
                    while (difftime(time(NULL), startTime) < TIMEOUT_SECONDS)
                    {
                        reply = (redisReply *)redisCommand(context, "GET conditionerChannel");
                        if (reply != NULL && reply->type == REDIS_REPLY_ARRAY && strcmp(reply->element[0]->str, "message") == 0)
                        {
                            std::string message = reply->element[2]->str;
                            std::cout << "Messaggio ricevuto da Redis: " << message << std::endl;
                            freeReplyObject(reply);
                        }
                    }
                    break;
                }
                case Device: {
                    reply = (redisReply *)redisCommand(context, "GET comando");
                    conditioner_type state = static_cast<conditioner_type>(atoi(reply->str));
                    freeReplyObject(reply);

                    reply = (redisReply *)redisCommand(context, "GET inizio");
                    int inizio = (atoi(reply->str));
                    freeReplyObject(reply);

                    reply = (redisReply *)redisCommand(context, "GET fine");
                    int fine = (atoi(reply->str));
                    freeReplyObject(reply);

                    // Definisci un array contenente i valori da inviare
                    int values[] = {state, inizio, fine};
                    const int NUM_MESSAGES = sizeof(values) / sizeof(values[0]);

                    for (int i = 0; i < NUM_MESSAGES; ++i)
                    {
                        // Invia il messaggio a Redis
                        reply = (redisReply *)redisCommand(context, "PUBLISH deviceChannel %d", values[i]);
                        if (reply != NULL)
                        {
                            freeReplyObject(reply);
                        }
                        else
                        {
                            std::cerr << "Errore nell'invio del messaggio " << i + 1 << " a Redis." << std::endl;
                        }

                        // Attendi un breve periodo di tempo tra l'invio dei messaggi
                        usleep(1000000); // Attendi 1 secondo (1000000 microsecondi)
                    }
                    freeReplyObject(reply);

                    // Ricevi i messaggi per un periodo di tempo
                    const int TIMEOUT_SECONDS = 1;
                    time_t startTime = time(NULL);
                    while (difftime(time(NULL), startTime) < TIMEOUT_SECONDS)
                    {
                        reply = (redisReply *)redisCommand(context, "GET deviceChannel");
                        if (reply != NULL && reply->type == REDIS_REPLY_ARRAY && strcmp(reply->element[0]->str, "message") == 0)
                        {
                            std::string message = reply->element[2]->str;
                            std::cout << "Messaggio ricevuto da Redis: " << message << std::endl;
                            freeReplyObject(reply);
                        }
                    }
                    break;
                }
                case Light: {
                    reply = (redisReply *)redisCommand(context, "GET comando");
                    light_type state = static_cast<light_type>(atoi(reply->str));
                    freeReplyObject(reply);

                    reply = (redisReply *)redisCommand(context, "GET color");
                    light_color color = static_cast<light_color>(atoi(reply->str));
                    freeReplyObject(reply);

                    reply = (redisReply *)redisCommand(context, "GET intensity");
                    int intensity = (atoi(reply->str));
                    freeReplyObject(reply);

                    // Definisci un array contenente i valori da inviare
                    int values[] = {state, intensity, color};
                    const int NUM_MESSAGES = sizeof(values) / sizeof(values[0]);

                    for (int i = 0; i < NUM_MESSAGES; ++i)
                    {
                        // Invia il messaggio a Redis
                        reply = (redisReply *)redisCommand(context, "PUBLISH lightChannel %d", values[i]);
                        if (reply != NULL)
                        {
                            freeReplyObject(reply);
                        }
                        else
                        {
                            std::cerr << "Errore nell'invio del messaggio " << i + 1 << " a Redis." << std::endl;
                        }

                        // Attendi un breve periodo di tempo tra l'invio dei messaggi
                        usleep(1000000); // Attendi 1 secondo (1000000 microsecondi)
                    }
                    freeReplyObject(reply);

                    // Ricevi i messaggi per un periodo di tempo
                    const int TIMEOUT_SECONDS = 1;
                    time_t startTime = time(NULL);
                    while (difftime(time(NULL), startTime) < TIMEOUT_SECONDS)
                    {
                        reply = (redisReply *)redisCommand(context, "GET lightChannel");
                        if (reply != NULL && reply->type == REDIS_REPLY_ARRAY && strcmp(reply->element[0]->str, "message") == 0)
                        {
                            std::string message = reply->element[2]->str;
                            std::cout << "Messaggio ricevuto da Redis: " << message << std::endl;
                            freeReplyObject(reply);
                        }
                    }
                    break;
                }
                case Sensor: {
                    reply = (redisReply *)redisCommand(context, "GET comando");
                    sensor_type state = static_cast<sensor_type>(atoi(reply->str));
                    freeReplyObject(reply);

                    reply = (redisReply *)redisCommand(context, "PUBLISH sensorChannel %s", state);
                    freeReplyObject(reply);

                    // Ricevi i messaggi per un periodo di tempo
                    const int TIMEOUT_SECONDS = 1;
                    time_t startTime = time(NULL);
                    while (difftime(time(NULL), startTime) < TIMEOUT_SECONDS)
                    {
                        reply = (redisReply *)redisCommand(context, "GET sensorChannel");
                        if (reply != NULL && reply->type == REDIS_REPLY_ARRAY && strcmp(reply->element[0]->str, "message") == 0)
                        {
                            std::string message = reply->element[2]->str;
                            std::cout << "Messaggio ricevuto da Redis: " << message << std::endl;
                            freeReplyObject(reply);
                        }
                    }
                    break;
                }
                case SensorGarden: {
                    reply = (redisReply *)redisCommand(context, "GET comando");
                    camera_type state = static_cast<camera_type>(atoi(reply->str));
                    freeReplyObject(reply);

                    reply = (redisReply *)redisCommand(context, "PUBLISH cameraChannel %s", state);
                    freeReplyObject(reply);

                    // Ricevi i messaggi per un periodo di tempo
                    const int TIMEOUT_SECONDS = 1;
                    time_t startTime = time(NULL);
                    while (difftime(time(NULL), startTime) < TIMEOUT_SECONDS)
                    {
                        reply = (redisReply *)redisCommand(context, "GET cameraChannel");
                        if (reply != NULL && reply->type == REDIS_REPLY_ARRAY && strcmp(reply->element[0]->str, "message") == 0)
                        {
                            std::string message = reply->element[2]->str;
                            std::cout << "Messaggio ricevuto da Redis: " << message << std::endl;
                            freeReplyObject(reply);
                        }
                    }
                    break;
                }
                default: {
                    break;
                }
                }
            }
            else if (received_message == "Not ok")
            {
                // Fare qualcosa se il comando non è andato a buon fine
            }
        }
    }

    redisFree(context);
    return 0;
}
