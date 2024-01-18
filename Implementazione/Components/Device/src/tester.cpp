#include "device.h"
#include "../../../main/main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>

int testDevice()
{
    char state[20];

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Leggi ID e STATE e NOME da Redis
    redisReply *reply = (redisReply *)redisCommand(context, "GET device_id");
    int deviceId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET device_state");
    device_type deviceState = static_cast<device_type>(atoi(reply->str));
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET nome_device");
    nome_type devicename = static_cast<nome_type>(atoi(reply->str));
    freeReplyObject(reply);

    int2stateDevice(state, deviceState);

    if (strcmp(state, "programmed") == 0)
    {
        int intervalloPrimo = changeInt();
        int intervalloSecondo = changeInt();
        reply = (redisReply *)redisCommand(context, "SET new_int1 %d", intervalloPrimo);
        reply = (redisReply *)redisCommand(context, "SET new_int2 %d", intervalloSecondo);
        freeReplyObject(reply);
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}