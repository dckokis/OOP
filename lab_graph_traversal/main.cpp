#include <iostream>
#include "Strategy.hpp"

int main() {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 5);
    g.addEdge(5, 6);

    std::shared_ptr<Traverse> tr = std::make_shared<PathToVertex>(6);
    DFS s(g, tr);

    s.execute(1);
    auto path = tr->getPath();
    for(auto i = path.begin(); i != path.end(); ++i) {
        std::cout << *i << ' ';
    }

    return 0;
}
