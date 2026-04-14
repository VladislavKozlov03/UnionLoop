#include "test_fixtures.hpp"

#include "cfg.hpp"

void Graph1::SetUp() {
    for (int i = 0; i < 6; ++i) {
        graph.addBasicBlock();
    }
    graph.setStartId(0);
    graph.setStopId(5);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 1);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
}

void Graph2::SetUp() {
    for (int i = 0; i < 6; ++i) {
        graph.addBasicBlock();
    }
    graph.setStartId(0);
    graph.setStopId(5);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 1);
    graph.addEdge(3, 5);
    graph.addEdge(4, 2);
    graph.addEdge(4, 5);
}
void Graph3::SetUp() {
    for (int i = 0; i < 6; ++i) {
        graph.addBasicBlock();
    }
    graph.setStartId(0);
    graph.setStopId(5);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
}

void Graph4::SetUp() {
    for (int i = 0; i < 7; ++i) {
        graph.addBasicBlock();
    }
    graph.setStartId(0);
    graph.setStopId(6);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 3);
    graph.addEdge(4, 5);
    graph.addEdge(5, 2);
    graph.addEdge(5, 6);
}