#include <iostream>
#include <random>
#include <unistd.h>
#include "device.h"
#include <string.h>

int main()
{
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
    PGresult *res;
    char buf[200];
    int pid;
    int t = 0;
    const char *response;

    /* init random number generator  */
    srand((unsigned)time(NULL));

    pid = getpid();

    printf("Start device with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());

    /* init device state */
    Device device = initDevice();

    // Sottoscrizione al canale
    redisReply *reply = (redisReply *)redisCommand(context, "SUBSCRIBE deviceChannel");
    if (reply == NULL || context->err)
    {
        std::cerr << "Errore durante la sottoscrizione al canale." << std::endl;
        exit(1);
    }
    freeReplyObject(reply);

    while (true)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 100);
        device_type state;
        nome_type nome;
        int countMessage = 0;
        int inizio = 0;
        int fine = 0;

        if (dis(gen) > 5)
        {
            if (redisGetReply(context, (void **)&reply) != REDIS_OK)
            {
                std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                exit(1);
            }
            
            response = "ok";
            // Utilizziamo redisGetReply per ottenere la risposta da Redis
            const int TIMEOUT_SECONDS = 1;
            time_t startTime = time(NULL);
            while (difftime(time(NULL), startTime) < TIMEOUT_SECONDS)
            {
                reply = (redisReply *)redisCommand(redis_conn, "GET deviceChannel");

                std::string message = reply->element[2]->str;
                std::cout << "Messaggio ricevuto da Redis: " << message << std::endl;

                if (countMessage == 0)
                {
                    state = static_cast<device_type>(atoi(reply->str));
                }
                else if (countMessage == 1)
                {
                    nome = static_cast<nome_type>(atoi(reply->str));
                }
                else if (countMessage == 2)
                {
                    inizio = (atoi(reply->str));
                }
                else if (countMessage == 3)
                {
                    fine = (atoi(reply->str));
                }

                 freeReplyObject(reply);
            }

            if (state == programmed)
            {
                device.programmed_device(inizio,fine);
            }
            device.setState(state);
            log2devicedb(db1, device.getId(), pid, device.getState(), device.getNome(), inizio, fine);

            // Scriviamo una risposta sulla stessa stream
            redisReply *publish_reply = (redisReply *)redisCommand(redis_conn, "PUBLISH deviceChannel %s", response);
            if (publish_reply == NULL)
            {
                std::cerr << "Errore nella pubblicazione della risposta su Redis." << std::endl;
            }
            else
            {
                std::cout << "Publisher: Risposta pubblicata su Redis." << std::endl;
                freeReplyObject(publish_reply);
            }
            

            freeReplyObject(reply);
        }
        else
        {
            response = "no";
            // Scriviamo una risposta sulla stessa stream
            redisReply *publish_reply = (redisReply *)redisCommand(redis_conn, "PUBLISH response_channel %s", response);
            if (publish_reply == NULL)
            {
                std::cerr << "Errore nella pubblicazione della risposta su Redis." << std::endl;
            }
            else
            {
                std::cout << "Publisher: Risposta pubblicata su Redis." << std::endl;
                freeReplyObject(publish_reply);
            }
        }
    }

    redisFree(redis_conn);
    return 0;
}