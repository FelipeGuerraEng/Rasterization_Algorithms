#ifndef DDALINE_H
#define DDALINE_H

#include <vector>
#include <tuple>

class DDALine {
public:
    DDALine(int x1, int y1, int x2, int y2);
    std::vector<std::tuple<int, int>> calculatePoints();

private:
    int x1, y1, x2, y2;
};

#endif // DDALINE_H
