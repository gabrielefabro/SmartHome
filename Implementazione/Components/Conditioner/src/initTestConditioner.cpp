#include "conditioner.h"
#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

int initTestConditioner(Conditioner conditioner)
{
    char state[20];
    int conditionerId;
    conditioner_type conditionerState;
    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }
    conditionerId = conditioner.getId();
    conditionerState = conditioner.getState();

    // Invia ID e STATE a Redis
    redisReply *reply = (redisReply *)redisCommand(context, "SET conditioner_id %d", conditionerId);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET conditioner_state %d", conditionerState);
    freeReplyObject(reply);

    testConditioner();

    // Aspetta una risposta dal tester
    reply = (redisReply *)redisCommand(context, "GET new_temperature");
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
