#pragma once

#include <stack>
#include <queue>
#include <utility>
#include <memory>
#include "Graph.hpp"
#include "Traverse.hpp"
#include "PathFinder.hpp"
#include "PathTo.hpp"

class Strategy {
public:
    using vertex = typename Graph::vertex;

    Strategy() = delete;

    explicit Strategy(Graph &_graph, std::shared_ptr<Traverse> &traverse_) : graph(_graph), traverse(
            traverse_) {};

    virtual void execute(const vertex &begin) = 0;

    virtual ~Strategy() = default;

protected:
    Graph &graph;
    std::shared_ptr<Traverse> traverse;
    std::unordered_map<vertex, vertex> previous;

    void begin(const vertex &begin) const { this->traverse->begin(begin); };

    void end() const { this->traverse->end(); };

    void visitVertex(vertex &vertex) const { this->traverse->visitVertex(vertex); };

    void visitEdge(vertex &begin, vertex &end) const { this->traverse->visitEdge(begin, end); };
};