#ifndef MIDPOINTCIRCLE_H
#define MIDPOINTCIRCLE_H

#include <vector>
#include <tuple>

class MidpointCircle {
public:
    MidpointCircle(int centerX, int centerY, int radius);

    std::vector<std::tuple<int, int>> calculatePoints() const;

private:
    int centerX, centerY, radius;

    void plotPoints(int x, int y, std::vector<std::tuple<int, int>>& points) const;
};

#endif // MIDPOINTCIRCLE_H
