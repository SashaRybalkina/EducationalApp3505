#include "mathengine.h"

MathEngine::MathEngine(CurveFunction curveFunc) : curve(curveFunc)
{
}

void MathEngine::addPlayer(std::string key, std::array<double, 3> values)
{
    xValues[key] = values;
}

std::array<double, 3> MathEngine::updateAndGetNewY(const std::string &key, double delta, int index)
{
    // Key is present
    std::array<double, 3> &values = xValues[key];
    if (xValues.find(key) != xValues.end())
    {
        // Changes all Kopta vs VCJim values
        if (index < 3)
        {
            updateXValues(values, delta, 0, 1);
        }
        // Changes all Apple vs Android values
        else if (index < 5)
        {
            updateXValues(values, delta, 1, 2);
        }
        // Changes all U of U vs BYU
        else if (index < 7)
        {
            updateXValues(values, delta, 2, values.size());
        }
        // Changes all Kopta vs VCJim and Apple vs Android values
        else if (index == 7)
        {
            updateXValues(values, delta, 0, 2);
        }
        // Changes all Kopta vs VCJim and U of U vs BYU values
        else if (index == 8)
        {
            updateXValues(values, delta, 0, 1);
            updateXValues(values, delta, 2, values.size());
        }
        // Changes all Apple vs Android and U of U vs BYU values
        else if (index == 9)
        {
            updateXValues(values, delta, 1, values.size());
        }
        // Changes all values
        else
        {
            updateXValues(values, delta, 0, values.size());
        }
        std::array<double, 3> yValues;
        yValues[0] = curve(xValues[key][0]);
        yValues[1] = curve(xValues[key][1]);
        yValues[2] = curve(xValues[key][2]);
        return yValues;
    }
}

void MathEngine::updateXValues(std::array<double, 3> &values, double delta, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        double yValue = abs(curve(values[i]));
        if (yValue == 0)
        {
            yValue = 1;
        }
        if (values[i] < 0)
        {
            values[i] = values[i] + delta/yValue;
        }
        else if (values[i] > 0)
        {
            values[i] = values[i] - delta/yValue;
        }
    }
}

void MathEngine::setCurveFunction(CurveFunction newCurveFunc)
{
    curve = newCurveFunc;
}
