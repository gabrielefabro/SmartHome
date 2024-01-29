#include "light.h"
#include "../../../main/src/main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>

// Funzione di test per la classe Light.
int testLight()
{
    // Dichiarazione di variabili locali per memorizzare lo stato e l'ID della luce.
    char state[20];
    int lightId;
    light_type lightState;

    // Inizializza la connessione a Redis.
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        // Gestione dell'errore in caso di problemi di connessione a Redis.
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Leggi l'ID e lo stato della luce da Redis.
    redisReply *reply = (redisReply *)redisCommand(context, "GET light_id");
    lightId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET light_state");
    lightState = static_cast<light_type>(atoi(reply->str));
    freeReplyObject(reply);

    // Converti lo stato numerico della luce in una stringa descrittiva.
    int2stateLight(state, lightState);

    // Verifica se lo stato indica un cambio di colore della luce.
    if (strcmp(state, "change_color") == 0)
    {
        // Genera un nuovo colore casuale per la luce.
        light_color newColor = getRandomColor();

        // Invia il nuovo colore a Redis come risposta al tester.
        reply = (redisReply *)redisCommand(context, "SET tester_response %s", colorToString(newColor));
        freeReplyObject(reply);
    }
    // Verifica se lo stato indica un cambio di intensità della luce.
    else if (strcmp(state, "change_intensity") == 0)
    {
        // Genera una nuova intensità casuale per la luce.
        int newIntensity = changeIntensity();

        // Invia la nuova intensità a Redis come risposta al tester.
        reply = (redisReply *)redisCommand(context, "SET tester_response %d", newIntensity);
        freeReplyObject(reply);
    }

    // Chiudi la connessione a Redis.
    redisFree(context);

    return 0;
}
