#include "camera.h"
#include "globalCa.h"
#include <cstdlib>

Camera initCamera()
{
    Camera camera(rand(), static_cast<camera_type>(rand() % 3));
    return camera;
}