#include "../../../main/src/main.h"
#include <iostream>

int initTestLight(Light light)
{
    int lightId;
    light_type lightState;

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    lightId = light.getId();
    lightState = light.getState();

    // Invia ID e STATE a Redis
    redisReply *reply = (redisReply *)redisCommand(context, "SET light_id %d", lightId);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET light_state %d", lightState);
    freeReplyObject(reply);

    testLight();

    char state[20];
    int2stateLight(state, lightState);

    if (strcmp(state, "change color") == 0 || strcmp(state, "change_intensity") == 0)
    {
        reply = (redisReply *)redisCommand(context, "GET tester_response");
        if (strcmp(state, "change_color") == 0)
        {
            char colorStr[20];
            sscanf(reply->str, "%s", colorStr);
            light_color newColor = stringToLightColor(colorStr);
            light.setColor(newColor);
        }
        else if (strcmp(state, "change_intensity") == 0)
        {
            int newIntensity = reply->integer;
            light.setIntensity(newIntensity);
        }

        freeReplyObject(reply);
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}