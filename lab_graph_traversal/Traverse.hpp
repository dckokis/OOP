#pragma once

#include "Graph.hpp"
#include <unordered_map>

class Traverse {
public:
    using vertex = typename Graph::vertex;

    Traverse() = default;

    virtual ~Traverse() = default;

    virtual void begin(const vertex &first_) = 0;

    virtual void end() = 0;

    virtual void visitVertex(const vertex &vrtx) = 0;

    virtual void visitEdge(const vertex &source, const vertex &dest) = 0;


    [[nodiscard]] const bool IsFinished() const {
        return isFinished;
    }

    [[nodiscard]] const std::deque<vertex> getPath() const {
        return path;
    }

protected:
    bool isFinished = false;
    std::deque<vertex> path{};
};