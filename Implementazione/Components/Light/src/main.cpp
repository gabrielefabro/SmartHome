#include "light.h"
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
    Light light = initLight();

    while (t < HORIZON)
    {
        // Invia ID e STATE a Redis
        redisReply *reply = (redisReply *)redisCommand(context, "SET light_id %d", light.getId());
        freeReplyObject(reply);

        reply = (redisReply *)redisCommand(context, "SET light_state %d", light.getState());
        freeReplyObject(reply);

        // Aspetta una risposta dal tester
        reply = (redisReply *)redisCommand(context, "GET tester_response");
        if (reply != nullptr && reply->str != nullptr)
        {
            freeReplyObject(reply);
        }

        char state[20];
        light_type lightState = static_cast<light_type>(atoi(reply->str));
        int2state(state, lightState);

        if (strcmp(state, "change_color"))
        {
            char colorStr[20];
            sscanf(reply->str, "%s", colorStr);
            light_color newColor = stringToLightColor(colorStr);
            light.setColor(newColor);
        }
        else if (strcmp(state, "change_intensity") == 0)
        {
            int newIntensity;
            sscanf(reply->str, "%d", &newIntensity); // converte reply in int
            light.setIntensity(newIntensity);
        }

        // Chiudi la connessione a Redis
        redisFree(context);

        light.next();

        t++;

        /* sleep   */
        micro_sleep(500);
    }

    return 0;
}
