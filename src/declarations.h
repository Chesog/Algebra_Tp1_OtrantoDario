#pragma once
#include "structs.h"

bool IsTriangle(int code[]);
void FindTriangle(int intersects[]);
void CalculateTriangle();
float CalculateTriangleArea(float a, float b, float c);

bool IsQuadrilateral(int code[]);
void FindQuadrilateral(int intersects[]);
void CalculateQuadrilateral();

bool CompareCodes(int c1[], int c2[]);
void ResetShapeCode();
void Manage();

void FindIntersections();
void AddIntersection(Vector2 intersection, int l1, int l2);
bool IsIntersectionRepeated(Vector2 intersection);
bool IsIntersectionInvalid(Line l, Vector2 intersection);
Vector2 LineLineIntersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

void Input();
void Draw();
void UpdateProgram();
void InitProgram();

float GetVectorsAngle(Vector2 v1, Vector2 v2, Vector2 c);
float GetVectorsDistance(Vector2 v1, Vector2 v2);
void InitVectors();


float DegreesToRadians(float deg);
float RadiansToDegrees(float rad);
void DrawCenteredText(const char* text, Vector2 pos, int fontSize, Color color);
bool IsInArray(int arr[], int size, int value);
void CopyArray(int oldArr[], int newArr[], int size);
void BubbleSort(int arr[], int size);
void PrintArray(int arr[], int size);