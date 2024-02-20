#include <iostream>
#include <random>
#include <hiredis/hiredis.h>
#include "pgsql.h"
#include <postgresql/libpq-fe.h>
#include <unistd.h>
#include "conditioner.h"
#include <string.h>

int main()
{
    auto tempo_iniziale = std::chrono::steady_clock::now();
    // Connessione a Redis
    redisContext *context = redisConnect("127.0.0.1", 6379);
    if (context == NULL || context->err)
    {
        if (context)
        {
            std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
            redisFree(context);
        }
        else
        {
            std::cerr << "Impossibile connettersi a Redis." << std::endl;
        }
        exit(1);
    }

    Con2DB db1("localhost", "5432", "smarthome", "12345", "logdb_smarthome");
    int pid;

    /* init random number generator  */
    srand((unsigned)time(NULL));

    pid = getpid();

    printf("Start conditioner with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());

    /* init conditioner state */
    Conditioner conditioner = initConditioner();

    // Sottoscrizione al canale
    redisReply *reply = (redisReply *)redisCommand(context, "SUBSCRIBE conditionerChannel");
    freeReplyObject(reply);

    while (true)
    {
        int countMessage = 0;
        int temperature = 0;
        conditioner_type state;

        while (countMessage < 2)
        {
            if (redisGetReply(context, (void **)&reply) != REDIS_OK)
            {
                std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                exit(1);
            }
            if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
            {

                if (countMessage == 0)
                {
                    state = static_cast<conditioner_type>(atoi(reply->element[2]->str));
                }
                else if (countMessage == 1)
                {
                    temperature = (atoi(reply->element[2]->str));
                }

                freeReplyObject(reply);
            }
            countMessage++;
            sleep(1);
        }
        
        const char *sms;
        if (rand() % 100 >= 5)
        {
            sms = "ok";
            if (state == change_temperature)
            {
                conditioner.modifyTemperature(temperature);
            }
            conditioner.setState(state);
            auto tempo_corrente = std::chrono::steady_clock::now();
            auto tempo_trascorso = std::chrono::duration_cast<std::chrono::milliseconds>(tempo_corrente - tempo_iniziale).count();
            log2conditionerdb(db1, conditioner.getId(), pid, conditioner.getState(), conditioner.getTemperature(), tempo_trascorso);
        }
        else
        {
            sms = "Comando fallito";
            sleep(10);
        }

        sleep(3);
            redisContext *context2 = redisConnect("127.0.0.1", 6379);
            std::cout << "messaggio mandato " << sms << std::endl;
            redisReply *secondReply = (redisReply *)redisCommand(context2, "PUBLISH rispostaChannel %s", sms);
            if (secondReply != NULL)
            {
                freeReplyObject(secondReply);
            }
            else
            {
                std::cerr << "Errore nell'invio del messaggio a Redis." << std::endl;
            }
    }

    redisFree(context);
    return 0;
}
