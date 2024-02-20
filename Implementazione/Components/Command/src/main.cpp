#include "command.h"

int main()
{

    redisContext *redis_conn = redisConnect("127.0.0.1", 6379);
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
    int t = 0;

    /* init random number generator  */
    srand((unsigned)time(NULL));

    
    while (t < HORIZON)
    {
        components comp = static_cast<components>(rand() & 6);
        std::string compString;
        std::cout << "Componente Generata: " << componentToString(comp) << std::endl;
        redisReply *reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", comp);
        freeReplyObject(reply);
        switch (comp)
        {
        case Camera:
        {
            auto comando = static_cast<camera_type>(rand() % 2);
            char comm[20];
            int2stateCamera(comm, comando);
            std::cout << "Comando Generato: " << comm << std::endl;
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", comando);
            freeReplyObject(reply);
            break;
        }
        case Conditioner:
        {
            auto comando = static_cast<conditioner_type>(rand() % 3);
            char comm[20];
            int2stateConditioner(comm, comando);
            std::cout << "Comando Generato: " << comm << std::endl;
            int value = 0;
            if (comando == change_temperature)
            {
                value = rand() % 40;
            }
            std::cout << "Temperatura desiderata: " << value << std::endl;
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", comando);
            freeReplyObject(reply);
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", value);
            freeReplyObject(reply);
            break;
        }
        case Device:
        {
            auto comando = static_cast<device_type>(rand() % 3);
            char comm[20];
            int2stateDevice(comm, comando);
            std::cout << "Comando Generato: " << comm << std::endl;
            auto nomeDev = static_cast<nome_type>(rand() % 8);
            int inizio = 0;
            int fine = 0;
            if (comando == programmed)
            {
                inizio = rand() % 23;
                fine = rand() % 23;
            }

            std::cout << " nome: " << nomeDev << " inizio: " << inizio << " fine: " << fine << std::endl;
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
            char comm[20];
            int2stateLight(comm, comando);
            light_color color;
            int intensity = 0;
            if (comando == change_color)
            {
                color = static_cast<light_color>(rand() % 7);
            }
            if (comando == change_intensity)
            {
                intensity = rand() % 10;
            }

            std::cout << "Comando Generato: " << comm << std::endl;

            std::cout << "stato: " << comando << " colore: " << color << " intensità: " << intensity << std::endl;

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
            char comm[20];
            int2stateSensor(comm, comando);
            reply = (redisReply *)redisCommand(redis_conn, "PUBLISH userInput_channel %d", comando);
            freeReplyObject(reply);
            break;
        }
        case SensorGarden:
        {
            auto comando = static_cast<sensorGarden_type>(rand() % 2);
            char comm[20];
            int2stateSensorGarden(comm, comando);
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
        }
        else
        {
            std::cout << "Publisher: Risposta pubblicata su Redis." << std::endl;
        }
        t++;
        sleep(10);
    }

    redisFree(redis_conn);
    return 0;
}
