#include "tsp.h"
#include <algorithm>

const int TSP::INF;

TSP::TSP(const std::vector<std::vector<int>>& matrix)
    : n(matrix.size()), cost(matrix)
{
}

std::pair<int, std::vector<int>> TSP::solve()
{
    std::vector<int> cities(n);
    for (int i = 0; i < n; ++i) {
        cities[i] = i;
    }

    int bestCost = INF;
    std::vector<int> bestPath;

    do {
        int curCost = 0;
        bool valid = true;

        for (int i = 0; i < n - 1; ++i) {
            if (cost[cities[i]][cities[i+1]] >= INF / 2) {
                valid = false;
                break;
            }
            curCost += cost[cities[i]][cities[i+1]];
        }

        if (valid) {
            if (cost[cities[n-1]][cities[0]] < INF / 2) {
                curCost += cost[cities[n-1]][cities[0]];
                if (curCost < bestCost) {
                    bestCost = curCost;
                    bestPath = cities;
                }
            }
        }

    } while (std::next_permutation(cities.begin() + 1, cities.end()));

    if (!bestPath.empty()) {
        bestPath.push_back(bestPath[0]);
    }

    return {bestCost, bestPath};
}
