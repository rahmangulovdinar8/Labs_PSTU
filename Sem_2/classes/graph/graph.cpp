#include "graph.h"
#include <queue>
#include <algorithm>

const int Graph::INF;

Graph::Graph() {}

void Graph::rebuildMatrix() {
    int n = vertices.size();
    adjMatrix.assign(n, std::vector<int>(n, INF));
    for (int i = 0; i < n; ++i) adjMatrix[i][i] = 0;
}

bool Graph::addVertex(const std::string &name) {
    if (vertexIndex.count(name)) return false;
    vertexIndex[name] = vertices.size();
    vertices.push_back(name);
    rebuildMatrix();
    return true;
}

bool Graph::removeVertex(const std::string &name) {
    if (!vertexIndex.count(name)) return false;
    int idx = vertexIndex[name];
    vertexIndex.erase(name);
    vertices.erase(vertices.begin() + idx);
    for (auto &pair : vertexIndex) {
        if (pair.second > idx) pair.second--;
    }
    rebuildMatrix();
    return true;
}

bool Graph::addEdge(const std::string &from, const std::string &to, int weight) {
    if (!vertexIndex.count(from) || !vertexIndex.count(to)) return false;
    int i = vertexIndex[from];
    int j = vertexIndex[to];
    if (adjMatrix[i][j] != INF && adjMatrix[i][j] != 0) return false;
    adjMatrix[i][j] = weight;
    // НЕ добавляем обратное ребро!
    return true;
}

bool Graph::removeEdge(const std::string &from, const std::string &to) {
    if (!vertexIndex.count(from) || !vertexIndex.count(to)) return false;
    int i = vertexIndex[from];
    int j = vertexIndex[to];
    if (adjMatrix[i][j] == INF) return false;
    adjMatrix[i][j] = INF;
    return true;
}

bool Graph::setWeight(const std::string &from, const std::string &to, int weight) {
    if (!vertexIndex.count(from) || !vertexIndex.count(to)) return false;
    int i = vertexIndex[from];
    int j = vertexIndex[to];
    if (adjMatrix[i][j] == INF) return false;
    adjMatrix[i][j] = weight;
    return true;
}

void Graph::clear() {
    vertices.clear();
    vertexIndex.clear();
    adjMatrix.clear();
}

std::vector<std::string> Graph::bfs(const std::string &start) {
    if (!vertexIndex.count(start)) return {};
    std::vector<bool> visited(vertices.size(), false);
    std::vector<std::string> order;
    std::queue<int> q;
    int startIdx = vertexIndex[start];
    visited[startIdx] = true;
    q.push(startIdx);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(vertices[u]);
        for (int v = 0; v < (int)vertices.size(); ++v) {
            if (adjMatrix[u][v] != INF && adjMatrix[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return order;
}

void Graph::dfsRecursive(int idx, std::vector<bool> &visited, std::vector<std::string> &order) {
    visited[idx] = true;
    order.push_back(vertices[idx]);
    for (int v = 0; v < (int)vertices.size(); ++v) {
        if (adjMatrix[idx][v] != INF && adjMatrix[idx][v] != 0 && !visited[v]) {
            dfsRecursive(v, visited, order);
        }
    }
}

std::vector<std::string> Graph::dfs(const std::string &start) {
    if (!vertexIndex.count(start)) return {};
    std::vector<bool> visited(vertices.size(), false);
    std::vector<std::string> order;
    dfsRecursive(vertexIndex[start], visited, order);
    return order;
}

std::unordered_map<std::string, int> Graph::dijkstra(const std::string &start) {
    std::unordered_map<std::string, int> result;
    if (!vertexIndex.count(start)) return result;
    int n = vertices.size();
    std::vector<int> dist(n, INF);
    std::vector<bool> visited(n, false);
    int startIdx = vertexIndex[start];
    dist[startIdx] = 0;
    for (int count = 0; count < n - 1; ++count) {
        int u = -1;
        int minDist = INF;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = true;
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] != INF && !visited[v] && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        result[vertices[i]] = dist[i];
    }
    return result;
}

std::vector<std::vector<int>> Graph::floyd() {
    int n = vertices.size();
    std::vector<std::vector<int>> dist = adjMatrix;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}

const std::vector<std::string>& Graph::getVertices() const {
    return vertices;
}

int Graph::getWeight(const std::string &from, const std::string &to) const {
    if (!vertexIndex.count(from) || !vertexIndex.count(to)) return INF;
    return adjMatrix.at(vertexIndex.at(from)).at(vertexIndex.at(to));
}
