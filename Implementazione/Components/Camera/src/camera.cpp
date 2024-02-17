#include "camera.h"

// Costruttore
Camera::Camera(int id, camera_type state) : id(id), state(state), recording(false) {}

// Metodo per ottenere lo stato corrente della telecamera.
camera_type Camera::getState() const
{
    return state;
}

// Metodo per ottenere l'ID della telecamera.
int Camera::getId() const
{
    return id;
}

// Metodo per impostare lo stato di registrazione della telecamera.
void Camera::setRecording(bool rec)
{
    recording = rec;
}

// Metodo per ottenere lo stato di registrazione della telecamera.
bool Camera::getRecording()
{
    return recording;
}

// Metodo per impostare manualmente lo stato della telecamera.
void Camera::setState(camera_type newState)
{
    state = newState;
}
