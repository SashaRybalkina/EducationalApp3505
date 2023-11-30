#ifndef MATHENGINE_H
#define MATHENGINE_H
#include <functional>
#include <string>
#include <map>


class MathEngine {
public:
    using CurveFunction = std::function<double(double)>;

    // Constructor that takes a curve function
    MathEngine(CurveFunction curveFunc);

    void addPlayer(std::string key, double x);

    // Method to update and get the new y value based on the key and delta. If delta is positive that means more polarized, negative less polarized
    double updateAndGetNewY(const std::string& key, double delta);

    // Optional: Method to set a new curve function
    void setCurveFunction(CurveFunction newCurveFunc);

private:
    CurveFunction curve;
    std::map<std::string, double> xValues;  // Map to store x values associated with keys (players)
};

#endif // MATHENGINE_H
