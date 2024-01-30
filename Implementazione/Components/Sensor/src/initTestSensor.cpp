#include "../../../main/src/main.h"
#include "../../../main/src/global.h"

// Funzione per inizializzare e testare un sensore.
int initTestSensor(Sensor &sensor)
{
    // Dichiarazione di variabili locali per memorizzare l'ID e lo stato del sensore.
    int sensorId;
    sensor_type sensorState;
    char state[20];

    // Inizializza la connessione a Redis.
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        // Gestisci l'errore nel caso di una connessione non riuscita a Redis.
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Ottieni l'ID e lo stato del sensore.
    sensorId = sensor.getId();
    sensorState = sensor.getState();

    // Invia l'ID e lo stato a Redis.
    redisReply *reply = (redisReply *)redisCommand(context, "SET sensor_id %d", sensorId);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET sensor_state %d", sensorState);
    freeReplyObject(reply);

    // Esegui il test del sensore.
    testSensor();

    // Converti lo stato numerico del sensore in una stringa descrittiva.
    int2stateSensor(state, sensorState);

    // Verifica lo stato del sensore e agisci di conseguenza.
    if ((strcmp(state, "SensorOFF") == 0) || strcmp(state, "SensorON") == 0)
    {
        // Se lo stato è "SensorOFF" o "SensorON", il sensore non rileva movimenti.
        sensor.setMovement(false);
        std::string message = "movement not detected";
        reply = (redisReply *)redisCommand(context, "SET message %s", message.c_str());
        freeReplyObject(reply);
    }
    if (strcmp(state, "CHECKING") == 0)
    {
        // Se lo stato è "CHECKING", verifica se il movimento è stato rilevato.
        reply = (redisReply *)redisCommand(context, "GET movment");

        // Ottieni l'informazione sul movimento dal tester.
        int movement = std::stoi(reply->str);
        freeReplyObject(reply);

        // Agisci in base alla presenza o assenza di movimento.
        if (movement == 1)
        {
            sensor.setMovement(true);
            std::string message = "movement detected";
            reply = (redisReply *)redisCommand(context, "SET message %s", message.c_str());
            freeReplyObject(reply);
            std::cout << "ATTENZIONE MOVIMENTO RILEVATO, INVIO MESSAGGIO ALLARME IN CORSO" << std::endl; // Simulaziodi di una notifica per le emergenze
        }
        else
        {
            std::string message = "movement not detected";
            reply = (redisReply *)redisCommand(context, "SET message %s", message.c_str());
            freeReplyObject(reply);
            sensor.setMovement(false);
        }
    }

    // Chiudi la connessione a Redis.
    redisFree(context);

    return 0;
}
