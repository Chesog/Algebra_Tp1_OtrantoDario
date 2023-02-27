#pragma once
#include "../lib/Include/raylib.h"

struct Line 
{
    Vector2 point1;
    Vector2 point2;
};

struct Intersection {
    Vector2 pos; // La posicion de la interseccion.
    int lines[2]; // Cuales lineas conforman esta interseccion.
};