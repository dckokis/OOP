#include "TraverseStrategy.hpp"
#include "DFS.hpp"
#include "BFS.hpp"
#include <gtest/gtest.h>

TEST(DFS, EmptyGraph) {
    Graph g;
    std::unique_ptr<Finder> tr = std::make_unique<PathToVertex>(4);
    DFS s(std::move(tr));
    s.execute(g, 1);
    EXPECT_TRUE(s.getPath().empty());
}

TEST(DFS, VisitNonExistentVertex) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    std::unique_ptr<Finder> tr = std::make_unique<PathToVertex>(4);
    DFS s(std::move(tr));
    s.execute(g, 1);
    EXPECT_TRUE(s.getPath().empty());
}

TEST (DFS, VisitExistentVertex) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(2, 1);
    g.addEdge(1, 3);
    g.addEdge(3, 1);
    g.addEdge(1, 4);
    g.addEdge(4, 1);
    g.addEdge(4, 5);
    g.addEdge(5, 4);
    g.addEdge(4, 6);
    g.addEdge(6, 4);
    g.addEdge(4, 7);
    g.addEdge(7, 4);
    g.addEdge(6, 8);
    g.addEdge(8, 6);
    g.addEdge(6, 9);
    g.addEdge(9, 6);

    std::unique_ptr<Finder> tr0 = std::make_unique<PathToVertex>(1);
    DFS s0(std::move(tr0));
    s0.execute(g, 1);
    ASSERT_EQ(s0.getPath().size(), 1);
    EXPECT_EQ(s0.getPath().at(0), 1);

    std::unique_ptr<Finder> tr1 = std::make_unique<PathToVertex>(2);
    DFS s1(std::move(tr1));
    s1.execute(g, 1);
    ASSERT_EQ(s1.getPath().size(), 2);
    EXPECT_EQ(s1.getPath().at(0), 1);
    EXPECT_EQ(s1.getPath().at(1), 2);

    std::unique_ptr<Finder> tr2 = std::make_unique<PathToVertex>(3);
    DFS s2(std::move(tr2));
    s2.execute(g, 1);
    ASSERT_EQ(s2.getPath().size(), 2);
    EXPECT_EQ(s2.getPath().at(0), 1);
    EXPECT_EQ(s2.getPath().at(1), 3);

    std::unique_ptr<Finder> tr = std::make_unique<PathToVertex>(4);
    DFS s(std::move(tr));
    s.execute(g, 1);
    ASSERT_EQ(s.getPath().size(), 2);
    EXPECT_EQ(s.getPath().at(0), 1);
    EXPECT_EQ(s.getPath().at(1), 4);
}

TEST(DFS, VisitNonExistentEdge) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    std::unique_ptr<Finder> tr = std::make_unique<PathToEdge>(1, 4);
    DFS s(std::move(tr));
    s.execute(g, 1);
    EXPECT_TRUE(s.getPath().empty());
}

TEST(DFS, VisitExistentEdge) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(4, 7);
    g.addEdge(6, 8);
    g.addEdge(6, 9);

    std::unique_ptr<Finder> tr = std::make_unique<PathToEdge>(1, 4);
    DFS s(std::move(tr));
    s.execute(g, 1);
    ASSERT_EQ(s.getPath().size(), 2);
    EXPECT_EQ(s.getPath().at(0), 1);
    EXPECT_EQ(s.getPath().at(1), 4);

    std::unique_ptr<Finder> tr1 = std::make_unique<PathToEdge>(1, 2);
    DFS s1(std::move(tr1));
    s1.execute(g, 1);
    ASSERT_EQ(s1.getPath().size(), 2);
    EXPECT_EQ(s1.getPath().at(0), 1);
    EXPECT_EQ(s1.getPath().at(1), 2);

    std::unique_ptr<Finder> tr2 = std::make_unique<PathToEdge>(1, 3);
    DFS s2(std::move(tr2));
    s2.execute(g, 1);
    ASSERT_EQ(s2.getPath().size(), 2);
    EXPECT_EQ(s2.getPath().at(0), 1);
    EXPECT_EQ(s2.getPath().at(1), 3);
}

TEST(BFS, EmptyGraph) {
    Graph g;
    std::unique_ptr<Finder> tr = std::make_unique<PathToVertex>(4);
    BFS s(std::move(tr));
    s.execute(g, 1);
    EXPECT_TRUE(s.getPath().empty());
}

TEST(BFS, VisitNonExistentVertex) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    std::unique_ptr<Finder> tr = std::make_unique<PathToVertex>(4);
    BFS s(std::move(tr));
    s.execute(g, 1);
    EXPECT_TRUE(s.getPath().empty());
}

TEST(BFS, VisitExistentVertex) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(4, 7);
    g.addEdge(6, 8);
    g.addEdge(6, 9);

    std::unique_ptr<Finder> tr0 = std::make_unique<PathToVertex>(1);
    BFS s0(std::move(tr0));
    s0.execute(g, 1);
    ASSERT_EQ(s0.getPath().size(), 1);
    EXPECT_EQ(s0.getPath().at(0), 1);

    std::unique_ptr<Finder> tr1 = std::make_unique<PathToVertex>(2);
    BFS s1(std::move(tr1));
    s1.execute(g, 1);
    ASSERT_EQ(s1.getPath().size(), 2);
    EXPECT_EQ(s1.getPath().at(0), 1);
    EXPECT_EQ(s1.getPath().at(1), 2);

    std::unique_ptr<Finder> tr2 = std::make_unique<PathToVertex>(3);
    BFS s2(std::move(tr2));
    s2.execute(g, 1);
    ASSERT_EQ(s2.getPath().size(), 2);
    EXPECT_EQ(s2.getPath().at(0), 1);
    EXPECT_EQ(s2.getPath().at(1), 3);

    std::unique_ptr<Finder> tr = std::make_unique<PathToVertex>(4);
    DFS s(std::move(tr));
    s.execute(g, 1);
    ASSERT_EQ(s.getPath().size(), 2);
    EXPECT_EQ(s.getPath().at(0), 1);
    EXPECT_EQ(s.getPath().at(1), 4);

}

TEST(BFS, VisitNonExistentEdge) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    std::unique_ptr<Finder> tr = std::make_unique<PathToEdge>(1, 4);
    BFS s(std::move(tr));
    s.execute(g, 1);
    EXPECT_TRUE(s.getPath().empty());
}

TEST(BFS, VisitExistentEdge) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(2, 1);
    g.addEdge(1, 3);
    g.addEdge(3, 1);
    g.addEdge(1, 4);
    g.addEdge(4, 1);
    g.addEdge(4, 5);
    g.addEdge(5, 4);
    g.addEdge(4, 6);
    g.addEdge(6, 4);
    g.addEdge(4, 7);
    g.addEdge(7, 4);
    g.addEdge(6, 8);
    g.addEdge(8, 6);
    g.addEdge(6, 9);
    g.addEdge(9, 6);

    std::unique_ptr<Finder> tr = std::make_unique<PathToEdge>(1, 4);
    BFS s(std::move(tr));
    s.execute(g, 1);
    ASSERT_EQ(s.getPath().size(), 2);
    EXPECT_EQ(s.getPath().at(0), 1);
    EXPECT_EQ(s.getPath().at(1), 4);

    std::unique_ptr<Finder> tr1 = std::make_unique<PathToEdge>(1, 2);
    BFS s1(std::move(tr1));
    s1.execute(g, 1);
    ASSERT_EQ(s1.getPath().size(), 2);
    EXPECT_EQ(s1.getPath().at(0), 1);
    EXPECT_EQ(s1.getPath().at(1), 2);

    std::unique_ptr<Finder> tr2 = std::make_unique<PathToEdge>(1, 3);
    BFS s2(std::move(tr2));
    s2.execute(g, 1);
    ASSERT_EQ(s2.getPath().size(), 2);
    EXPECT_EQ(s2.getPath().at(0), 1);
    EXPECT_EQ(s2.getPath().at(1), 3);
}