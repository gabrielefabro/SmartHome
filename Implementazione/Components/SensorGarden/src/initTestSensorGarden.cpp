#include "../../../main/main.h"
#include "../../../main/global.h"

int initTestSensorGarden(SensorGarden sensorGarden)
{

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Inizializza un oggetto SensorGarden
    SensorGarden sensorGarden = initSensorGarden();

    // Invia ID e STATE a Redis
    redisReply *reply = (redisReply *)redisCommand(context, "SET sensorGarden_id %d", sensorGarden.getId());
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET sensorGarden_state %d", sensorGarden.getState());
    freeReplyObject(reply);

    testSensorGarden();

    // Aspetta una risposta dal tester
    reply = (redisReply *)redisCommand(context, "GET humidity");
    if (reply != nullptr && reply->str != nullptr)
    {
        freeReplyObject(reply);
    }

    int humidity = reply->integer;

    char state[20];
    sensorGarden_type sensorGardenState = static_cast<sensorGarden_type>(atoi(reply->str));
    int2stateSensorGarden(state, sensorGardenState);

    if (strcmp(state, "change_light") == 0)
    {
        // Aspetta una risposta dal tester
        reply = (redisReply *)redisCommand(context, "GET temperature");
        if (reply != nullptr && reply->str != nullptr)
        {
            freeReplyObject(reply);
        }

        int temperature = reply->integer;

        // Adjust the lights based on humidity and temperature conditions
        if (humidity > 50 && temperature > 25)
        {
            std::cout << "luci spente" << std::endl;
        }
        else
        {
            std::cout << "luci accese" << std::endl;
        }
    }
    else if (strcmp(state, "set_sprinklers") == 0)
    {
        // Adjust irrigation based on humidity conditions
        if (humidity < 30)
        {
            std::cout << "irrigatori accesi" << std::endl;
        }
        else
        {
            std::cout << "irrigatori spenti" << std::endl;
        }
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}
