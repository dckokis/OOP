#pragma once

#include <memory>
#include <stack>
#include <queue>
#include <set>
#include "Graph.hpp"
#include "Traverse.hpp"

template<std::shared_ptr<Traverse> &traverse>
class Strategy {
public:
    Strategy() = delete;

    explicit Strategy(const Graph &graph) : m_graph(graph) {};

    virtual void bypassGraph(const Graph::vertex &first) = 0;

    virtual ~Strategy() = default;

protected:
    void begin(const Graph::vertex &first) const { traverse->begin(first); }

    void end() const { traverse->end(); }

    void visitVertex(const Graph::vertex &v) const { traverse->visitVertex(v); }

    void visitEdge(const Graph::vertex &source, const Graph::vertex &destination) const {
        traverse->visitEdge(source, destination);
    }

    const bool is_finished() const { return traverse->isFinished(); }

    const Graph &m_graph;
    std::map<Graph::vertex, Graph::vertex> m_prev{};
};