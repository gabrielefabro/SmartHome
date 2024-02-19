#include "command.h"

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
    PGresult *res;
    char buf[200];
    int pid;
    int t = 0;

    /* init random number generator  */
    srand((unsigned)time(NULL));

    redisReply *reply;
    while (t < HORIZON)
    {
        components comp = static_cast<components>(2);
        std::string compString;
        std::cout << comp << std::endl;
        reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", comp);
        freeReplyObject(reply);
        switch (comp)
        {
        case Camera:
        {
            auto comando = static_cast<camera_type>(rand() % 2);
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", comando);
            freeReplyObject(reply);
            redisFree(redis_conn);
            break;
        }
        case Conditioner:
        {
            auto comando = static_cast<conditioner_type>(rand() % 3);
            int value = 0;
            if (comando == change_temperature)
            {
                value = 20 ;//changeRandomTemperature();
            }
            std::cout<<"temperatura"<<value<<std::endl;
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", comando);
            freeReplyObject(reply);
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", value);
            freeReplyObject(reply);
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
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", comando);
            freeReplyObject(reply);
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", nomeDev);
            freeReplyObject(reply);
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", inizio);
            freeReplyObject(reply);
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", fine);
            freeReplyObject(reply);
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
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", comando);
            freeReplyObject(reply);
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", color);
            freeReplyObject(reply);
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", intensity);
            freeReplyObject(reply);
            break;
        }
        case Sensor:
        {
            auto comando = static_cast<sensor_type>(rand() % 2);
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", comando);
            freeReplyObject(reply);
            break;
        }
        case SensorGarden:
        {
            auto comando = static_cast<sensorGarden_type>(rand() % 4);
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", comando);
            freeReplyObject(reply);
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
        }
        t++;
        sleep(30);
    }

    redisFree(redis_conn);
    return 0;
}
