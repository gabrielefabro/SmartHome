#include "sensorGarden.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>

int main()
{

    char state[20];

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Leggi ID e STATE da Redis
    redisReply *reply = (redisReply *)redisCommand(context, "GET sensorGarden_id");
    int lightId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET sensorGarden_state");
    sensorGarden_type sensorGardenState = static_cast<sensorGarden_type>(atoi(reply->str));
    freeReplyObject(reply);

    int2state(state, sensorGardenState);

    if (strcmp(state, "change_light") == 0)
    {
        std::srand(std::time(0));
        int humidity = std::rand() % 101;
        std::srand(std::time(0));
        int temperature = std::rand() % 46;

        redisReply *reply = (redisReply *)redisCommand(context, "MSET humidity %d temperature %d", humidity, temperature);
    }
    else if (strcmp(state, "set_sprinklers") == 0)
    {
        std::srand(std::time(0));
        int humidity = std::rand() % 101;

        reply = (redisReply *)redisCommand(context, "SET humidity %d", humidity);
        freeReplyObject(reply);
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}
