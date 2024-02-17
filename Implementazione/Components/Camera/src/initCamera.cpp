#include "camera.h"
#include <cstdlib>

// Funzione che inizializza l'oggetto camera
Camera initCamera()
{
    Camera camera(rand(), static_cast<camera_type>(rand() % 3));
    return camera;
}