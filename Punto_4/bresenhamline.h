#ifndef BRESENHAMLINE_H
#define BRESENHAMLINE_H

#include <vector>
#include <tuple>

class BresenhamLine {
public:
    BresenhamLine(int x1, int y1, int x2, int y2);

    std::vector<std::tuple<int, int>> calculatePoints() const;

private:
    int x1, y1, x2, y2;
};

#endif // BRESENHAMLINE_H
