#include <iostream>
#include "structs.h"
#include "variables.h"
#include "declarations.h"

using namespace std;

void main()
{
	InitProgram();
	UpdateProgram();
	CloseWindow();
}

void InitProgram()
{
	InitWindow(screenWidth, screenHeight, "Algebra_TP1_OtrantoDario");

	currentVector = 0;
	par = true;
	currectIntersection = 0;
	InitVectors();
}

void UpdateProgram()
{
	SetExitKey(NULL);

	do
	{
		Input();
		Draw();
	} while (!WindowShouldClose());
}

void Input()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && currentVector < maxVectors)
	{
		if (par)
		{
			vectors[currentVector].point1 = GetMousePosition();
			cout << "[" << currentVector + 1 << "] Punto 1: (" << vectors[currentVector].point1.x << ";" << vectors[currentVector].point1.y << ")" << endl;
			par = !par;
		}
		else {
			vectors[currentVector].point2 = GetMousePosition();
			cout << "[" << currentVector + 1 << "] Punto 2: (" << vectors[currentVector].point2.x << ";" << vectors[currentVector].point2.y << ")" << endl;
			par = !par;
			currentVector++;
		}
		if (currentVector == maxVectors)
		{
			FindIntersections();
			Manage();
		}
	}

	if (IsKeyPressed(KEY_ESCAPE))
	{
		shapeArea = 0;
		currentVector = 0;
		par = true;
		currectIntersection = 0;
		ResetShapeCode();
		InitVectors();
		cout << "Vectores reiniciados..." << endl;
	}
}

void Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	for (int i = 0; i < maxVectors; i++)
	{
		if (i < currentVector)
		{
			DrawLine(vectors[i].point1.x, vectors[i].point1.y, vectors[i].point2.x, vectors[i].point2.y, GREEN);
		}
		if (!par && currentVector < maxVectors)
		{
			DrawLine(vectors[currentVector].point1.x, vectors[currentVector].point1.y, GetMousePosition().x, GetMousePosition().y, GREEN);
		}
	}
	for (int i = 0; i < currectIntersection; i++)
	{
		DrawCircle(intersections[i].pos.x, intersections[i].pos.y, 5.0f, BLUE);
		DrawCenteredText(TextFormat("%i", i), intersections[i].pos, 10.0f, WHITE);
	}

	if (shapeArea > 0)
	{
		DrawText(shapeName, GetScreenWidth() * .02, GetScreenHeight() * .05, GetScreenHeight() * .08, GREEN);
		DrawText(TextFormat("Area: %f", shapeArea), GetScreenWidth() * .02, GetScreenHeight() * .15, GetScreenHeight() * .04, RAYWHITE);
	}

	EndDrawing();
}

float GetVectorsAngle(Vector2 v1, Vector2 v2, Vector2 center)
{

http://phrogz.net/angle-between-three-points

	float a = powf(center.x - v1.x, 2) + powf(center.y - v1.y, 2);
	float b = powf(center.x - v2.x, 2) + powf(center.y - v2.y, 2);
	float c = powf(v2.x - v1.x, 2) + powf(v2.y - v1.y, 2);
	return acosf((a + b - c) / sqrtf(4 * a * b));
}

float GetVectorsDistance(Vector2 v1, Vector2 v2)
{
https://en.wikipedia.org/wiki/Euclidean_distance

	float distX = v1.x - v2.x;
	float distY = v1.y - v2.y;
	return sqrt((distX * distX) + (distY * distY));
}

void InitVectors()
{
	for (int i = 0; i < maxVectors; i++)
	{
		vectors[i].point1 = { 0, 0 };
		vectors[i].point2 = { 0, 0 };
	}
}

float DegreesToRadians(float deg)
{
	return (deg * (PI/ 180.0));
}

float RadiansToDegrees(float rad)
{
	return (rad * (180.0 / PI));
}

void DrawCenteredText(const char* text, Vector2 pos, int fontSize, Color color)
{
	int textWide = MeasureText(text, fontSize);
	DrawText(text, (pos.x) - (textWide * .5), (pos.y) - (fontSize * .5), fontSize, color);
}

bool IsInArray(int arr[], int size, int value)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == value)
		{
			return true;
		}
	}
	return false;
}

void BubbleSort(int arr[], int size)
{
	int aux;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j + 1 < size - i; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				aux = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = aux;
			}
		}
	}
}

void CopyArray(int oldArr[], int newArr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		newArr[i] = oldArr[i];
	}
}

void PrintArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}

void AddIntersection(Vector2 intersection, int line1, int line2)
{
	intersections[currectIntersection].pos = intersection;
	intersections[currectIntersection].lines[0] = line1;
	intersections[currectIntersection].lines[1] = line2;
	currectIntersection++;
}

bool IsIntersectionRepeated(Vector2 intersection)
{
	if (currectIntersection > 0)
	{
		for (int i = 0; i < currectIntersection; i++)
		{
			if (intersections[i].pos.x == intersection.x && intersections[i].pos.y == intersection.y)
			{
				return true;
			}
		}
	}
	else {
		return false;
	}
	return false;
}

bool IsIntersectionInvalid(Line line, Vector2 intersection)
{
	return (intersection.x < line.point1.x&& intersection.x < line.point2.x&& intersection.x
		|| intersection.x > line.point1.x&& intersection.x > line.point2.x && intersection.x
		|| intersection.y < line.point1.y&& intersection.y < line.point2.y&& intersection.y
		|| intersection.y > line.point1.y&& intersection.y > line.point2.y && intersection.y);
}

Vector2 LineLineIntersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	Vector2 intersection;

	intersection.x =
		(((x1 * y2 - y1 * x2) * (x3 - x4)) - ((x1 - x2) * (x3 * y4 - y3 * x4))) /
		(((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)));

	intersection.y =
		(((x1 * y2 - y1 * x2) * (y3 - y4)) - ((y1 - y2) * (x3 * y4 - y3 * x4))) /
		(((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)));

	return intersection;
}

void FindIntersections()
{
	for (int i = 0; i < maxVectors; i++)
	{
		for (int j = 0; j < maxVectors; j++)
		{
			Vector2 intersect = LineLineIntersection(vectors[i].point1.x, vectors[i].point1.y, vectors[i].point2.x, vectors[i].point2.y, vectors[j].point1.x, vectors[j].point1.y, vectors[j].point2.x, vectors[j].point2.y);
			if (!isnan(intersect.x) && !IsIntersectionInvalid(vectors[i], intersect) && !IsIntersectionInvalid(vectors[j], intersect) && !IsIntersectionRepeated(intersect))
			{
				AddIntersection(intersect, i, j);

				shapeCode[i]++;
				shapeCode[j]++;
				cout << "intersection found: (" << intersect.x << ";" << intersect.y << ") Lines: [" << i << " & " << j << "]\n";
			}
		}
	}
}

float CalculateTriangleArea(float a, float b, float c)
{
	https://en.wikipedia.org/wiki/Heron%27s_formula

	float s = ((a + b + c) / 2);
	return sqrt(s * ((s - a) * (s - b) * (s - c)));
}

void FindQuadrilateral(int intersects[])
{
	int main = 0;
	int parents[2] = { 0, 0 };
	int currentParent = 0;

	for (int i = 1; i < currectIntersection; i++)
	{
		if (intersections[i].lines[0] == intersections[main].lines[0] ||
			intersections[i].lines[0] == intersections[main].lines[1] ||
			intersections[i].lines[1] == intersections[main].lines[0] ||
			intersections[i].lines[1] == intersections[main].lines[1])
		{
			parents[currentParent] = i;
			currentParent++;
		}
	}
	int opposite = 0;
	for (int i = 0; i < currectIntersection; i++)
	{
		if (i != main && i != parents[0] && i != parents[1])
			opposite = i;
	}
	
	float mainAng = RadiansToDegrees(GetVectorsAngle(intersections[parents[0]].pos, intersections[parents[1]].pos, intersections[main].pos));
	float parent1Ang = RadiansToDegrees(GetVectorsAngle(intersections[opposite].pos, intersections[main].pos, intersections[parents[0]].pos));
	float parent2Ang = RadiansToDegrees(GetVectorsAngle(intersections[opposite].pos, intersections[main].pos, intersections[parents[1]].pos));
	float oppositeAng = RadiansToDegrees(GetVectorsAngle(intersections[parents[0]].pos, intersections[parents[1]].pos, intersections[opposite].pos));
	
	if ((mainAng + parent1Ang + parent2Ang + oppositeAng) > 358)
	{
		cout << "It's a Convex Quadrilateral.\n";
		shapeName = "Convex Quadrilateral";
		intersects[0] = main;
		intersects[1] = opposite;
	}
	else 
	{
		
		cout << "It's a Concave Quadrilateral.\n";
		shapeName = "Concave Quadrilateral";
		if (mainAng + oppositeAng > parent1Ang + parent2Ang)
		{
			cout << "Slicing triangles from main to opposite.\n";
			intersects[0] = main;
			intersects[1] = opposite;
		}
		else 
		{
			cout << "Slicing triangles from parent A to parent B.\n";
			intersects[0] = parents[0];
			intersects[1] = parents[1];
		}
	}
}

void CalculateQuadrilateral() {
	
	int mainIntersects[2];
	int parentIntersects[2] = { 0, 0 }; 
	int parentCount = 0;
	FindQuadrilateral(mainIntersects);
	for (int i = 0; i < currectIntersection; i++)
	{
		if (i != mainIntersects[0] && i != mainIntersects[1])
		{
			parentIntersects[parentCount] = i;
			parentCount++;
		}
	}

	float a = GetVectorsDistance(intersections[mainIntersects[0]].pos, intersections[mainIntersects[1]].pos);

	float b = GetVectorsDistance(intersections[mainIntersects[0]].pos, intersections[parentIntersects[0]].pos);
	float c = GetVectorsDistance(intersections[mainIntersects[1]].pos, intersections[parentIntersects[0]].pos);
	float triangleA = CalculateTriangleArea(a, b, c);
	cout << "a: " << b <<
		"\nb: " << c << "\n";

	b = GetVectorsDistance(intersections[mainIntersects[0]].pos, intersections[parentIntersects[1]].pos);
	c = GetVectorsDistance(intersections[mainIntersects[1]].pos, intersections[parentIntersects[1]].pos);
	float triangleB = CalculateTriangleArea(a, b, c);
	cout << "c: " << b <<
		"\nd: " << c << "\n";

	cout << "The area of the quadrilateral is: " << (triangleA + triangleB) << ".\n";
	shapeArea = (triangleA + triangleB);
}

void FindTriangle(int intersects[]) 
{
	int cursor = 0;
	for (int i = 0; i < currectIntersection; i++)
	{
		if (shapeCode[intersections[i].lines[0]] > 1 && shapeCode[intersections[i].lines[1]] > 1)
		{
			intersects[cursor] = i;
			cursor++;
		}
	}
}

void CalculateTriangle()
{
	int intersects[3];
	FindTriangle(intersects);

	float a = GetVectorsDistance(intersections[intersects[0]].pos, intersections[intersects[1]].pos);
	cout << "a: " << a << "\n";
	float b = GetVectorsDistance(intersections[intersects[1]].pos, intersections[intersects[2]].pos);
	cout << "b: " << b << "\n";
	float c = GetVectorsDistance(intersections[intersects[2]].pos, intersections[intersects[0]].pos);
	cout << "c: " << c << "\n";
	float s = ((a + b + c) / 2);
	float area = sqrt(s * ((s - a) * (s - b) * (s - c)));
	cout << "The area of the triangle is: " << area << "\n";
	shapeName = "Triangle";
	shapeArea = area;
}

bool IsQuadrilateral(int code[])
{
	int code1[] = { 2, 2, 2, 2 };
	return (CompareCodes(code, code1));
}

bool IsTriangle(int code[])
{
	int code1[] = { 2, 2, 2, 0 };
	int code2[] = { 3, 2, 2, 1 };
	return (CompareCodes(code, code1) || CompareCodes(code, code2));
}

bool CompareCodes(int c1[], int c2[])
{
	for (int i = 0; i < maxVectors; i++)
	{
		if (c1[i] != c2[i])
			return false;
	}
	return true;
}

void ResetShapeCode() {
	for (int i = 0; i < maxVectors; i++) {
		shapeCode[i] = 0;
	}
}

void Manage()
{
	int arrangedCode[maxVectors];
	CopyArray(shapeCode, arrangedCode, maxVectors);
	BubbleSort(arrangedCode, maxVectors);
	cout << "Shape code: ";
	PrintArray(arrangedCode, maxVectors);
	cout << "\n";

	if (IsTriangle(arrangedCode))
	{
		cout << "The shape is a triangle!\n";
		CalculateTriangle();
	}
	if (IsQuadrilateral(arrangedCode)) {
		cout << "The shape is a quadrilateral!\n";
		CalculateQuadrilateral();
	}
}