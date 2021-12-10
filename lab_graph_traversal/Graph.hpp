#pragma once

#include <map>
#include <vector>

class Graph {
public:
    using vertex = int;

    virtual void addEdge(const vertex &edgeBegin, const vertex &edgeEnd) {
        graph[edgeBegin].push_back(edgeEnd);
        graph[edgeEnd];
    }

    virtual const std::vector<vertex> &getNeighbours(const vertex &v) {
        return graph.at(v);
    }

    [[nodiscard]] virtual const size_t getSize() const {
        return graph.size();
    }

private:
    std::map<vertex, std::vector<vertex>> graph{};
};
