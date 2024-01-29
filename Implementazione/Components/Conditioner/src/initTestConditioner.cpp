#include "conditioner.h"
#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

// Funzione per testare un condizionatore e generare un qualsiasi scenario possibile
int initTestConditioner(Conditioner &conditioner)
{
    char state[20];
    int conditionerId, conditionerTemperature;
    conditioner_type conditionerState;

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        // Stampa un messaggio di errore se la connessione a Redis fallisce.
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Ottieni l'ID, lo stato e la temperatura corrente del condizionatore.
    conditionerId = conditioner.getId();
    conditionerState = conditioner.getState();
    conditionerTemperature = conditioner.getTemperature();

    // Invia l'ID, lo stato e la temperatura al database Redis.
    redisReply *reply = (redisReply *)redisCommand(context, "SET conditioner_id %d", conditionerId);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET conditioner_state %d", conditionerState);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET conditioner_temperature %d", conditionerTemperature);
    freeReplyObject(reply);

    // Esegui un test del condizionatore.
    testConditioner();

    // Converti lo stato del condizionatore in una rappresentazione di stringa.
    int2stateConditioner(state, conditionerState);

    // Se lo stato del condizionatore è "change_temperature", ottieni la nuova temperatura dal database Redis.
    if (strcmp(state, "change_temperature") == 0)
    {
        reply = (redisReply *)redisCommand(context, "GET new_temperature");
        int newTemperature;
        newTemperature = std::stoi(reply->str);
        conditioner.modifyTemperature(newTemperature);
    }

    // Chiudi la connessione a Redis.
    redisFree(context);

    return 0;
}
