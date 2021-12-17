#pragma once

#include <memory>
#include <utility>
#include "TraverseStrategy.hpp"

class DFS final : public TraverseStrategy {
public:
    DFS() = delete;

    explicit DFS(std::shared_ptr<Finder> traverse_) : TraverseStrategy(std::move(traverse_)) {};

    void execute(std::shared_ptr<Graph> graph, const vertex &begin_) override {
        if (graph->getSize() == 0) {
            return;
        }
        std::unordered_map<vertex, vertex> previous;
        std::stack<std::pair<vertex, bool>> stack;
        begin(begin_);

        stack.push(std::make_pair(begin_, false));
        previous[begin_] = begin_;
        while (!stack.empty()) {
            auto&[cur, attended] = stack.top();
            if (!attended) {
                visitVertex(cur);
                visitEdge(previous.at(cur), cur);
                attended = true;

                if (traverse->IsFinished()) {
                    break;
                }

                const auto &neighbours = graph->getNeighbours(cur);
                for (auto i = neighbours.crbegin(); i != neighbours.crend(); ++i) {
                    if (*i != previous[cur]) {
                        stack.push(std::make_pair(*i, false));
                        previous[*i] = cur;
                    }
                }
            } else {
                stack.pop();
            }
        }
        end();
    }
};
