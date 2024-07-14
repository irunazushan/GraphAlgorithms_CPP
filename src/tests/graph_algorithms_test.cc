#include "graph_libs_test.h"

TEST(GraphAlgorithms, GraphAlgorithmsTest1) {
  Graph graph;
  graph.LoadGraphFromFile("graph_samples/matrix.dot");

  GraphAlgorithms algorithm;
  std::string* result = algorithm.DepthFirstSearch(graph, 1);
  ASSERT_EQ(result[0], "a");
  ASSERT_EQ(result[1], "b");
  ASSERT_EQ(result[2], "d");
  ASSERT_EQ(result[3], "e");
  delete[] result;

  result = algorithm.BreadthFirstSearch(graph, 1);
  ASSERT_EQ(result[0], "a");
  ASSERT_EQ(result[1], "b");
  ASSERT_EQ(result[2], "c");
  ASSERT_EQ(result[3], "d");
  delete[] result;
}

TEST(GraphAlgorithms, GraphAlgorithmsTest2) {
  Graph graph;
  graph.LoadGraphFromFile("graph_samples/graph_4.dot");

  GraphAlgorithms algorithm;
  ASSERT_EQ(algorithm.GetShortestPathBetweenVertices(graph, 1, 6), 18);
  try {
    algorithm.GetShortestPathBetweenVertices(graph, 1, 7);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
  try {
    algorithm.GetShortestPathBetweenVertices(graph, -1, 6);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(GraphAlgorithms, GraphAlgorithmsTest3) {
  Graph graph;
  graph.LoadGraphFromFile("graph_samples/graph_4.dot");

  GraphAlgorithms algorithm;
  auto result = algorithm.GetShortestPathsBetweenAllVertices(graph);
  ASSERT_EQ(result[0][0], 0);
  ASSERT_EQ(result[0][1], 7);
  ASSERT_EQ(result[0][2], 12);
  ASSERT_EQ(result[0][3], 23);
  ASSERT_EQ(result[0][4], 21);
  ASSERT_EQ(result[0][5], 18);

  ASSERT_EQ(result[1][0], 7);
  ASSERT_EQ(result[1][1], 0);
  ASSERT_EQ(result[1][2], 5);
  ASSERT_EQ(result[1][3], 16);
  ASSERT_EQ(result[1][4], 14);
  ASSERT_EQ(result[1][5], 11);

  ASSERT_EQ(result[2][0], 12);
  ASSERT_EQ(result[2][1], 5);
  ASSERT_EQ(result[2][2], 0);
  ASSERT_EQ(result[2][3], 11);
  ASSERT_EQ(result[2][4], 9);
  ASSERT_EQ(result[2][5], 6);

  ASSERT_EQ(result[3][0], 23);
  ASSERT_EQ(result[3][1], 16);
  ASSERT_EQ(result[3][2], 11);
  ASSERT_EQ(result[3][3], 0);
  ASSERT_EQ(result[3][4], 8);
  ASSERT_EQ(result[3][5], 9);

  ASSERT_EQ(result[4][0], 21);
  ASSERT_EQ(result[4][1], 14);
  ASSERT_EQ(result[4][2], 9);
  ASSERT_EQ(result[4][3], 8);
  ASSERT_EQ(result[4][4], 0);
  ASSERT_EQ(result[4][5], 3);

  ASSERT_EQ(result[5][0], 18);
  ASSERT_EQ(result[5][1], 11);
  ASSERT_EQ(result[5][2], 6);
  ASSERT_EQ(result[5][3], 9);
  ASSERT_EQ(result[5][4], 3);
  ASSERT_EQ(result[5][5], 0);
}

TEST(GraphAlgorithms, GraphAlgorithmsTest4) {
  Graph graph;
  graph.LoadGraphFromFile("graph_samples/spanning_tree.dot");
  graph.PrintAdjacencyMatrix();

  GraphAlgorithms algorithm;
  auto result = algorithm.GetLeastSpanningTree(graph);

  ASSERT_EQ(result[0][1], 7);
  ASSERT_EQ(result[0][3], 5);
  ASSERT_EQ(result[1][0], 7);
  ASSERT_EQ(result[1][4], 7);
  ASSERT_EQ(result[2][4], 5);
  ASSERT_EQ(result[3][0], 5);
  ASSERT_EQ(result[3][5], 6);
  ASSERT_EQ(result[4][1], 7);
  ASSERT_EQ(result[4][2], 5);
  ASSERT_EQ(result[4][6], 9);
  ASSERT_EQ(result[5][3], 6);
  ASSERT_EQ(result[6][4], 9);
}

TEST(GraphAlgorithms, GraphAlgorithmsTest5) {
  Graph graph;
  graph.LoadGraphFromFile("graph_samples/ants.dot");

  GraphAlgorithms algorithm;
  auto result = algorithm.SolveTravelingSalesmanProblem(graph);

  ASSERT_EQ(result.distance, 44);
  ASSERT_EQ(result.path.size(), 11);
}

TEST(GraphAlgorithms, GraphAlgorithmsTest6) {
  Graph graph;
  graph.LoadGraphFromFile("graph_samples/matrix.dot");

  GraphAlgorithms algorithm;

  try {
    auto result = algorithm.SolveTravelingSalesmanProblem(graph);
    ASSERT_ANY_THROW();
  } catch (std::string ex) {
  }
}
