#include "TraverseStrategy.hpp"
#include "DFS.hpp"
#include "BFS.hpp"
#include <gtest/gtest.h>

TEST(DFS, EmptyGraph) {
    auto g = std::make_shared<Graph>();
    std::shared_ptr<Finder> tr = std::make_shared<PathToVertex>(4);
    DFS s(tr);
    s.execute(g, 1);
    EXPECT_TRUE(tr->getPath().empty());
}

TEST(DFS, VisitNonExistentVertex) {
    auto g = std::make_shared<Graph>();
    g->addEdge(1, 2);
    g->addEdge(1, 3);

    std::shared_ptr<Finder> tr = std::make_shared<PathToVertex>(4);
    DFS s(tr);
    s.execute(g, 1);
    EXPECT_TRUE(tr->getPath().empty());
}

TEST (DFS, VisitExistentVertex) {
    auto g = std::make_shared<Graph>();
    g->addEdge(1, 2);
    g->addEdge(2, 1);
    g->addEdge(1, 3);
    g->addEdge(3, 1);
    g->addEdge(1, 4);
    g->addEdge(4, 1);
    g->addEdge(4, 5);
    g->addEdge(5, 4);
    g->addEdge(4, 6);
    g->addEdge(6, 4);
    g->addEdge(4, 7);
    g->addEdge(7, 4);
    g->addEdge(6, 8);
    g->addEdge(8, 6);
    g->addEdge(6, 9);
    g->addEdge(9, 6);

    std::shared_ptr<Finder> tr0 = std::make_shared<PathToVertex>(1);
    DFS s0(tr0);
    s0.execute(g, 1);
    ASSERT_EQ(tr0->getPath().size(), 1);
    EXPECT_EQ(tr0->getPath().at(0), 1);

    std::shared_ptr<Finder> tr1 = std::make_shared<PathToVertex>(2);
    DFS s1(tr1);
    s1.execute(g, 1);
    ASSERT_EQ(tr1->getPath().size(), 2);
    EXPECT_EQ(tr1->getPath().at(0), 1);
    EXPECT_EQ(tr1->getPath().at(1), 2);

    std::shared_ptr<Finder> tr2 = std::make_shared<PathToVertex>(3);
    DFS s2(tr2);
    s2.execute(g, 1);
    ASSERT_EQ(tr2->getPath().size(), 2);
    EXPECT_EQ(tr2->getPath().at(0), 1);
    EXPECT_EQ(tr2->getPath().at(1), 3);

    std::shared_ptr<Finder> tr = std::make_shared<PathToVertex>(4);
    DFS s(tr);
    s.execute(g, 1);
    ASSERT_EQ(tr->getPath().size(), 2);
    EXPECT_EQ(tr->getPath().at(0), 1);
    EXPECT_EQ(tr->getPath().at(1), 4);
}

TEST(DFS, VisitNonExistentEdge) {
    auto g = std::make_shared<Graph>();
    g->addEdge(1, 2);
    g->addEdge(1, 3);

    std::shared_ptr<Finder> tr = std::make_shared<PathToEdge>(1, 4);
    DFS s(tr);
    s.execute(g, 1);
    EXPECT_TRUE(tr->getPath().empty());
}

TEST(DFS, VisitExistentEdge) {
    auto g = std::make_shared<Graph>();
    g->addEdge(1, 2);
    g->addEdge(1, 3);
    g->addEdge(1, 4);
    g->addEdge(4, 5);
    g->addEdge(4, 6);
    g->addEdge(4, 7);
    g->addEdge(6, 8);
    g->addEdge(6, 9);

    std::shared_ptr<Finder> tr = std::make_shared<PathToEdge>(1, 4);
    DFS s(tr);
    s.execute(g, 1);
    ASSERT_EQ(tr->getPath().size(), 2);
    EXPECT_EQ(tr->getPath().at(0), 1);
    EXPECT_EQ(tr->getPath().at(1), 4);

    std::shared_ptr<Finder> tr1 = std::make_shared<PathToEdge>(1, 2);
    DFS s1(tr1);
    s1.execute(g, 1);
    ASSERT_EQ(tr1->getPath().size(), 2);
    EXPECT_EQ(tr1->getPath().at(0), 1);
    EXPECT_EQ(tr1->getPath().at(1), 2);

    std::shared_ptr<Finder> tr2 = std::make_shared<PathToEdge>(1, 3);
    DFS s2(tr2);
    s2.execute(g, 1);
    ASSERT_EQ(tr2->getPath().size(), 2);
    EXPECT_EQ(tr2->getPath().at(0), 1);
    EXPECT_EQ(tr2->getPath().at(1), 3);
}

TEST(BFS, EmptyGraph) {
    auto g = std::make_shared<Graph>();
    std::shared_ptr<Finder> tr = std::make_shared<PathToVertex>(4);
    BFS s(tr);
    s.execute(g, 1);
    EXPECT_TRUE(tr->getPath().empty());
}

TEST(BFS, VisitNonExistentVertex) {
    auto g = std::make_shared<Graph>();
    g->addEdge(1, 2);
    g->addEdge(1, 3);

    std::shared_ptr<Finder> tr = std::make_shared<PathToVertex>(4);
    BFS s(tr);
    s.execute(g, 1);
    EXPECT_TRUE(tr->getPath().empty());
}

TEST(BFS, VisitExistentVertex) {
    auto g = std::make_shared<Graph>();
    g->addEdge(1, 2);
    g->addEdge(1, 3);
    g->addEdge(1, 4);
    g->addEdge(4, 5);
    g->addEdge(4, 6);
    g->addEdge(4, 7);
    g->addEdge(6, 8);
    g->addEdge(6, 9);

    std::shared_ptr<Finder> tr0 = std::make_shared<PathToVertex>(1);
    BFS s0(tr0);
    s0.execute(g, 1);
    ASSERT_EQ(tr0->getPath().size(), 1);
    EXPECT_EQ(tr0->getPath().at(0), 1);

    std::shared_ptr<Finder> tr1 = std::make_shared<PathToVertex>(2);
    BFS s1(tr1);
    s1.execute(g, 1);
    ASSERT_EQ(tr1->getPath().size(), 2);
    EXPECT_EQ(tr1->getPath().at(0), 1);
    EXPECT_EQ(tr1->getPath().at(1), 2);

    std::shared_ptr<Finder> tr2 = std::make_shared<PathToVertex>(3);
    BFS s2(tr2);
    s2.execute(g, 1);
    ASSERT_EQ(tr2->getPath().size(), 2);
    EXPECT_EQ(tr2->getPath().at(0), 1);
    EXPECT_EQ(tr2->getPath().at(1), 3);

    std::shared_ptr<Finder> tr = std::make_shared<PathToVertex>(4);
    BFS s(tr);
    s.execute(g, 1);
    ASSERT_EQ(tr->getPath().size(), 2);
    EXPECT_EQ(tr->getPath().at(0), 1);
    EXPECT_EQ(tr->getPath().at(1), 4);
}

TEST(BFS, VisitNonExistentEdge) {
    auto g = std::make_shared<Graph>();
    g->addEdge(1, 2);
    g->addEdge(1, 3);

    std::shared_ptr<Finder> tr = std::make_shared<PathToEdge>(1, 4);
    BFS s(tr);
    s.execute(g, 1);
    EXPECT_TRUE(tr->getPath().empty());
}

TEST(BFS, VisitExistentEdge) {
    auto g = std::make_shared<Graph>();
    g->addEdge(1, 2);
    g->addEdge(2, 1);
    g->addEdge(1, 3);
    g->addEdge(3, 1);
    g->addEdge(1, 4);
    g->addEdge(4, 1);
    g->addEdge(4, 5);
    g->addEdge(5, 4);
    g->addEdge(4, 6);
    g->addEdge(6, 4);
    g->addEdge(4, 7);
    g->addEdge(7, 4);
    g->addEdge(6, 8);
    g->addEdge(8, 6);
    g->addEdge(6, 9);
    g->addEdge(9, 6);

    std::shared_ptr<Finder> tr = std::make_shared<PathToEdge>(1, 4);
    BFS s(tr);
    s.execute(g, 1);
    ASSERT_EQ(tr->getPath().size(), 2);
    EXPECT_EQ(tr->getPath().at(0), 1);
    EXPECT_EQ(tr->getPath().at(1), 4);

    std::shared_ptr<Finder> tr1 = std::make_shared<PathToEdge>(1, 2);
    BFS s1(tr1);
    s1.execute(g, 1);
    ASSERT_EQ(tr1->getPath().size(), 2);
    EXPECT_EQ(tr1->getPath().at(0), 1);
    EXPECT_EQ(tr1->getPath().at(1), 2);

    std::shared_ptr<Finder> tr2 = std::make_shared<PathToEdge>(1, 3);
    BFS s2(tr2);
    s2.execute(g, 1);
    ASSERT_EQ(tr2->getPath().size(), 2);
    EXPECT_EQ(tr2->getPath().at(0), 1);
    EXPECT_EQ(tr2->getPath().at(1), 3);
}