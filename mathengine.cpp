#include "mathengine.h"

MathEngine::MathEngine(CurveFunction curveFunc) : curve(curveFunc)
{
}

void MathEngine::addPlayer(std::string key, double x)
{
    xValues[key] = x;
}

double MathEngine::updateAndGetNewY(const std::string &key, double delta)
{
    // Key is present
    if (xValues.find(key) != xValues.end())
    {
        if (xValues[key] < 0)
        {
            xValues[key] += delta/xValues[key];
        }
        else if (xValues[key] > 0)
        {
            xValues[key] -= delta/xValues[key];
        }
    }
}

void MathEngine::setCurveFunction(CurveFunction newCurveFunc)
{
    curve = newCurveFunc;
}
