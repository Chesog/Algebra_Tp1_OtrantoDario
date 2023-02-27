#pragma once
#include "raylib.h"

int screenWidth = 1280;
int screenHeight = 720;

const int maxVectors = 4;
const int maxIntersects = 6;
int currentVector;
int currectIntersection;
int shapeCode[maxVectors];

const float m_pi = 3.14159265358979323846;
float shapeArea = 0;

const char* shapeName;

bool par;

Line vectors[maxVectors];
Intersection intersections[maxIntersects];