#pragma once

#include <stack>
#include <queue>
#include <utility>
#include <memory>
#include "Graph.hpp"
#include "Finder.hpp"
#include "PathFinder.hpp"
#include "PathTo.hpp"

class TraverseStrategy {
public:
    using vertex = typename Graph::vertex;

    TraverseStrategy() = delete;

    explicit TraverseStrategy(std::shared_ptr<Finder> traverse_) : traverse(std::move(
            traverse_)) {};

    virtual void execute(std::shared_ptr<Graph> graph, const vertex &begin) = 0;

    virtual ~TraverseStrategy() = default;

protected:
    //Graph &graph;
    std::shared_ptr<Finder> traverse;
    //std::unordered_map<vertex, vertex> previous;

    void begin(const vertex &begin) const { this->traverse->begin(begin); };

    void end() const { this->traverse->end(); };

    void visitVertex(vertex &vertex) const { this->traverse->visitVertex(vertex); };

    void visitEdge(vertex &begin, vertex &end) const { this->traverse->visitEdge(begin, end); };
};