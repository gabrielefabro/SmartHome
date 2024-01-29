#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

// Funzione di inizializzazione per il test del dispositivo.
int initTestDevice(Device &device)
{
    // Dichiarazioni di variabili locali
    int deviceId;
    device_type deviceState;
    char state[20];

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        // Stampa un messaggio di errore se la connessione a Redis fallisce.
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Ottieni l'ID e lo stato corrente del dispositivo.
    deviceId = device.getId();
    deviceState = device.getState();

    // Invia l'ID, lo stato e il nome del dispositivo a Redis.
    redisReply *reply = (redisReply *)redisCommand(context, "SET device_id %d", deviceId);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET device_state %d", deviceState);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET nome_device %d", device.getNome());
    freeReplyObject(reply);

    // Esegui un test del dispositivo.
    testDevice();

    // Converti lo stato del dispositivo in una rappresentazione di stringa.
    int2stateDevice(state, deviceState);

    // Se lo stato del dispositivo è "programmed", recupera gli intervalli di tempo salvati in Redis e programma il dispositivo.
    if (strcmp(state, "programmed") == 0)
    {
        // Recupera il primo intervallo di tempo da Redis.
        reply = (redisReply *)redisCommand(context, "GET new_int1");
        int interval1 = std::atoi(reply->str);
        freeReplyObject(reply);

        // Recupera il secondo intervallo di tempo da Redis.
        reply = (redisReply *)redisCommand(context, "GET new_int2");
        int interval2 = std::atoi(reply->str);
        freeReplyObject(reply);

        // Programma il dispositivo con gli intervalli di tempo recuperati.
        device.programmed_device(interval1, interval2);
    }

    // Chiudi la connessione a Redis.
    redisFree(context);

    return 0;
}
