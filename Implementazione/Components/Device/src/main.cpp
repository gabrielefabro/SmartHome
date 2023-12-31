#include "device.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include "main.h"

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

    // Inizializza un oggetto Device
    Device device = initDevice();

    while (t < HORIZON)
    {
        // Invia ID e STATE e NOME a Redis
        redisReply *reply = (redisReply *)redisCommand(context, "SET device_id %d", device.getId());
        freeReplyObject(reply);

        reply = (redisReply *)redisCommand(context, "SET device_state %d", device.getState());
        freeReplyObject(reply);

        reply = (redisReply *)redisCommand(context, "SET nome_type %d", device.getNome());
        freeReplyObject(reply);

        // Aspetta una risposta dal tester
        reply = (redisReply *)redisCommand(context, "GET new_int1");
        if (reply != nullptr && reply->str != nullptr)
        {
            freeReplyObject(reply);
        }

        int interval1 = reply->integer;

        reply = (redisReply *)redisCommand(context, "GET new_int2");
        if (reply != nullptr && reply->str != nullptr)
        {
            freeReplyObject(reply);
        }

        int interval2 = reply->integer;

        char state[20];
        device_type deviceState = static_cast<device_type>(atoi(reply->str));
        int2state(state, deviceState);

        if (strcmp(state, "programmed") == 0)
        {
           device.programmed_device(interval1,interval2);
        }
    
        // Chiudi la connessione a Redis
        redisFree(context);

        device.next();

        t++;

        /* sleep   */
        micro_sleep(500);
    }

    return 0;
}