#include "conditioner.h"
#include "../../../main/src/main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>

// Funzione di test per il condizionatore
int testConditioner()
{
    char state[20];
    bool corretto;
    int newTemperature;

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        // Stampa un messaggio di errore se la connessione a Redis fallisce.
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Ottieni l'ID, lo stato e la temperatura corrente del condizionatore da Redis.
    redisReply *reply = (redisReply *)redisCommand(context, "GET conditioner_id");
    int conditionerId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET conditioner_state");
    conditioner_type conditionerState = static_cast<conditioner_type>(atoi(reply->str));
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET conditioner_temperature");
    int conditionerTemperature = atoi(reply->str);
    freeReplyObject(reply);

    // Converti lo stato del condizionatore in una rappresentazione di stringa.
    int2stateConditioner(state, conditionerState);

    // Se lo stato del condizionatore è "change_temperature", modifica la temperatura in modo casuale.
    if (strcmp(state, "change_temperature") == 0)
    {
        corretto = true;

        // Esegui un loop finché non ottieni una nuova temperatura che non sia troppo distante dalla precedente, questo per creare uno scenario realistico.
        while (corretto)
        {
            newTemperature = changeRandomTemperature();

            // Verifica
            if ((newTemperature < conditionerTemperature + 8) && (newTemperature > conditionerTemperature - 8))
            {
                corretto = false;
            }
        }

        // Aggiorna la temperatura nel database Redis.
        reply = (redisReply *)redisCommand(context, "SET new_temperature %d", newTemperature);
        freeReplyObject(reply);
    }

    // Chiudi la connessione a Redis.
    redisFree(context);

    return 0;
}
