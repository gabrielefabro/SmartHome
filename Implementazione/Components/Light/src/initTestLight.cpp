#include "../../../main/src/main.h"
#include <iostream>

// Funzione di inizializzazione per il test della luce.
int initTestLight(Light &light)
{
    // Dichiarazioni di variabili locali
    int lightId;
    light_type lightState;
    char state[20];

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        // Stampa un messaggio di errore se la connessione a Redis fallisce.
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Ottieni l'ID e lo stato corrente della luce.
    lightId = light.getId();
    lightState = light.getState();

    // Invia l'ID e lo stato della luce a Redis.
    redisReply *reply = (redisReply *)redisCommand(context, "SET light_id %d", lightId);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET light_state %d", lightState);
    freeReplyObject(reply);

    // Esegui un test sulla luce.
    testLight();

    // Converti lo stato della luce in una rappresentazione di stringa.
    int2stateLight(state, lightState);

    // Se lo stato della luce è "change_color" o "change_intensity", leggi la risposta dal tester in Redis e
    // aggiorna lo stato della luce di conseguenza.
    if (strcmp(state, "change_color") == 0 || strcmp(state, "change_intensity") == 0)
    {
        // Leggi la risposta dal tester.
        reply = (redisReply *)redisCommand(context, "GET tester_response");

        // Se lo stato è "change_color", estrai il colore dalla risposta e aggiorna lo stato della luce.
        if (strcmp(state, "change_color") == 0)
        {
            char colorStr[20];
            sscanf(reply->str, "%s", colorStr);
            light_color newColor = stringToLightColor(colorStr);
            light.setColor(newColor);
        }
        // Se lo stato è "change_intensity", estrai l'intensità dalla risposta e aggiorna lo stato della luce.
        else if (strcmp(state, "change_intensity") == 0)
        {
            int newIntensity = std::stoi(reply->str);
            light.setIntensity(newIntensity);
        }

        freeReplyObject(reply);
    }

    // Chiudi la connessione a Redis.
    redisFree(context);

    return 0;
}
