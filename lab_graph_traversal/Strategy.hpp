#pragma once
#include <stack>
#include <utility>
#include "Graph.hpp"
#include "Traverse.hpp"

class TraverseStrategy {
public:
    using vertex = typename Graph::vertex;

    TraverseStrategy() = delete;

    explicit TraverseStrategy(Graph &_graph, std::shared_ptr<Traverse> &traverse_) : graph(_graph), traverse(
            traverse_) {};

    virtual void execute(const vertex &begin) = 0;

    virtual ~TraverseStrategy() = default;

protected:
    Graph &graph;
    std::shared_ptr<Traverse> traverse;
    std::map<vertex, vertex> previous;

    void begin(const vertex &begin) const { this->traverse->begin(begin); };

    void end() const { this->traverse->end(); };

    void visitVertex(vertex &vertex) const { this->traverse->visitVertex(vertex); };

    void visitEdge(vertex &begin, vertex &end) const { this->traverse->visitEdge(begin, end); };
};

class DFS : public TraverseStrategy {
public:
    DFS() = delete;

    explicit DFS(Graph &_graph, std::shared_ptr<Traverse> &traverse_) : TraverseStrategy(
            _graph, traverse_) {};

    void execute(const vertex &begin) override {
        if (this->graph.getSize() == 0) {
            return;
        }
        this->previous.clear();
        std::stack<std::pair<vertex, bool>> stack;;
        this->begin(begin);

        stack.push(std::make_pair(begin, false));
        this->previous[begin] = begin;
        while (!stack.empty()) {
            auto& [cur, attended] = stack.top();
            if(!attended) {
                this->visitVertex(cur);
                this->visitEdge(this->previous.at(cur), cur);
                attended = true;

                if(this->traverse->IsFinished()) {
                    break;
                }

                const auto& neighbours = this->graph.getNeighbours(cur);
                for (auto i = neighbours.crbegin(); i != neighbours.crend(); ++i) {
                    if(*i != this->previous[cur]) {
                        stack.push(std::make_pair(*i, false));
                        this->previous[*i] = cur;
                    }
                }
             } else {
                stack.pop();
            }
        }
        this->end();
    }
};

class BFS : TraverseStrategy {
public:
    BFS() = delete;

    explicit BFS(Graph &_graph, std::shared_ptr<Traverse> &traverse_) : TraverseStrategy(
            _graph, traverse_) {};
};