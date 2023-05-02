#include "bresenham_circle.h"

BresenhamCircle::BresenhamCircle(int centerX, int centerY, int radius) : x0(centerX), y0(centerY), r(radius) {}

std::vector<std::tuple<int, int>> BresenhamCircle::calculatePoints() {
    std::vector<std::tuple<int, int>> points;

    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (y >= x) {
        points.push_back(std::make_tuple(x0 + x, y0 + y));
        points.push_back(std::make_tuple(x0 - x, y0 + y));
        points.push_back(std::make_tuple(x0 + x, y0 - y));
        points.push_back(std::make_tuple(x0 - x, y0 - y));
        points.push_back(std::make_tuple(x0 + y, y0 + x));
        points.push_back(std::make_tuple(x0 - y, y0 + x));
        points.push_back(std::make_tuple(x0 + y, y0 - x));
        points.push_back(std::make_tuple(x0 - y, y0 - x));

        x++;

        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }

    return points;
}
