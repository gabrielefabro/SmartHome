#include <string.h>
#include "light.h"

// Funzione che ritorna la striga di un colore passato come argomento alla funzione
const char* colorToString(light_color color)
{
    switch (color)
    {
        case RED:
            return "RED";
        case BLUE:
            return "BLUE";
        case YELLOW:
            return "YELLOW";
        case PINK:
            return "PINK";
        case ORANGE:
            return "ORANGE";
        case WHITE:
            return "WHITE";
        case PURPLE:
            return "PURPLE";
        default:
            return "UNKNOWN_COLOR";
    }
}
