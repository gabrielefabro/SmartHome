#include "light.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>
#include "randomColor.cpp"
#include "randomIntensity.cpp"


int main() {
    
    char state[20];

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err) {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

     // Leggi ID e STATE da Redis
    redisReply *reply = (redisReply *)redisCommand(context, "GET light_id");
    int lightId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET light_state");
    light_type lightState = static_cast<light_type>(atoi(reply->str));
    freeReplyObject(reply);

    int2state(state,lightState);

    if(strcmp(state, "change_color") == 0)
    {
        // Invia il nuovo colore a Redis
        light_color newColor = getRandomColor();
        reply = (redisReply *)redisCommand(context, "SET new_color %s", newColor);
        freeReplyObject(reply);
    }
    else if (strcmp(state, "change_intensity") == 0)
    {
        // Invia la nuova intensita' a Redis
        int newIntensity = changeIntensity();
        reply = (redisReply *)redisCommand(context, "SET new_intensity %d", newIntensity);
        freeReplyObject(reply);
    }
    
    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}

