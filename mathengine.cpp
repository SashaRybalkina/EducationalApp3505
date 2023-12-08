#include "mathengine.h"

MathEngine::MathEngine(CurveFunction curveFunc) : curve(curveFunc)
{
}

void MathEngine::addPlayer(std::string key, std::vector<double> values)
{
    xValues[key] = values;
}

std::vector<double> MathEngine::updateAndGetNewY(const std::string &key, double delta, int index)
{
    // Key is present
    std::vector<double> &values = xValues[key];
    if (xValues.find(key) != xValues.end())
    {
        //Changes all Kopta vs VCJim values
        if (index < 3)
        {
            updateXValues(values, delta, 0, 1);
        }
        //Changes all Apple vs Android values
        else if (index < 5)
        {
            updateXValues(values, delta, 1, 2);
        }
        //Changes all U of U vs BYU
        else if (index < 7)
        {
            updateXValues(values, delta, 2, values.size());
        }
        //Changes all Kopta vs VCJim and Apple vs Android values
        else if (index == 7)
        {
            updateXValues(values, delta, 0, 2);
        }
        //Changes all Kopta vs VCJim and U of U vs BYU values
        else if (index == 8)
        {
            updateXValues(values, delta, 0, 1);
            updateXValues(values, delta, 2, values.size());
        }
        //Changes all Apple vs Android and U of U vs BYU values
        else if (index == 9)
        {
            updateXValues(values, delta, 1, values.size());
        }
        //Changes all values
        else
        {
            updateXValues(values, delta, 0, values.size());
        }
        //xValues[key] = values;
        std::vector<double> yValues;
        yValues.push_back(curve(xValues[key][0]));
        yValues.push_back(curve(xValues[key][1]));
        yValues.push_back(curve(xValues[key][2]));
        return yValues;
    }
}

void MathEngine::updateXValues(std::vector<double> &values, double delta, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        if (values[i] < 0)
        {
            values[i] = values[i] + delta;
        }
        else if (values[i] > 0)
        {
            values[i] = values[i]- delta;
        }
    }
}

void MathEngine::setCurveFunction(CurveFunction newCurveFunc)
{
    curve = newCurveFunc;
}
