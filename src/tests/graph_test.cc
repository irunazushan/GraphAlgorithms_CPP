#include "graph_libs_test.h"

TEST(Graph, GraphTest1) {
  Graph graph1;
  graph1.LoadGraphFromFile("graph_samples/graph_1.dot");
  std::string name = graph1.GetGraphName();
  ASSERT_EQ(graph1.IsDirected(), false);
  ASSERT_EQ(name, "A");
  ASSERT_EQ(graph1.GetVertices().size(), 4);

  Graph graph2;
  graph2.LoadGraphFromFile("graph_samples/graph_2.dot");
  name = graph2.GetGraphName();
  ASSERT_EQ(name, "B");
  ASSERT_EQ(graph2.GetVertices()[2], "c");
}

TEST(Graph, GraphTest2) {
  Graph graph1;
  graph1.LoadGraphFromFile("graph_samples/graph_1.dot");
  graph1.ExportGraphToDot("graph_samples/graph_1_copy.dot");
  Graph graph2;
  graph2.LoadGraphFromFile("graph_samples/graph_1_copy.dot");
  ASSERT_EQ(graph1.GetGraphName(), graph2.GetGraphName());
}

TEST(Graph, GraphTest3) {
  Graph graph1;
  graph1.LoadGraphFromFile("graph_samples/graph_3.dot");
  ASSERT_EQ(graph1.IsDirected(), true);
  ASSERT_EQ(graph1.GetGraphName(), "C");
  auto adjMx = graph1.GetAdjacencyMatrix();
  ASSERT_EQ(adjMx.size(), 6);
  ASSERT_EQ(adjMx[0][1], 5);
  ASSERT_EQ(adjMx[1][2], 3);
  ASSERT_EQ(adjMx[1][3], 9);
  ASSERT_EQ(adjMx[3][4], 9);
  ASSERT_EQ(adjMx[4][5], 7);
}
