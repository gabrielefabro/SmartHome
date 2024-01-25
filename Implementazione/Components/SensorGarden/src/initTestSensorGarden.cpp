#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

int initTestSensorGarden(SensorGarden &sensorGarden)
{
    int sensorGardenId;
    sensorGarden_type sensorGardenState;
    int sensorGardenTemperature, sensorGardenHumidity;

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    sensorGardenId = sensorGarden.getId();
    sensorGardenState = sensorGarden.getState();
    sensorGardenTemperature = sensorGarden.getTemperature();
    sensorGardenHumidity = sensorGarden.getHumidity();

    // Invia ID e STATE a Redis
    redisReply *reply = (redisReply *)redisCommand(context, "SET sensorGarden_id %d", sensorGardenId);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET sensorGarden_state %d", sensorGardenState);
    freeReplyObject(reply);

    // Invia ID e STATE a Redis
    reply = (redisReply *)redisCommand(context, "SET sensorGarden_temperature %d", sensorGardenTemperature);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET sensorGarden_humidity %d", sensorGardenHumidity);
    freeReplyObject(reply);

    testSensorGarden();

    char state[20];
    int2stateSensorGarden(state, sensorGardenState);

    if (strcmp(state, "change_light") == 0 || strcmp(state, "set_sprinklers") == 0)
    {
        // Aspetta una risposta dal tester
        reply = (redisReply *)redisCommand(context, "GET humidity");
        int humidity = std::atoi(reply->str);
        sensorGarden.setHumidity(humidity);
        freeReplyObject(reply);
        // Aspetta una risposta dal tester
        reply = (redisReply *)redisCommand(context, "GET temperature");
        int temperature = std::atoi(reply->str);
        freeReplyObject(reply);
        sensorGarden.setTemperature(temperature);

    }
    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}
