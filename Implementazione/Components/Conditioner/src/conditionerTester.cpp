#include "conditioner.h"
#include "../../../main/src/main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>

int testConditioner()
{

    char state[20];
    bool corretto;
    int newTemperature;

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    redisReply *reply = (redisReply *)redisCommand(context, "GET conditioner_id");
    int conditionerId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET conditioner_state");
    conditioner_type conditionerState = static_cast<conditioner_type>(atoi(reply->str));
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET conditioner_temperature");
    int conditionerTemperature = atoi(reply->str);
    freeReplyObject(reply);

    int2stateConditioner(state, conditionerState);

    if (strcmp(state, "change_temperature") == 0)
    {
        corretto = true;
        while (corretto) 
        {
        newTemperature = changeRandomTemperature();
        if ((newTemperature < conditionerTemperature + 8) && (newTemperature > conditionerTemperature - 8))
                {
                    corretto = false;
                }
        }
        reply = (redisReply *)redisCommand(context, "SET new_temperature %d", newTemperature);
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}
