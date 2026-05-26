#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

class Graph {
public:
    static const int INF = 1000000000;

    Graph();
    bool addVertex(const std::string &name);
    bool removeVertex(const std::string &name);
    bool addEdge(const std::string &from, const std::string &to, int weight);
    bool removeEdge(const std::string &from, const std::string &to);
    bool setWeight(const std::string &from, const std::string &to, int weight);
    void clear();

    std::vector<std::string> bfs(const std::string &start);
    std::vector<std::string> dfs(const std::string &start);
    std::unordered_map<std::string, int> dijkstra(const std::string &start);
    std::vector<std::vector<int>> floyd();

    const std::vector<std::string>& getVertices() const;
    int getWeight(const std::string &from, const std::string &to) const;

private:
    std::vector<std::string> vertices;
    std::map<std::string, int> vertexIndex;
    std::vector<std::vector<int>> adjMatrix;

    void rebuildMatrix();
    void dfsRecursive(int idx, std::vector<bool> &visited, std::vector<std::string> &order);
};

#endif
