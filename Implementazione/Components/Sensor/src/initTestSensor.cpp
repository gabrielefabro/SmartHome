#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

int initTestSensor(Sensor &sensor)
{
    int sensorId;
    sensor_type sensorState;
    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    sensorId = sensor.getId();
    sensorState = sensor.getState();

    // Invia ID e STATE a Redis
    redisReply *reply = (redisReply *)redisCommand(context, "SET sensor_id %d", sensorId);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET sensor_state %d", sensorState);
    freeReplyObject(reply);

    testSensor();

    // Aspetta una risposta dal tester

    char state[20];
    int2stateSensor(state, sensorState);

    if ((strcmp(state, "SensorOFF") == 0) || strcmp(state, "SensorON") == 0)
    {
        sensor.setMovement(false);
        std::string message = "movement not detected";
        redisReply *reply = (redisReply *)redisCommand(context, "SET message %s", message.c_str());
        freeReplyObject(reply);
    }
    if (strcmp(state, "CHECKING") == 0)
    {
        reply = (redisReply *)redisCommand(context, "GET movment");

        int movement = std::stoi(reply->str);
        freeReplyObject(reply);
        if (movement == 1)
        {
            std::cout << "TROVATO MOVIMENTO" << std::endl;
            sensor.setMovement(true);
            std::cout << "lo stato è " << sensor.getMovement() << std::endl;
            std::string message = "movement detected";
            redisReply *reply = (redisReply *)redisCommand(context, "SET message %s", message.c_str());
            freeReplyObject(reply);
        }
        else
        {
            std::string message = "movement not detected";
            redisReply *reply = (redisReply *)redisCommand(context, "SET message %s", message.c_str());
            freeReplyObject(reply);
            sensor.setMovement(false);
        }
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}
