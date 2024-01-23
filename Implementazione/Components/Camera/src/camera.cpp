#include "camera.h"

Camera::Camera(int id, camera_type state) : id(id), state(state) {}

camera_type Camera::next()
{
    state = static_cast<camera_type>(rand() % 3);
    return state;
}

camera_type Camera::getState() const
{
    return state;
}

int Camera::getId() const
{
    return id;
}

void Camera::setRecording()
{
    recording = true;
}

bool Camera::getRecording()
{
    return recording;
}

void Camera::setState(camera_type newState)
{
    state = newState;
}