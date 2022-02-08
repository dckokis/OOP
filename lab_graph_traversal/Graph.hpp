#pragma once

#include <map>
#include <vector>

class Graph {
public:
    using vertex = int;

   void addEdge(const vertex &edgeBegin, const vertex &edgeEnd) {
       auto neigbours = graph[edgeBegin];
       if(std::find(neigbours.begin(), neigbours.end(), edgeEnd) != neigbours.end()) {
           return;
       }
        graph[edgeBegin].push_back(edgeEnd);
        graph[edgeEnd];
    }

    [[nodiscard]] const std::vector<vertex> &getNeighbours(const vertex &v) const{
        return graph.at(v);
    }

    [[nodiscard]] size_t getSize() const {
        return graph.size();
    }

private:
    std::map<vertex, std::vector<vertex>> graph{};
};
