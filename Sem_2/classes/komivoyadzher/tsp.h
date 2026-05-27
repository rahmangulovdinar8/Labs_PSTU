#ifndef TSP_H
#define TSP_H

#include <vector>

class TSP {
public:
    static const int INF = 1000000000;

    TSP(const std::vector<std::vector<int>>& matrix);
    std::pair<int, std::vector<int>> solve();

private:
    int n;
    std::vector<std::vector<int>> cost;
};

#endif
