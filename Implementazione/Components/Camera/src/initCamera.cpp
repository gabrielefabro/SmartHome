#include "camera.h"
#include "../../../main/global.h"
#include <cstdlib>

Camera initCamera()
{
    Camera camera(rand(), static_cast<camera_type>(rand() % 3));
    return camera;
}