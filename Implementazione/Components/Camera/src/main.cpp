#include "camera.h"

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
    int pid;
    char buf[200];
    int t = 0;
    const char *response;

    /* init random number generator  */
    srand((unsigned)time(NULL));

    pid = getpid();

    printf("Start camera with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());

    /* init camera state */
    Camera camera = initCamera();

    // Sottoscrizione al canale
    redisReply *reply = (redisReply *)redisCommand(context, "SUBSCRIBE cameraChannel");
    freeReplyObject(reply);

    while (true)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 100);
        camera_type state;

        if (redisGetReply(context, (void **)&reply) != REDIS_OK)
        {
            std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
            exit(1);
        }
        else
        {
            std::cout << "camera ha ricevuto qualcosa " << std::endl;
        }
        if (reply->type == REDIS_REPLY_ARRAY && strcmp(reply->element[0]->str, "message") == 0)
        {
            std::cout << "il messaggio va bene" << std::endl;

            if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
            {
                const char *received_message = reply->element[2]->str;
                std::cout << "Receiver: Messaggio ricevuto da Redis: " << received_message << std::endl;

                if (true)
                {
                    response = "ok";
                    state = static_cast<camera_type>(atoi(reply->element[2]->str));

                    freeReplyObject(reply);

                    if (state == CameraOFF)
                    {
                        camera.setRecording(false);
                    }
                    else if (state == CameraON)
                    {
                        camera.setRecording(true);
                    }
                    log2cameradb(db1, camera.getId(), pid, camera.getState(), camera.getRecording());

                    // Scriviamo una risposta sulla stessa stream
                    redisReply *publish_reply = (redisReply *)redisCommand(context, "PUBLISH userInput_channel %s", response);
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
                else
                {
                    response = "no";
                    // Scriviamo una risposta sulla stessa stream
                    redisReply *publish_reply = (redisReply *)redisCommand(context, "PUBLISH userInput_channel %s", response);
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
            freeReplyObject(reply);
        }
    }

    redisFree(context);
    return 0;
}
