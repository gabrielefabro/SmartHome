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
    freeReplyObject(reply);

    // Ascolto dei messaggi
    while (true)
    {

        std::cout << "STO ASPETTANDO UN MESSAGGIO" << std::endl;
        if (redisGetReply(context, (void **)&reply) != REDIS_OK)
        {
            std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
            exit(1);
        }

        if (reply->type == REDIS_REPLY_ARRAY && strcmp(reply->element[0]->str, "message") == 0)
        {
            std::string message = reply->element[2]->str;
            std::cout << "La component di interesse è : " << message << std::endl;

            components comp = static_cast<components>(atoi(reply->element[2]->str));
            freeReplyObject(reply);

            switch (comp)
            {
                case Camera:
                {
                    int comando = 0;
                    camera_type state = static_cast<camera_type>(comando);

                    if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                    {
                        std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                        exit(1);
                    }

                    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                    {
                        std::string messageA = reply->element[2]->str;
                        std::cout << "Messaggio ricevuto da Redis(COMANDO): " << messageA << std::endl;
                        state = static_cast<camera_type>(atoi(reply->element[2]->str));
                        freeReplyObject(reply);

                        redisContext *context2 = redisConnect("127.0.0.1", 6379);
                        redisReply *secondReply = (redisReply *)redisCommand(context2, "PUBLISH cameraChannel %d", state);
                        std::cout << "Ho pubblicato il messaggio: " << std::endl;

                        if (secondReply != NULL)
                        {
                            freeReplyObject(secondReply);
                            std::cout << "pubblica su camera channel" << std::endl;
                        }
                        else
                        {
                            std::cerr << "Errore nell'invio del messaggio a Redis." << std::endl;
                        }

                        /*
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
                        */
                        
                    }
                    break;
                }
                case Conditioner:
                {
                    std::cout << "sono in conditioner" << std::endl;
                    int numMessage = 0;
                    int comando, temp;
                    conditioner_type state = static_cast<conditioner_type>(comando);
                    while (numMessage < 2)
                    {
                        if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                        {
                            std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                            exit(1);
                        }

                        if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                        {
                            std::string messageA = reply->element[2]->str;
                            std::cout << "Messaggio ricevuto da Redis(COMANDO): " << messageA << std::endl;
                            if (numMessage == 0)
                            {
                                state = static_cast<conditioner_type>(atoi(reply->element[2]->str));
                                std::cout << "prendo stato" << std::endl;
                                freeReplyObject(reply);
                            }
                            if (numMessage == 1)
                            {
                                temp = (atoi(reply->element[2]->str));
                                std::cout << "prendo temperatura" << std::endl;
                                freeReplyObject(reply);
                            }
                            numMessage++;
                        }

                        // Definisci un array contenente i valori da inviare
                    }
                    std::cout << "stato: " << state << " temperatura: " << temp << std::endl;
                    int values[] = {state, temp};
                    const int NUM_MESSAGES = sizeof(values) / sizeof(values[0]);
                    redisContext *context2 = redisConnect("127.0.0.1", 6379);
                    redisReply *secondReply;
                    for (int i = 0; i < NUM_MESSAGES; ++i)
                    {
                        // Invia il messaggio a Redis
                        std::cout << "mando il valore: " << values[i] << std::endl;

                        secondReply = (redisReply *)redisCommand(context2, "PUBLISH conditionerChannel %d", values[i]);
                        if (reply != NULL)
                        {
                            freeReplyObject(secondReply);
                        }
                        else
                        {
                            std::cerr << "Errore nell'invio del messaggio " << i + 1 << " a Redis." << std::endl;
                        }

                        // Attendi un breve periodo di tempo tra l'invio dei messaggi
                        sleep(1); // Attendi 1 secondo (1000000 microsecondi)

                        /* Ricevi i messaggi per un periodo di tempo
                        const int TIMEOUT_SECONDS = 10;
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
                        */
                    }
                    break;
                }
                case Device:
                {
                    int numMessage = 0;
                    int comando, nomeDev, inizio, fine;
                    device_type state = static_cast<device_type>(comando);
                    nome_type nomeDispositivo = static_cast<nome_type>(nomeDev);
                    while (numMessage < 4)
                    {
                        if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                        {
                            std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                            exit(1);
                        }

                        if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                        {
                            std::cout << "Messaggio ricevuto da Redis array !!" << std::endl;
                            std::string messageA = reply->element[2]->str;
                            if (numMessage == 0)
                            {
                                std::cout << "Messaggio ricevuto da Redis(COMANDO): " << messageA << std::endl;
                                state = static_cast<device_type>(atoi(reply->element[2]->str));
                                freeReplyObject(reply);
                            }
                            if (numMessage == 1)
                            {
                                std::cout << "Messaggio ricevuto da Redis(Elettrodomestico): " << messageA << std::endl;
                                nomeDispositivo = static_cast<nome_type>(atoi(reply->element[2]->str));
                                freeReplyObject(reply);
                            }
                            if (numMessage == 2)
                            {
                                std::cout << "Messaggio ricevuto da Redis(inizio): " << messageA << std::endl;
                                inizio = (atoi(reply->element[2]->str));
                                freeReplyObject(reply);
                            }
                            if (numMessage == 3)
                            {
                                std::cout << "Messaggio ricevuto da Redis(fine): " << messageA << std::endl;
                                fine = (atoi(reply->element[2]->str));
                                freeReplyObject(reply);
                            }
                        }
                        numMessage++;
                    }

                    // Definisci un array contenente i valori da inviare
                    int values[] = {state, nomeDispositivo, inizio, fine};
                    const int NUM_MESSAGES = sizeof(values) / sizeof(values[0]);
                    redisContext *context2 = redisConnect("127.0.0.1", 6379);
                    redisReply *secondReply;

                    for (int i = 0; i < NUM_MESSAGES; ++i)
                    {

                        std::cout << values[i] << std::endl;
                        // Invia il messaggio a Redis
                        secondReply = (redisReply *)redisCommand(context2, "PUBLISH deviceChannel %d", values[i]);
                        if (reply != NULL)
                        {
                            freeReplyObject(reply);
                            std::cout << "pubblicato messaggio" << std::endl;
                        }
                        else
                        {
                            std::cerr << "Errore nell'invio del messaggio " << i + 1 << " a Redis." << std::endl;
                        }

                        // Attendi un breve periodo di tempo tra l'invio dei messaggi
                        sleep(1); // Attendi 1 secondo (1000000 microsecondi)
                    }

                    /* Ricevi i messaggi per un periodo di tempo
                    const int TIMEOUT_SECONDS = 10;
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
                    */
                    break;
                }
                case Light:
                {
                    int numMessage = 0;
                    int comando, color, intensity;
                    light_type state = static_cast<light_type>(comando);
                    light_color coloreLuce = static_cast<light_color>(color);
                    while (numMessage < 3)
                    {
                        if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                        {
                            std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                            exit(1);
                        }

                        if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                        {
                            std::cout << "Messaggio ricevuto da Redis!!" << std::endl;
                            std::string messageA = reply->element[2]->str;
                            std::cout << "Messaggio ricevuto da Redis: " << messageA << std::endl;
                            if (numMessage == 0)
                            {
                                state = static_cast<light_type>(atoi(reply->element[2]->str));
                                freeReplyObject(reply);
                            }
                            if (numMessage == 1)
                            {
                                coloreLuce = static_cast<light_color>(atoi(reply->element[2]->str));
                                freeReplyObject(reply);
                            }
                            if (numMessage == 2)
                            {
                                intensity = (atoi(reply->element[2]->str));
                                freeReplyObject(reply);
                            }
                        }
                        numMessage++;
                    }
                    // Definisci un array contenente i valori da inviare
                    int values[] = {state, coloreLuce, intensity};
                    const int NUM_MESSAGES = sizeof(values) / sizeof(values[0]);
                    redisContext *context2 = redisConnect("127.0.0.1", 6379);
                    redisReply *secondReply;

                    for (int i = 0; i < NUM_MESSAGES; ++i)
                    {
                        std::cout <<"invio: " << values[i] << std::endl;
                        // Invia il messaggio a Redis
                        secondReply = (redisReply *)redisCommand(context2, "PUBLISH lightChannel %d", values[i]);
                        if (reply != NULL)
                        {
                            freeReplyObject(secondReply);
                        }
                        else
                        {
                            std::cerr << "Errore nell'invio del messaggio " << i + 1 << " a Redis." << std::endl;
                        }

                        // Attendi un breve periodo di tempo tra l'invio dei messaggi
                        sleep(1); // Attendi 1 secondo (1000000 microsecondi)
                    }

                    /* Ricevi i messaggi per un periodo di tempo
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
                    */
                    break;
                }
                case Sensor:
                {
                    int comando;
                    sensor_type state = static_cast<sensor_type>(comando);

                    if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                    {
                        std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                        exit(1);
                    }

                    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                    {
                        std::cout << "Messaggio ricevuto da Redis!!" << std::endl;
                        std::string messageA = reply->element[2]->str;
                        std::cout << "Messaggio ricevuto da Redis: " << messageA << std::endl;

                        state = static_cast<sensor_type>(atoi(reply->element[2]->str));
                        freeReplyObject(reply);

                        redisContext *context2 = redisConnect("127.0.0.1", 6379);
                        redisReply *secondReply = (redisReply *)redisCommand(context2, "PUBLISH sensorChannel %d", state);
                        std::cout << "Ho pubblicato il messaggio: " << std::endl;

                        if (secondReply != NULL)
                        {
                            freeReplyObject(secondReply);
                            std::cout << "pubblica su sensor channel" << std::endl;
                        }
                        else
                        {
                            std::cerr << "Errore nell'invio del messaggio a Redis." << std::endl;
                        }

                        /*
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
                        */
                        break;
                    }
                }
                case SensorGarden:
                {
                    int comando;
                    sensorGarden_type state = static_cast<sensorGarden_type>(comando);

                    if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                    {
                        std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                        exit(1);
                    }

                    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                    {
                        std::cout << "Messaggio ricevuto da Redis!!" << std::endl;
                        std::string messageA = reply->element[2]->str;
                        std::cout << "Messaggio ricevuto da Redis: " << messageA << std::endl;

                        state = static_cast<sensorGarden_type>(atoi(reply->element[2]->str));
                        freeReplyObject(reply);

                        redisContext *context2 = redisConnect("127.0.0.1", 6379);
                        redisReply *secondReply = (redisReply *)redisCommand(context2, "PUBLISH sensorGardenChannel %d", state);
                        std::cout << "Ho pubblicato il messaggio: " << std::endl;

                        if (secondReply != NULL)
                        {
                            freeReplyObject(secondReply);
                            std::cout << "pubblica su sensorGarden channel" << std::endl;
                        }
                        else
                        {
                            std::cerr << "Errore nell'invio del messaggio a Redis." << std::endl;
                        }

                        /*
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
                        */
                        break;
                    }
                }
                default:
                {
                    break;
                }
            }
            //redisFree(context);
            
        }
        sleep(35);
    }
    return 0; //spostato return fuori dal while perchè interrompeva l'esecuzione adesso però entra in errore ricezione perchè troppo veloce ?
}
