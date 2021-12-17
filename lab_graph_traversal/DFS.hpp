#pragma once

#include <memory>
#include "Strategy.hpp"

class DFS final : public Strategy {
public:
    DFS() = delete;

    explicit DFS(Graph &_graph, std::shared_ptr<Traverse> &traverse_) : Strategy(
            _graph, traverse_) {};

    void execute(const vertex &begin) override {
        if (this->graph.getSize() == 0) {
            return;
        }
        this->previous.clear();
        std::stack<std::pair<vertex, bool>> stack;
        this->begin(begin);

        stack.push(std::make_pair(begin, false));
        this->previous[begin] = begin;
        while (!stack.empty()) {
            auto&[cur, attended] = stack.top();
            if (!attended) {
                this->visitVertex(cur);
                this->visitEdge(this->previous.at(cur), cur);
                attended = true;

                if (this->traverse->IsFinished()) {
                    break;
                }

                const auto &neighbours = this->graph.getNeighbours(cur);
                for (auto i = neighbours.crbegin(); i != neighbours.crend(); ++i) {
                    if (*i != this->previous[cur]) {
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
