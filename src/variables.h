#pragma once
#include "raylib.h"

int screenWidth = 1280;
int screenHeight = 720;

const int maxVectors = 4;
const int maxIntersects = 6;
int currentVector;
int currectIntersection;
int shapeCode[maxVectors];

float shapeArea = 0;

const char* shapeName;

bool par;

Line vectors[maxVectors];
Intersection intersections[maxIntersects];