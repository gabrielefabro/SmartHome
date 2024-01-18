#include "conditioner.h"
#include "../../../main/main.h"
#include "../../../main/global.h"

int initTestConditioner(Conditioner conditioner)
{
    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Invia ID e STATE a Redis
    redisReply *reply = (redisReply *)redisCommand(context, "SET conditioner id %d", conditioner.getId());
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET conditioner_state %d", conditioner.getState());
    freeReplyObject(reply);

    testConditioner();

    // Aspetta una risposta dal tester
    reply = (redisReply *)redisCommand(context, "GET new_temperaturer");
    if (reply != nullptr && reply->str != nullptr)
    {
        freeReplyObject(reply);
    }

    char state[20];
    conditioner_type conditionerState = static_cast<conditioner_type>(atoi(reply->str));
    int2stateConditioner(state, conditionerState);

    if (strcmp(state, "change_temperature") == 0)
    {
        int newTemperature;
        newTemperature = reply->integer;
        conditioner.modifyTemperature(newTemperature);
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}
