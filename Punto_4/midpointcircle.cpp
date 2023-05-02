#include "midpointcircle.h"

MidpointCircle::MidpointCircle(int centerX, int centerY, int radius)
    : centerX(centerX), centerY(centerY), radius(radius) {
}

std::vector<std::tuple<int, int>> MidpointCircle::calculatePoints() const {
    std::vector<std::tuple<int, int>> points;

    int x = 0;
    int y = radius;
    int p = 1 - radius;

    plotPoints(x, y, points);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        plotPoints(x, y, points);
    }

    return points;
}

void MidpointCircle::plotPoints(int x, int y, std::vector<std::tuple<int, int>>& points) const {
    points.emplace_back(centerX + x, centerY + y);
    points.emplace_back(centerX - x, centerY + y);
    points.emplace_back(centerX + x, centerY - y);
    points.emplace_back(centerX - x, centerY - y);
    points.emplace_back(centerX + y, centerY + x);
    points.emplace_back(centerX - y, centerY + x);
    points.emplace_back(centerX + y, centerY - x);
    points.emplace_back(centerX - y, centerY - x);
}
