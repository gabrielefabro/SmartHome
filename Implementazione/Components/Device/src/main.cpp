#include <iostream>
#include <random>
#include <unistd.h>
#include "device.h"
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

    printf("Start device with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());

    /* init device state */
    Device device = initDevice();

    // Sottoscrizione al canale
    redisReply *reply = (redisReply *)redisCommand(context, "SUBSCRIBE deviceChannel");
    freeReplyObject(reply);

    while (true)
    {
        device_type state;
        nome_type nome;
        int countMessage = 0;
        int inizio = 0;
        int fine = 0;

        // Utilizziamo redisGetReply per ottenere la risposta da Redis
        while (countMessage < 4)
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
                    state = static_cast<device_type>(atoi(reply->element[2]->str));
                }
                else if (countMessage == 1)
                {
                    nome = static_cast<nome_type>(atoi(reply->element[2]->str));
                }
                else if (countMessage == 2)
                {
                    inizio = (atoi(reply->element[2]->str));
                }
                else if (countMessage == 3)
                {
                    fine = (atoi(reply->element[2]->str));
                }

                freeReplyObject(reply);
            }
            countMessage++;
        }

        if (state == programmed)
        {
            device.programmed_device(inizio, fine);
        }
        device.setName(nome);
        device.setState(state);
        auto tempo_corrente = std::chrono::steady_clock::now();
        auto tempo_trascorso = std::chrono::duration_cast<std::chrono::milliseconds>(tempo_corrente - tempo_iniziale).count();
        log2devicedb(db1, device.getId(), pid, device.getState(), device.getNome(), inizio, fine, tempo_trascorso);
    }

    redisFree(context);
    return 0;
}