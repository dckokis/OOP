#pragma once

#include "Graph.hpp"


class Traverse {
public:
    Traverse() = default;

    virtual void begin(const Graph::vertex &first) {
        firstVertex = first;
        finished = false;
        cyclic = false;
        m_path.clear();
    }

    virtual void visitVertex(const Graph::vertex &v) = 0;

    virtual void visitEdge(const Graph::vertex &sorce, const Graph::vertex &destination) = 0;

    virtual void end() = 0;

    const bool isFinished() const {
        return finished;
    }

    const std::vector<Graph::vertex> &getPath() const {
        return m_path;
    }

    const bool isCyclic() const {
        return cyclic;
    }

    virtual ~Traverse() = default;

protected:
    bool finished = false;
    bool cyclic = false;
    Graph::vertex firstVertex{};
    std::vector<Graph::vertex> m_path{};
};
