#ifndef CAMERA_H
#define CAMERA_H

#include <cstdlib>

typedef enum
{
    CameraON,
    WAITING,
    CameraOFF
} camera_type;

class Camera
{
private:
    camera_type state;
    int id;
    bool recording;

public:
    // Costruttore
    Camera(int id, camera_type state);

    // Funzione per ottenere lo stato successivo
    camera_type next();

    // Funzione per controllare lo stato di registrazione
    camera_type getState() const;

    // Funzione per ottenere l'ID della fotocamera
    int getId() const;

    void setRecording();

    bool getRecording();

    void setState(camera_type newState);
};

#endif // CAMERA_H
