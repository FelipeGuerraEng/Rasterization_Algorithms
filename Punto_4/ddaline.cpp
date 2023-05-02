#include "ddaline.h"
#include <cmath>

DDALine::DDALine(int x1, int y1, int x2, int y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {
}

std::vector<std::tuple<int, int>> DDALine::calculatePoints() {
    std::vector<std::tuple<int, int>> points;

    int deltaX = x2 - x1;
    int deltaY = y2 - y1;

    int steps = std::max(std::abs(deltaX), std::abs(deltaY));

    float xIncrement = static_cast<float>(deltaX) / steps;
    float yIncrement = static_cast<float>(deltaY) / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; ++i) {
        points.push_back(std::make_tuple(std::round(x), std::round(y)));
        x += xIncrement;
        y += yIncrement;
    }

    return points;
}
