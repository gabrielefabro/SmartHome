#include <string.h>
#include "../../../main/src/main.h"

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