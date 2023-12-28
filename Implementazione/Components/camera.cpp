#include <iostream>
#include <string>

class Camera
{
private:
    bool recording;
    int id;

public:
    // Costruttore
    Camera(int cameraId) : recording(false), id(cameraId) {}

    // Funzione per iniziare la registrazione
    std::string startRecording()
    {
        if (!recording)
        {
            recording = true;
            std::cout << "Recording started." << std::endl;
        }
        else
        {
            std::cout << "Error: Already recording." << std::endl;
            return "";
        }
    }

    // Funzione per fermare la registrazione
    void stopRecording()
    {
        if (recording)
        {
            recording = false;
            std::cout << "Recording stopped." << std::endl;
        }
        else
        {
            std::cout << "Error: Not currently recording." << std::endl;
        }
    }

    // Funzione per controllare lo stato di registrazione
    bool isRecording() const
    {
        return recording;
    }
};
