#ifndef MATHENGINE_H
#define MATHENGINE_H
#include <functional>
#include <string>
#include <QHash>
#include <map>

/**
 * @brief The MathEngine class handles the impact of interactions on player characteristics
 */
class MathEngine
{
public:
    using CurveFunction = std::function<double(double)>;

    /**
     * @brief MathEngine - stores current x valeus for keys and updates them and returns 'y' values (scores)
     * @param curveFunc - the function to use to map input x to score y
     */
    MathEngine(CurveFunction curveFunc);

    /**
     * @brief addPlayer - stores x values for key
     * @param key - of player
     * @param values - x values for player
     */
    void addPlayer(std::string key, std::array<double, 3> values);

    /**
     * @brief updateAndGetNewY - update and get the new y value based on the key and delta
     * @param key - ID for player
     * @param delta - if delta is positive that means more polarized, negative less polarized. Exp: if pass in 2 and the player has x of -2 there x will be -4
     * @param index - used for only updating specific player stats
     * @return y score
     */
    std::array<double, 3> updateAndGetNewY(const std::string &key, double delta, int index);

    /**
     * @brief setCurveFunction - set a new curve func
     * @param newCurveFunc - new func
     */
    void setCurveFunction(CurveFunction newCurveFunc);

private:
    CurveFunction curve;
    // 0 kopta_jim 1 apple_android 2 uofu_byu
    std::map<std::string, std::array<double, 3>> xValues; // Map to store x values associated with keys (players)
    void updateXValues(std::array<double, 3> &values, double delta, int start, int end);
};

#endif // MATHENGINE_H
