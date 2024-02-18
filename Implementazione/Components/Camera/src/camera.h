#ifndef CAMERA_H
#define CAMERA_H

#include <cstdlib>
<<<<<<< HEAD
#include "../../con2db/src/pgsql.h"
=======
#include <iostream>
#include <random>
#include "../../../con2db/src/pgsql.h"
#include <postgresql/libpq-fe.h>
#include <unistd.h>
#include <string.h>
>>>>>>> fb0c8a55095d71fc9ac088a9472b5b9a211a07d2


typedef enum
{
    CameraON,
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

    // Funzione per cambiare stato
    void setState(camera_type newState);

    // Funzione per controllare lo stato di registrazione
    camera_type getState() const;

    // Funzione per ottenere l'ID della fotocamera
    int getId() const;

    // Funzione per impostare lostato di registrazione
    void setRecording(bool rec);

    // Funzione per controllare la registrazione
    bool getRecording();
};

Camera initCamera();
void log2cameradb(Con2DB db1, int id, int pid, camera_type state, bool recording);
void int2stateCamera(char *buf, camera_type x);
<<<<<<< HEAD
void timeFlies(char *buf);
=======
>>>>>>> fb0c8a55095d71fc9ac088a9472b5b9a211a07d2

#endif
