#include <iostream>
#include <hiredis/hiredis.h>
#include "software.h"
#include <chrono>
#include <cstdlib>

int main()
{
    std::chrono::_V2::steady_clock::time_point tempo_iniziale;
    // Connessione al database
    Con2DB db1("localhost", "5432", "smarthome", "12345", "logdb_smarthome");
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
        std::cout << "IN ATTESA DI UN COMANDO" << std::endl;
        if (redisGetReply(context, (void **)&reply) != REDIS_OK)
        {
            std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
            exit(1);
        }

        if (reply->type == REDIS_REPLY_ARRAY && strcmp(reply->element[0]->str, "message") == 0)
        {

            components comp = static_cast<components>(atoi(reply->element[2]->str));
            std::cout << "La component di interesse è : " << componentToString(comp) << std::endl;
            freeReplyObject(reply);
            switch (comp)
            {
            case Camera:
            {
                camera_type cameraState;
                char com[20];

                if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                {
                    std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                    exit(1);
                }

                if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                {
                    cameraState = static_cast<camera_type>(atoi(reply->element[2]->str));
                    freeReplyObject(reply);
                    int2stateCamera(com, cameraState);
                    log2db(db1, componentToString(comp), com);
                    redisContext *context2 = redisConnect("127.0.0.1", 6379);
                    redisReply *secondReply = (redisReply *)redisCommand(context2, "PUBLISH cameraChannel %d", cameraState);
                    tempo_iniziale = std::chrono::steady_clock::now();
                    freeReplyObject(secondReply);
                    redisFree(context2);
                }
                break;
            }
            case Conditioner:
            {
                conditioner_type conditionerState;
                int numMessage = 0;
                int temp;
                char com[20];

                while (numMessage < 2)
                {
                    if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                    {
                        std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                        exit(1);
                    }

                    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                    {
                        if (numMessage == 0)
                        {
                            conditionerState = static_cast<conditioner_type>(atoi(reply->element[2]->str));
                            freeReplyObject(reply);
                        }
                        if (numMessage == 1)
                        {
                            temp = (atoi(reply->element[2]->str));
                            freeReplyObject(reply);
                        }
                        numMessage++;
                    }
                    int2stateConditioner(com, conditionerState);
                    log2db(db1, componentToString(comp), com);

                    // Definisci un array contenente i valori da inviare
                }
                int values[] = {conditionerState, temp};
                const int NUM_MESSAGES = sizeof(values) / sizeof(values[0]);
                redisContext *context2 = redisConnect("127.0.0.1", 6379);
                redisReply *secondReply;
                for (int i = 0; i < NUM_MESSAGES; ++i)
                {
                    // Invia il messaggio a Redis

                    secondReply = (redisReply *)redisCommand(context2, "PUBLISH conditionerChannel %d", values[i]);

                    // Attendi un breve periodo di tempo tra l'invio dei messaggi
                    freeReplyObject(secondReply);
                    redisFree(context2);
                    sleep(1); // Attendi 1 secondo (1000000 microsecondi)
                }
                break;
            }
            case Device:
            {
                device_type deviceState;
                nome_type nomeDispositivo;
                int numMessage = 0;
                int nomeDev, inizio, fine;
                char com[20];

                while (numMessage < 4)
                {
                    if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                    {
                        std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                        exit(1);
                    }

                    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                    {
                        if (numMessage == 0)
                        {
                            deviceState = static_cast<device_type>(atoi(reply->element[2]->str));
                            freeReplyObject(reply);
                        }
                        if (numMessage == 1)
                        {
                            nomeDispositivo = static_cast<nome_type>(atoi(reply->element[2]->str));
                            freeReplyObject(reply);
                        }
                        if (numMessage == 2)
                        {
                            inizio = (atoi(reply->element[2]->str));
                            freeReplyObject(reply);
                        }
                        if (numMessage == 3)
                        {
                            fine = (atoi(reply->element[2]->str));
                            freeReplyObject(reply);
                        }
                    }
                    numMessage++;
                }
                int2stateDevice(com, deviceState);
                log2db(db1, componentToString(comp), com);

                // Definisci un array contenente i valori da inviare
                int values[] = {deviceState, nomeDispositivo, inizio, fine};
                const int NUM_MESSAGES = sizeof(values) / sizeof(values[0]);
                redisContext *context2 = redisConnect("127.0.0.1", 6379);
                redisReply *secondReply;

                for (int i = 0; i < NUM_MESSAGES; ++i)
                {

                    // Invia il messaggio a Redis
                    secondReply = (redisReply *)redisCommand(context2, "PUBLISH deviceChannel %d", values[i]);
                    auto tempo_iniziale = std::chrono::steady_clock::now();
                    freeReplyObject(secondReply);

                    // Attendi un breve periodo di tempo tra l'invio dei messaggi
                    sleep(1); // Attendi 1 secondo (1000000 microsecondi)
                }
                redisFree(context2);
                break;
            }
            case Light:
            {
                light_type lightState;
                light_color coloreLuce;
                int numMessage = 0;
                int intensity;
                char com[20];

                while (numMessage < 3)
                {
                    if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                    {
                        std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                        exit(1);
                    }

                    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                    {
                        if (numMessage == 0)
                        {
                            lightState = static_cast<light_type>(atoi(reply->element[2]->str));
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
                int2stateLight(com, lightState);
                log2db(db1, componentToString(comp), com);
                // Definisci un array contenente i valori da inviare
                int values[] = {lightState, coloreLuce, intensity};
                const int NUM_MESSAGES = sizeof(values) / sizeof(values[0]);
                redisContext *context2 = redisConnect("127.0.0.1", 6379);
                redisReply *secondReply;

                for (int i = 0; i < NUM_MESSAGES; ++i)
                {
                    // Invia il messaggio a Redis
                    secondReply = (redisReply *)redisCommand(context2, "PUBLISH lightChannel %d", values[i]);
                    auto tempo_iniziale = std::chrono::steady_clock::now();
                    freeReplyObject(secondReply);

                    // Attendi un breve periodo di tempo tra l'invio dei messaggi
                    sleep(1); // Attendi 1 secondo (1000000 microsecondi)
                }
                redisFree(context2);
                break;
            }
            case Sensor:
            {
                sensor_type sensorState;
                int comando;
                char com[20];
                

                

                if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                {
                    std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                    exit(1);
                }

                if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                {

                    sensorState = static_cast<sensor_type>(atoi(reply->element[2]->str));
                    freeReplyObject(reply);

                    redisContext *context2 = redisConnect("127.0.0.1", 6379);
                    redisReply *secondReply = (redisReply *)redisCommand(context2, "PUBLISH sensorChannel %d", sensorState);
                    auto tempo_iniziale = std::chrono::steady_clock::now();

                    freeReplyObject(secondReply);
                    redisFree(context2);
                }
                int2stateSensor(com, sensorState);
                const char *component = componentToString(comp);
                log2db(db1, component, com);
                break;
            }
            case SensorGarden:
            {
                sensorGarden_type sensorGardenState;
                int comando;
                char com[20];

                if (redisGetReply(context, (void **)&reply) != REDIS_OK)
                {
                    std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                    exit(1);
                }

                if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
                {

                    sensorGardenState = static_cast<sensorGarden_type>(atoi(reply->element[2]->str));
                    freeReplyObject(reply);

                    redisContext *context2 = redisConnect("127.0.0.1", 6379);
                    redisReply *secondReply = (redisReply *)redisCommand(context2, "PUBLISH sensorGardenChannel %d", sensorGardenState);
                    auto tempo_iniziale = std::chrono::steady_clock::now();

                    freeReplyObject(secondReply);
                    redisFree(context2);

                    break;
                }
                int2stateSensorGarden(com, sensorGardenState);
                log2db(db1, componentToString(comp), com);
            }
            default:
            {
                break;
            }
            }
            // redisFree(context);
        }

        redisContext *context3 = redisConnect("127.0.0.1", 6379);
        if (context3 == NULL || context3->err)
        {
            if (context3)
            {
                std::cerr << "Errore nella connessione a Redis: " << context3->errstr << std::endl;
                redisFree(context3);
            }
            else
            {
                std::cerr << "Impossibile connettersi a Redis." << std::endl;
            }
            exit(1);
        }

        // Sottoscrizione al canale
        redisReply *altrareply = (redisReply *)redisCommand(context3, "SUBSCRIBE rispostaChannel");
        freeReplyObject(altrareply);
        while (true)
        {
            std::cout << "IN ATTESA RISPOSTA" << std::endl;
            if (redisGetReply(context3, (void **)&altrareply) != REDIS_OK)
            {
                std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                exit(1);
            }

            if (altrareply->type == REDIS_REPLY_ARRAY && altrareply->elements == 3 && strcmp(altrareply->element[0]->str, "message") == 0)
            {
                // const char *received_message = altrareply->element[2]->str;
                // std::cout << "Receiver: Messaggio ricevuto da Redis: " << received_message << std::endl;
                std::cout << "Messaggio ricevuto sul canale " << altrareply->element[1]->str << ": " << altrareply->element[2]->str << std::endl;
                auto tempo_corrente = std::chrono::steady_clock::now();
                auto tempo_trascorso = std::chrono::duration_cast<std::chrono::milliseconds>(tempo_corrente - tempo_iniziale).count();

                if (tempo_trascorso > 5000)
                {
                    std::cout << "Sistema lento " << std::endl;
                }
                freeReplyObject(altrareply);

                sleep(5);
            }
            break;
        }
        redisFree(context3);
    }
    redisFree(context);
    return 0;
}
