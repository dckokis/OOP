#pragma once

#include <memory>
#include "Strategy.hpp"

class BFS final : public Strategy {
public:
    BFS() = delete;

    explicit BFS(Graph &_graph, std::shared_ptr<Traverse> &traverse_) : Strategy(
            _graph, traverse_) {};

    void execute(const vertex &begin) override {
        if (this->graph.getSize() == 0) {
            return;
        }
        this->previous.clear();
        std::queue<vertex> q;
        this->begin(begin);

        q.push(begin);
        this->previous[begin] = begin;
        while(!q.empty()){
            auto cur = q.front();
            q.pop();
            this->visitVertex(cur);
            this->visitEdge(this->previous.at(cur), cur);
            if(this->traverse->IsFinished()) {
                break;
            }
            const auto &neighbours = this->graph.getNeighbours(cur);
            for(auto i = neighbours.crbegin(); i != neighbours.crend(); ++i) {
                if (*i != this->previous[cur]) {
                    q.push(*i);
                    this->previous[*i] = cur;
                }
            }
        }
        this->end();
    };
};
