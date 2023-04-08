#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>

#include "Boid.hpp"

using namespace std;

float randomFloat(float a, float b)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

vector<float> random2DVector(float lo, float hi)
{
    // returns a random 2D vector w/ values from lo to hi
    return {randomFloat(lo, hi), randomFloat(lo, hi)};
}

void limit(float& variable, float value)
{
    if(variable > value)
        variable = value;

    if(variable < -value)
        variable = -value;
}

void setMagnitude(vector<float>& v, float newMagnitude)
{
    float oldMagnitude = sqrt(v[0] * v[0] + v[1] * v[1]);

    if(oldMagnitude != 0.0f)
    {
        float multiplier = newMagnitude / oldMagnitude;

        v[0] *= multiplier;
        v[1] *= multiplier;
    }
}

#endif  // FUNCTIONS_H
