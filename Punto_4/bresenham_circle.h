#ifndef BRESENHAM_CIRCLE_H
#define BRESENHAM_CIRCLE_H

#include <vector>
#include <tuple>

class BresenhamCircle {
public:
    BresenhamCircle(int centerX, int centerY, int radius);
    std::vector<std::tuple<int, int>> calculatePoints();

private:
    int x0, y0, r;
};

#endif // BRESENHAM_CIRCLE_H
