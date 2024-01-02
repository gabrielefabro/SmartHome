#include <iostream>
#include <string>
#include "RedisManager.hpp"

class Camera
{
private:
    bool recording;
    int id;
    RedisManager &redisManager;

public:
    // Costruttore
    Camera::Camera(int cameraId, RedisManager &redisManager) : recording(false), id(cameraId), redisManager(redisManager) {}

    // Funzione per iniziare la registrazione
    void startRecording()
    {
        if (!recording)
        {
            recording = true;
            std::cout << "Recording started." << std::endl;

            // Registra l'evento di inizio registrazione in Redis
            redisManager.sendCommand("LPUSH camera_events:start_recording " + std::to_string(getId()) + " " + getCurrentTimestamp());
            redisManager.sendCommand("SET camera_checking:" + std::to_string(getId()) + std::to_string(isRecording()));
        }
        else
        {
            std::cout << "Error: Already recording." << std::endl;
        }
    }

    // Funzione per fermare la registrazione
    void stopRecording()
    {
        if (recording)
        {
            recording = false;
            std::cout << "Recording stopped." << std::endl;
            redisManager.sendCommand("LPUSH camera_events:stop_recording " + std::to_string(getId()) + " " + getCurrentTimestamp());
            redisManager.sendCommand("SET camera_checking:" + std::to_string(getId()) + std::to_string(isRecording()));
        }
    }

    // Funzione per controllare lo stato di registrazione
    bool isRecording() const
    {
        return recording;
    }

    int getId(){
        return id;
    }
};