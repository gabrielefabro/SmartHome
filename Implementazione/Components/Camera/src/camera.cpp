#include <iostream>
#include <string>
#include <cstdlib>
#include "main.h"
#include "camera.h"

class Camera
{
private:
    camera_type state;
    int id;

public:
    // Costruttore
    Camera(int id, camera_type state) : state(state), id(id) {}
    
    camera_type next(Camera camera)
    {
        camera.state = static_cast<camera_type>((state + rand() % 2) % 3);
        return state;
    }

    // Funzione per controllare lo stato di registrazione
    camera_type getState() const
    {
        return state;
    }

    int getId() const
    {
        return id;
    }
};
