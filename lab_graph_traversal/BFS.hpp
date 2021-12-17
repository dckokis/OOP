#pragma once

#include <memory>
#include <utility>
#include "TraverseStrategy.hpp"

class BFS final : public TraverseStrategy {
public:
    BFS() = delete;

    explicit BFS(std::shared_ptr<Finder> traverse_) : TraverseStrategy(std::move(traverse_)) {};

    void execute(std::shared_ptr<Graph> graph, const vertex &begin_) override {
        if (graph->getSize() == 0) {
            return;
        }
        std::unordered_map<vertex, vertex> previous;
        std::queue<vertex> q;
        begin(begin_);

        q.push(begin_);
        previous[begin_] = begin_;
        while(!q.empty()){
            auto cur = q.front();
            q.pop();
            visitVertex(cur);
            visitEdge(previous.at(cur), cur);
            if(traverse->IsFinished()) {
                break;
            }
            const auto &neighbours = graph->getNeighbours(cur);
            for(auto i = neighbours.crbegin(); i != neighbours.crend(); ++i) {
                if (*i != previous[cur]) {
                    q.push(*i);
                    previous[*i] = cur;
                }
            }
        }
        end();
    };
};
