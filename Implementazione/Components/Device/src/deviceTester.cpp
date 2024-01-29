#include "device.h"
#include "../../../main/src/main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>

// Funzione di test per il dispositivo
int testDevice()
{
    char state[20];

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        // Stampa un messaggio di errore se la connessione a Redis fallisce.
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Leggi l'ID, lo stato e il nome del dispositivo da Redis.
    redisReply *reply = (redisReply *)redisCommand(context, "GET device_id");
    int deviceId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET device_state");
    device_type deviceState = static_cast<device_type>(atoi(reply->str));
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET nome_device");
    nome_type devicename = static_cast<nome_type>(atoi(reply->str));
    freeReplyObject(reply);

    // Converti lo stato del dispositivo in una rappresentazione di stringa.
    int2stateDevice(state, deviceState);

    // Se lo stato del dispositivo è "programmed", genera due intervalli di tempo casuali e li salva in Redis.
    if (strcmp(state, "programmed") == 0)
    {
        // Genera due intervalli di tempo casuali.
        int intervalloPrimo = changeInt();
        int intervalloSecondo = changeInt();

        // Salva i due intervalli di tempo casuali in Redis.
        reply = (redisReply *)redisCommand(context, "SET new_int1 %d", intervalloPrimo);
        freeReplyObject(reply);

        reply = (redisReply *)redisCommand(context, "SET new_int2 %d", intervalloSecondo);
        freeReplyObject(reply);
    }

    // Chiudi la connessione a Redis.
    redisFree(context);

    return 0;
}
