#pragma once

#include <map>
#include <vector>


class Graph final {
public:
    Graph() = default;

    using vertex = int;

    void addEdge(const vertex &edgeBegin, const vertex &edgeEnd) {
        graph[edgeBegin].push_back(edgeEnd);
        graph[edgeEnd];
    }

    const std::vector<vertex> &getNeighbours(const vertex &v) const {
        return graph.at(v);
    }

    const size_t getSize() const {
        return graph.size();
    }

private:
    std::map<vertex, std::vector<vertex>> graph{};
};