#include "sensor.h"
#include "../../../main/src/main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>

// Funzione di test per il sensore
int testSensor()
{
    char state[20];

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Legge l'ID e lo stato del sensore da Redis
    redisReply *reply = (redisReply *)redisCommand(context, "GET sensor_id");
    int sensorId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET sensor_state");
    sensor_type sensorState = static_cast<sensor_type>(atoi(reply->str));
    freeReplyObject(reply);

    int2stateSensor(state, sensorState);

    if (strcmp(state, "CHECKING") == 0)
    {
        // Genera un numero casuale, se è pari allora fai che sia stato rilevato movimento, altrimenti no
        int n = std::rand();
        if (n % 2 == 0)
        {
            n = 1;
            // Invia al Redis se è presente movimento
            reply = (redisReply *)redisCommand(context, "SET movment %d", n);
            freeReplyObject(reply);
        }
        else
        {
            n = 0;
            // Invia al Redis se non è presente movimento
            reply = (redisReply *)redisCommand(context, "SET movment %d", n);
            freeReplyObject(reply);
        }
    }

    // Chiude la connessione a Redis
    redisFree(context);

    return 0;
}
