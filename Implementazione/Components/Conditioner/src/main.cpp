#include "conditioner.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>


int main()
{

    int t = 0;

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Inizializza un oggetto Light
    Conditioner conditioner = initConditioner();

    while (t < HORIZON)
    {
        // Invia ID e STATE a Redis
        redisReply *reply = (redisReply *)redisCommand(context, "SET conditioner id %d", conditioner.getId());
        freeReplyObject(reply);

        reply = (redisReply *)redisCommand(context, "SET conditioner_state %d", conditioner.getState());
        freeReplyObject(reply);

        // Aspetta una risposta dal tester
        reply = (redisReply *)redisCommand(context, "GET tester_response");
        if (reply != nullptr && reply->str != nullptr)
        {
            freeReplyObject(reply);
        }

        char state[20];
        conditioner_type conditionerState = static_cast<conditioner_type>(atoi(reply->str));
        int2state(state, conditionerState);

        if (strcmp(state, "change_temperature"))
        {
            int newTemperature;
            newTemperature = reply->integer;
            conditioner.modifyTemperature(newTemperature);
        }
        

        // Chiudi la connessione a Redis
        redisFree(context);

        conditioner.next();

        t++;

        /* sleep   */
        micro_sleep(500);
    }

    return 0;
}
