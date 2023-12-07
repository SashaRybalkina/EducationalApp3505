#include "mathengine.h"

MathEngine::MathEngine(CurveFunction curveFunc) : curve(curveFunc)
{
}

void MathEngine::addPlayer(std::string key, std::string values)
{
    xValues[key] = values;
}

double MathEngine::updateAndGetNewY(const std::string &key, double delta, int index)
{
    // Key is present
    if (xValues.find(key) != xValues.end())
    {
        QStringList values = QString::fromStdString(xValues[key]).split(" ");
        if (index < 3)
        {
            updateXValues(values, delta, 0, 1);
        }
        else if (index < 5)
        {
            updateXValues(values, delta, 1, 2);
        }
        else if (index < 7)
        {
            updateXValues(values, delta, 2, values.size());
        }
        else if (index == 7)
        {
            updateXValues(values, delta, 0, 2);
        }
        else if (index == 8)
        {
            updateXValues(values, delta, 0, 1);
            updateXValues(values, delta, 2, values.size());
        }
        else if (index == 9)
        {
            updateXValues(values, delta, 1, values.size());
        }
        else
        {
            updateXValues(values, delta, 0, values.size());
        }
        xValues[key] = values.join(" ").toStdString();
    }
}

void MathEngine::updateXValues(QStringList &values, double delta, int start, int end)
{
    QString str;
    for (int i = start; i < end; i++)
    {
        if (values[i].toDouble() < 0)
        {
            values[i] = str.setNum(values[i].toDouble() + delta / values[i].toDouble());
        }
        else if (values[i].toDouble() > 0)
        {
            values[i] = str.setNum(values[i].toDouble() - delta / values[i].toDouble());
        }
    }
}

void MathEngine::setCurveFunction(CurveFunction newCurveFunc)
{
    curve = newCurveFunc;
}
