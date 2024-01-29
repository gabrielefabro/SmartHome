#include "sensorGarden.h"
#include "../../../main/src/main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>

// Funzione di test per il sensore da giardino
int testSensorGarden()
{
    bool corretto;
    int humidity, temperature;
    char state[20];

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Leggi ID, STATE, TEMPERATURE, HUMIDITY da Redis
    redisReply *reply = (redisReply *)redisCommand(context, "GET sensorGarden_id");
    int sensorGardenId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET sensorGarden_state");
    sensorGarden_type sensorGardenState = static_cast<sensorGarden_type>(atoi(reply->str));
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET sensorGarden_temperature");
    int sensorGardenTemperature = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET sensorGarden_humidity");
    int sensorGardenHumidity = atoi(reply->str);
    freeReplyObject(reply);

    int2stateSensorGarden(state, sensorGardenState);

    // Verifica se lo stato richiede una simulazione di cambiamento
    if (strcmp(state, "change_light") == 0 || strcmp(state, "set_sprinklers") == 0)
    {
        corretto = true;
        // Genera nuovi valori di umidità e temperatura
        while (corretto)
        {
            humidity = std::rand() % 101;
            temperature = std::rand() % 46;
            // Verifica se i nuovi valori sono vicini ai valori attuali
            if ((humidity < sensorGardenHumidity + 5) && (humidity > sensorGardenHumidity - 5) &&
                (temperature < sensorGardenTemperature + 5) && (temperature > sensorGardenTemperature - 5))
            {
                corretto = false;
            }
        }

        // Aggiorna i valori di umidità e temperatura in Redis
        redisReply *reply = (redisReply *)redisCommand(context, "MSET humidity %d temperature %d", humidity, temperature);
        freeReplyObject(reply);
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}
