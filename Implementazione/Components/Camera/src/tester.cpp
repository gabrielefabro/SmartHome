#include "camera.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>

int test()
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
    redisReply *reply = (redisReply *)redisCommand(context, "GET camera_id");
    int cameraId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET camera_state");
    camera_type cameraState = static_cast<camera_type>(atoi(reply->str));
    freeReplyObject(reply);

    int2state(state, cameraState);

    if (strcmp(state, "WAITING") == 0)
    {

    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}
