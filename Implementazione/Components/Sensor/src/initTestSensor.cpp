#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

int initTestSensor(Sensor sensor)
{

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Invia ID e STATE a Redis
    redisReply *reply = (redisReply *)redisCommand(context, "SET sensor_id %d", sensor.getId());
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET sensor_state %d", sensor.getState());
    freeReplyObject(reply);

    testSensor();

    // Aspetta una risposta dal tester
    reply = (redisReply *)redisCommand(context, "GET tester_response");
    if (reply != nullptr && reply->str != nullptr)
    {
        freeReplyObject(reply);
    }

    char state[20];
    sensor_type sensorState = static_cast<sensor_type>(atoi(reply->str));
    int2stateSensor(state, sensorState);
    if (strcmp(state, "CHECKING") == 0)
    {
        int movement;
        sscanf(reply->str, "%d", &movement); // converte reply in int
        if (movement == 0)
        {
            sensor.setMovement(false);
        }
        else
        {
            sensor.setMovement(true);
            std::string message = "movement detected";
            redisReply *reply = (redisReply *)redisCommand(context, "PUBLISH channel %s", message.c_str());
            freeReplyObject(reply);
        }
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}
