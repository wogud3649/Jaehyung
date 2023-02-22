#include "framework.h"
#include "MathUtility.h"

int MathUtility::RandomInt(int min, int max)
{
    int result = rand() % (max - min) + min;
    return result;
}

float MathUtility::RandomFloat(float min, float max)
{
    float zeroToOne = (float)rand() / (float)RAND_MAX;

    return (max - min) * zeroToOne + min;
}
