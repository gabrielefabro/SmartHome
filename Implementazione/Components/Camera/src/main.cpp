#include "camera.h"
#include <hiredis/hiredis.h>


int main()
{
    const char *redis_host = "127.0.0.1";
    int redis_port = 6379;
    struct timeval timeout = {1, 500000};

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
    int pid;
    const char *response;

    /* init random number generator  */
    srand((unsigned)time(NULL));

    pid = getpid();

    printf("Start camera with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());

    /* init traffic light state */
    Camera camera = initCamera();

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
            reply = (redisReply *)redisCommand(redis_conn, "SUBSCRIBE cameraChannel");
            if (reply == NULL)
            {
                std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                exit(1);
            }

            if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
            {
                std::string received_message = reply->element[2]->str;
                std::cout << "Receiver: Messaggio ricevuto da Redis: " << received_message << std::endl;

                if (strcmp(received_message.c_str(), "CameraOFF") == 0)
                {
                    camera.setRecording(false);
                }
                else if (strcmp(received_message.c_str(), "CameraON") == 0)
                {
                    camera.setRecording(true);
                }

                log2cameradb(db1, camera.getId(), pid, camera.getState(), camera.getRecording());

                // Scriviamo una risposta sulla stessa stream
                redisReply *publish_reply = (redisReply *)redisCommand(redis_conn, "PUBLISH cameraChannel %s", response);
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
            redisReply *publish_reply = (redisReply *)redisCommand(redis_conn, "PUBLISH cameraChannel %s", response);
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
