#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

int initTestDevice(Device device)
{
    int deviceId;
    device_type deviceState;

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    deviceId = device.getId();
    deviceState = device.getState();

    // Invia ID e STATE e NOME a Redis
    redisReply *reply = (redisReply *)redisCommand(context, "SET device_id %d", deviceId);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET device_state %d", deviceState);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET nome_device %d", device.getNome());
    freeReplyObject(reply);

    testDevice();

    char state[20];
    int2stateDevice(state, deviceState);

    if (strcmp(state, "programmed") == 0)
    {
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
        device.programmed_device(interval1, interval2);
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}