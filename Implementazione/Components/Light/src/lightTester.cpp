#include "light.h"
#include "../../../main/src/main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>

int testLight()
{

    char state[20];
    int lightId;
    light_type lightState;

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Leggi ID e STATE da Redis
    redisReply *reply = (redisReply *)redisCommand(context, "GET light_id");
    lightId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET light_state");
    lightState = static_cast<light_type>(atoi(reply->str));
    freeReplyObject(reply);

    int2stateLight(state, lightState);

    if (strcmp(state, "change_color") == 0)
    {
        // Invia il nuovo colore a Redis
        light_color newColor = getRandomColor();
        reply = (redisReply *)redisCommand(context, "SET tester_response %s", colorToString(newColor));
        freeReplyObject(reply);
    }
    else if (strcmp(state, "change_intensity") == 0)
    {
        // Invia la nuova intensita' a Redis
        int newIntensity = changeIntensity();
        reply = (redisReply *)redisCommand(context, "SET tester_response %d", newIntensity);
        freeReplyObject(reply);
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}
