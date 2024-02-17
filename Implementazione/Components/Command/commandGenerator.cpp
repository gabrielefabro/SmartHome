#include "command.h"

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

    Con2DB db1("localhost", "5432", "smarthome", "47002", "logdb_smarthome");
    PGresult *res;
    char buf[200];
    int pid;
    int t = 0;

    /* init random number generator  */
    srand((unsigned)time(NULL));

    redisReply *reply;
    while (t < HORIZON)
    {
        components comp = static_cast<components>(rand() % 6);
        std::string compString;

        switch (comp)
        {
        case Camera:
        {
            auto comando = static_cast<camera_type>(rand() % 2);
            reply = (redisReply *)redisCommand(redis_conn, "SET comp:%d comando:%d", comp, comando);
            break;
        }
        case Conditioner:
        {
            auto comando = static_cast<conditioner_type>(rand() % 3);
            int value = 0;
            if (comando == change_temperature)
            {
                value = changeRandomTemperature();
            }
            reply = (redisReply *)redisCommand(redis_conn, "SET comp:%d comando:%d temperature:%d", comp, comando, value);
            break;
        }
        case Device:
        {
            auto comando = static_cast<device_type>(rand() % 3);
            auto nomeDev = static_cast<nome_type>(rand() % 8);
            int inizio = 0;
            int fine = 0;
            if (comando == programmed)
            {
                inizio = changeInt();
                fine = changeInt();
            }
            reply = (redisReply *)redisCommand(redis_conn, "SET comp:%d comando:%d nomeDev: %d inizio:%d fine:%d", comp, comando, nomeDev, inizio, fine);
            break;
        }
        case Light:
        {
            auto comando = static_cast<light_type>(rand() % 4);
            const char *color;
            int intensity = 0;
            if (comando == change_color)
            {
                color = colorToString(getRandomColor());
            }
            if (comando == change_intensity)
            {
                intensity = changeIntensity();
            }
            reply = (redisReply *)redisCommand(redis_conn, "SET comp:%d comando:%d color:%s intensity:%d", comp, comando, color, intensity);
            break;
        }
        case Sensor:
        {
            auto comando = static_cast<sensor_type>(rand() % 2);
            reply = (redisReply *)redisCommand(redis_conn, "SET comp:%d comando:%d", comp, comando);
            break;
        }
        case SensorGarden:
        {
            auto comando = static_cast<sensorGarden_type>(rand() % 4);
            reply = (redisReply *)redisCommand(redis_conn, "SET comp:%d comando:%d humidity:%d temperature:%d", comp, comando);
            break;
        }
        default:
            break;
        }

        if (reply == NULL)
        {
            std::cerr << "Errore nella pubblicazione della risposta su Redis." << std::endl;
            freeReplyObject(reply);
        }
        else
        {
            std::cout << "Publisher: Risposta pubblicata su Redis." << std::endl;
            freeReplyObject(reply);

            const char *message = "yeahBAby";

            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel mssg:%s", message);

            // Utilizziamo redisGetReply per ottenere la risposta da Redis
            if (redisGetReply(redis_conn, (void **)&reply) != REDIS_OK)
            {
                std::cerr << "Errore nella ricezione del messaggio da Redis." << std::endl;
                exit(1);
            }

            if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
            {
                std::string received_message = reply->element[2]->str;
                std::cout << "Receiver: Messaggio ricevuto da Redis: " << received_message << std::endl;

                if (received_message == "Ok")
                {
                    std::cout << "Comando eseguito con successo" << std::endl;
                }
                else if (received_message == "Not ok")
                {
                    // Fare qualcosa se il comando non è andato a buon fine
                }
            }

            freeReplyObject(reply);
        }
        t++;
    }

    redisFree(redis_conn);
    return 0;
}
