#include "basic_line_rasterization.h"

BasicLineRasterization::BasicLineRasterization(int x1, int y1, int x2, int y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {
}

std::vector<std::tuple<int, int>> BasicLineRasterization::calculatePoints() {
    std::vector<std::tuple<int, int>> points;
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) >= abs(dy)) {
        if (x1 > x2) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        int y = y1;
        int error = 0;
        int halfDx = dx / 2;

        for (int x = x1; x <= x2; x++) {
            points.emplace_back(x, y);
            error += dy;

            if (error > halfDx) {
                y += (y2 > y1 ? 1 : -1);
                error -= dx;
            }
        }
    } else {
        if (y1 > y2) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        int x = x1;
        int error = 0;
        int halfDy = dy / 2;

        for (int y = y1; y <= y2; y++) {
            points.emplace_back(x, y);
            error += dx;

            if (error > halfDy) {
                x += (x2 > x1 ? 1 : -1);
                error -= dy;
            }
        }
    }

    return points;
}
