#include <iostream>
#include <random>
#include <hiredis/hiredis.h>
#include "../../con2db/src/pgsql.h"
#include <postgresql/libpq-fe.h>
#include <unistd.h>
#include "sensor.h"
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

    printf("Start camera with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());

    /* init traffic light state */
    Sensor sensor = initSensor();

    redisReply *reply;

    while (true)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 100);

        if (dis(gen) > 5)
        {
            response = "ok";
            // Utilizziamo redisGetReply per ottenere la risposta da Redis
            reply = (redisReply *)redisCommand(redis_conn, "SUBSCRIBE sensorChannel");
            if (reply == NULL)
            {
                std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                exit(1);
            }

            if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
            {
                std::string received_message = reply->element[2]->str;
                std::cout << "Receiver: Messaggio ricevuto da Redis: " << received_message << std::endl;

                if (strcmp(received_message.c_str(), "SensorON") == 0)
                {
                    sensor.setCheck(true);
                }
                else if (strcmp(received_message.c_str(), "SensorOFF") == 0)
                {
                    sensor.setCheck(false);
                }

                log2sensordb(db1, sensor.getId(), pid, sensor.getState(), sensor.getCheck());

                // Scriviamo una risposta sulla stessa stream
                redisReply *publish_reply = (redisReply *)redisCommand(redis_conn, "PUBLISH sensorChannel %s", response);
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
