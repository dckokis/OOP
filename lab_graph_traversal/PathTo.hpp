#pragma once

#include "PathFinder.hpp"

class PathToVertex final : public PathFinder {
public:
    using vertex = typename Graph::vertex;

    PathToVertex() = delete;

    explicit PathToVertex(const vertex &destination_) : PathFinder(), destination(destination_) {}

private:
    const vertex destination;

    bool comp(const vertex &vertex) override {
        return vertex == destination;
    }

    bool comp(const vertex &source, const vertex &dest) override {
        return isFinished;
    }

    void buildPath() override {
        auto cur = destination;
        while (cur != this->sourceVertex) {
            this->path.emplace_front(cur);
            cur = this->ancestor[cur];
        }
        this->path.emplace_front(cur);
    }
};

class PathToEdge final : public PathFinder {
public:
    using vertex = typename Graph::vertex;

    PathToEdge() = delete;

    explicit PathToEdge(const vertex &source, const vertex &dest) : PathFinder(), first(source), second(dest) {};
private:
    const vertex first, second;

    bool comp(const vertex &source, const vertex &dest) override {
        return first == source && second == dest;
    }

    bool comp(const vertex &vertex) override {
        return isFinished;
    }

    void buildPath() override {
        auto cur = second;
        while (cur != this->first) {
            this->path.emplace_front(cur);
            cur = this->ancestor[cur];
        }
        this->path.emplace_front(cur);
    }
};