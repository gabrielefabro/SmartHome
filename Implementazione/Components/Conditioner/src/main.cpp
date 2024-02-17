#include <iostream>
#include <random>
#include <hiredis/hiredis.h>
#include "../../con2db/src/pgsql.h"
#include <postgresql/libpq-fe.h>
#include <unistd.h>
#include "conditioner.h"
#include <string.h>

int main()
{
    const char *redis_host = "127.0.0.1";
    int redis_port = 6379;
    struct timeval timeout = {1, 100000000000000};

    redisContext *redis_conn = redisConnectWithTimeout(redis_host, redis_port, timeout);
    if (redis_conn == NULL || redis_conn->err)
    {
        if (redis_conn)
        {
            std::cerr << "Errore nella connessione a Redis: " << redis_conn->errstr << std::endl;
            redisFree(redis_conn);
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

    printf("Start conditioner with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());

    /* init traffic light state */
    Conditioner conditioner = initConditioner();

    redisReply *reply;

    while (true)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 100);
        int countMessage = 0;
        int temperature = 0;
        conditioner_type state;

        if (dis(gen) > 5)
        {
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
                    state = static_cast<conditioner_type>(atoi(reply->str));
                }
                else if (countMessage == 1)
                {
                    temperature = (atoi(reply->str));
                }

                freeReplyObject(reply);
            }

            if (state == change_temperature)
            {
                conditioner.modifyTemperature(temperature);
            }
            conditioner.setState(state);
            log2conditionerdb(db1, conditioner.getId(), pid, conditioner.getState(), conditioner.getTemperature());

            // Scriviamo una risposta sulla stessa stream
            redisReply *publish_reply = (redisReply *)redisCommand(redis_conn, "PUBLISH conditionerChannel %s", response);
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
