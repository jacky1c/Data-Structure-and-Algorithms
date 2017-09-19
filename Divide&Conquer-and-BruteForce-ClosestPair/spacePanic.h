#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <unistd.h>

using namespace std;

const int SPACE_WIDTH = 100;
const int SPACE_HEIGHT = 40;
const int MAX_BOMBS_PER_DROP = 10;
const int SLEEP_DELAY = 75000;
const int HIGH_VALUE = 9999;
struct Point
{
    int x;
    int y;
};

struct ClosePair
{
    float dMin;
    Point p1;
    Point p2;
};

// functions in spacePanic
void Initialize (char space [][SPACE_WIDTH + 1]);
void PrintUpperBorder ();
void MoveSpaceShips (char space [][SPACE_WIDTH + 1], int& bombsDestroyed);
void MoveBombs (char space [][SPACE_WIDTH + 1], int& spaceShipsDestroyed);
void ReleaseSpaceShip (char space [][SPACE_WIDTH + 1], int iterations, int& bombsDestroyed);
void ReleaseBombs (char space [][SPACE_WIDTH + 1], int iterations, int& spaceShipsDestroyed);
bool ContinueAttack (char space [][SPACE_WIDTH + 1], int& pointCoint, bool quiteMode);
void PrintLowerBorder ();
void DetectCollisions (int iterations, int pointCount, char space [][SPACE_WIDTH + 1]);
void Pause (int bombsDestroyed, int spaceShipsDestroyed, int& iterations, bool automaticMode, bool quiteMode);
void PrintStats (int bombsDestroyed, int spaceShipsDestroyed, time_t start, time_t end);

// functions used for Divide and Conquer Closest Pair
ClosePair* ClosestPair(Point pX[], int startIndex, int endIndex, int& numOfClosePair);
ClosePair* BruteForce (Point pX[], int startIndex, int endIndex, int& numOfClosePair);
ClosePair* Min(ClosePair clPL, ClosePair clPR, int& numOfClosePair);
ClosePair* CheckBoundaryPoints(Point pX[], int startIndex, int endIndex, int& numOfClosePair);
float Distance(Point a, Point b);
ClosePair* Combine(ClosePair* clPL, int numOfClosePairL, ClosePair* clPR, int numOfClosePairR, int& numOfClosePair);
// functions used for Brute Force Closest Pair
ClosePair* BF_ClosestPair(Point pX[], int startIndex, int endIndex, int& numOfClosePairs);
