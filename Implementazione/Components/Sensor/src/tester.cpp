#include "sensor.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <ctime>


int main() {
    
    char state[20];

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err) {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

     // Leggi ID e STATE da Redis
    redisReply *reply = (redisReply *)redisCommand(context, "GET sensor_id");
    int lightId = atoi(reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "GET sensor_state");
    sensor_type sensorState = static_cast<sensor_type>(atoi(reply->str));
    freeReplyObject(reply);

    int2state(state,sensorState);

    if(strcmp(state, "CHEKING"))
    {
        // Inizializza il generatore di numeri casuali con il tempo corrente
        std::srand(std::time(0));

        // Genera un numero casuale tra 0 e RAND_MAX
        int n = std::rand();

        // Invia se e' presente movimento a Redis
        reply = (redisReply *)redisCommand(context, "SET new_color %s", n);
        freeReplyObject(reply);
    }


    // Chiudi la connessione a Redis
    redisFree(context);

    return 0;
}

