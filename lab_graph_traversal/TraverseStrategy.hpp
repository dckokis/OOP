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

    explicit TraverseStrategy(std::unique_ptr<Finder> traverse_) : finder(std::move(
            traverse_)) {};

    virtual void execute(const Graph& graph, const vertex &begin) = 0;

    [[nodiscard]] std::deque<vertex> getPath() const {
        return finder->getPath();
    }

    virtual ~TraverseStrategy() = default;
protected:
    std::unique_ptr<Finder> finder;

    void begin(const vertex &begin) const { this->finder->begin(begin); };

    void end() const { this->finder->end(); };

    void visitVertex(vertex &vertex) const { this->finder->visitVertex(vertex); };

    void visitEdge(vertex &begin, vertex &end) const { this->finder->visitEdge(begin, end); };
};