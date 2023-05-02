#ifndef BASIC_LINE_RASTERIZATION_H
#define BASIC_LINE_RASTERIZATION_H

#include <vector>
#include <tuple>

class BasicLineRasterization {
public:
    BasicLineRasterization(int x1, int y1, int x2, int y2);

    std::vector<std::tuple<int, int>> calculatePoints();

private:
    int x1, y1, x2, y2;
};

#endif // BASIC_LINE_RASTERIZATION_H
