#ifndef CAMERA_H
#define CAMERA_H

#include <cstdlib>
#include <iostream>
#include <random>
#include "pgsql.h"
#include <unistd.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include <chrono>


typedef enum
{
    CameraON,
    CameraOFF
} camera_type;

class Camera
{
private:
    int id;
    camera_type state;
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
void log2cameradb(Con2DB db1, int id, int pid, camera_type state, bool recording, int64_t tempo_trascorso);
void int2stateCamera(char *buf, camera_type x);
void timeFlies(char *buf);

#endif
