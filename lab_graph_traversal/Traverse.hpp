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
    vertex first{};
    std::deque<vertex> path{};
};

class PathFinder : public Traverse {
public:
    using vertex = typename Graph::vertex;

    PathFinder() = default;

    void begin(const vertex &first_) override {
        first = first_;
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
    std::unordered_map<vertex, vertex> ancestor{};

    virtual void buildPath() = 0;

    virtual bool comp(const vertex &vertex) = 0;

    virtual bool comp(const vertex &source, const vertex &dest) = 0;
};

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
        return this->IsFinished();
    }

    void buildPath() override {
        auto cur = destination;
        while (cur != this->first) {
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