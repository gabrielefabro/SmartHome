#include "conditioner.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>



int test() {
    
    char state[20];

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err) {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

     // Leggi ID e STATE da Redis
    redisReply *reply = (redisReply *)redisCommand(context, "GET conditioner_id");
    int conditionerId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET conditioner_state");
    conditioner_type conditionerState = static_cast<conditioner_type>(atoi(reply->str));
    freeReplyObject(reply);

    int2state(state, conditionerState);

    if(strcmp(state, "change_temperature") == 0)
    {
        // Invia il nuovo colore a Redis
        int newTemperature = changeRandomTemperature();
        reply = (redisReply *)redisCommand(context, "SET new_temperaturer %d", newTemperature);
        freeReplyObject(reply);
    }
    
    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}

