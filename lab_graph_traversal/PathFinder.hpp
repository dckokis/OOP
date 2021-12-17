#pragma once

#include "Traverse.hpp"

class PathFinder : public Traverse {
public:
    using vertex = typename Graph::vertex;

    PathFinder() = default;

    void begin(const vertex &first_) override {
        sourceVertex = first_;
        isFinished = false;
        path.clear();
    }

    void end() override {
        if (!isFinished) {
            path.clear();
            return;
        }
        buildPath();
    }

    void visitVertex(const vertex &vrtx) override {
        isFinished = comp(vrtx);
    }

    void visitEdge(const vertex &source, const vertex &dest) override {
        isFinished = comp(source, dest);
        ancestor[dest] = source;
    }

    ~PathFinder() override = default;

protected:
    vertex sourceVertex{};

    std::unordered_map<vertex, vertex> ancestor{};

    virtual void buildPath() = 0;

    virtual bool comp(const vertex &vertex) = 0;

    virtual bool comp(const vertex &source, const vertex &dest) = 0;
};