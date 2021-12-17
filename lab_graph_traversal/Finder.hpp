#pragma once

#include "Graph.hpp"
#include <unordered_map>

class Finder {
public:
    using vertex = typename Graph::vertex;

    Finder() = default;

    virtual ~Finder() = default;

    virtual void begin(const vertex &first_) = 0;

    virtual void end() = 0;

    virtual void visitVertex(const vertex &vrtx) = 0;

    virtual void visitEdge(const vertex &source, const vertex &dest) = 0;


    [[nodiscard]] bool IsFinished() const { // я тут получаю по сути копию, делать копию константной смысла нет, мы ее все равно копируем
        return isFinished;
    }

    [[nodiscard]] std::deque<vertex> getPath() const {
        return path;
    }

protected:
    bool isFinished = false;
    std::deque<vertex> path{};
};