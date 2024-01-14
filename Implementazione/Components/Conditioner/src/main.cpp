#include "conditioner.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <ctime>
#include <cstdlib>
#include "global.h"

int main()
{

    int t = 0;
    int pid;
    char buf[200];

    // Inizializza database
    Con2DB db1("localhost", "5432", "smarthome", "12345", "logdb_smarthome");

    pid = getpid();

    /* init time */
    init_time();

    // Inizializza la connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err)
    {
        std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
        return 1;
    }

    // Inizializza un oggetto Conditioner
    Conditioner conditioner = initConditioner();

    init_logdb(db1, pid, conditioner.getId(), conditioner.getState());

    while (t < HORIZON)
    {

        nanos_day = nanos2day(buf, nanos);

        // Invia ID e STATE a Redis
        redisReply *reply = (redisReply *)redisCommand(context, "SET conditioner id %d", conditioner.getId());
        freeReplyObject(reply);

        reply = (redisReply *)redisCommand(context, "SET conditioner_state %d", conditioner.getState());
        freeReplyObject(reply);

        test();

        // Aspetta una risposta dal tester
        reply = (redisReply *)redisCommand(context, "GET tester_response");
        if (reply != nullptr && reply->str != nullptr)
        {
            freeReplyObject(reply);
        }

        char state[20];
        conditioner_type conditionerState = static_cast<conditioner_type>(atoi(reply->str));
        int2state(state, conditionerState);

        if (strcmp(state, "change_temperature") == 0)
        {
            int newTemperature;
            newTemperature = reply->integer;
            conditioner.modifyTemperature(newTemperature);
        }

        log2db(db1, pid, nanos, conditioner.getState(), conditioner.getTemperature());

        // Chiudi la connessione a Redis
        redisFree(context);

        conditioner.next();

        t++;

        /* sleep   */
        micro_sleep(500);
    }
    log2stdout(db1, pid);
    return 0;
}
