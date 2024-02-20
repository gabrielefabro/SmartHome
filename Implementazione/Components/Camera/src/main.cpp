#include "camera.h"

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

    printf("Start camera with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());

    /* init camera state */
    Camera camera = initCamera();

    // Sottoscrizione al canale
    redisReply *reply = (redisReply *)redisCommand(context, "SUBSCRIBE cameraChannel");
    freeReplyObject(reply);

    while (true)
    {
        camera_type state;

        if (redisGetReply(context, (void **)&reply) != REDIS_OK)
        {
            std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
            exit(1);
        }

        if (reply->type == REDIS_REPLY_ARRAY && strcmp(reply->element[0]->str, "message") == 0)
        {

            if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
            {
                const char *sms;
                if (rand() % 100 >= 5)
                {
                    sms = "ok";
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
                    auto tempo_corrente = std::chrono::steady_clock::now();
                    auto tempo_trascorso = std::chrono::duration_cast<std::chrono::milliseconds>(tempo_corrente - tempo_iniziale).count();
                    log2cameradb(db1, camera.getId(), pid, camera.getState(), camera.getRecording(), tempo_trascorso);
                }
                else
                {
                    sms = "Comando fallito";
                }

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
        }
    }

    redisFree(context);
    return 0;
}
