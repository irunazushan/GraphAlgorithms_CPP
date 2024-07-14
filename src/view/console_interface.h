#ifndef CONSOLE_INTERFACE_H_
#define CONSOLE_INTERFACE_H_

#include "../lib_graph/s21_graph.h"
#include "../lib_graph_algorithms/s21_graph_algorithms.h"

class GraphInterface {
 public:
  void run();

 private:
  Graph graph_;
  GraphAlgorithms algorithm_;

  void PrintMatrix(std::vector<std::vector<int>> matrix,
                   std::vector<std::string> vertices);
  void LoadGraph();
  void TraverseIn(bool isBFS);
  void FindShortestBtwTwoVertices();
  void FindShortestBtwAllPairVertices();
  void FindMinimumSpanningTree();
  void SolveSalesmanProblem();
  int CheckValidity();
  void ShowMenu();
};

#endif