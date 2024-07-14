#ifndef S21_GRAPH_ALGORITHMS_H_
#define S21_GRAPH_ALGORITHMS_H_

#define A 1
#define B 2
#define Q 2
#define K 0.64

#include <limits.h>

#include <chrono>
#include <climits>
#include <cmath>
#include <random>
#include <set>

#include "../lib_graph/s21_graph.h"
#include "../lib_queue/s21_queue.h"
#include "../lib_stack/s21_stack.h"

enum visitStatus { White = 0, Grey, Black };

struct TsmResult {
  std::vector<int> path;
  double distance = INFINITY;
};

struct AntsPath {
  double edgeConst;
  double pheromone = 0.2;
};

class GraphAlgorithms {
 public:
  std::string *DepthFirstSearch(Graph &graph, int start_vertex);
  std::string *BreadthFirstSearch(Graph &graph, int start_vertex);
  std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph);
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph &graph);

  TsmResult SolveTravelingSalesmanProblem(Graph &graph);

 private:
  TsmResult answer_;
  std::vector<int> tmpResult_;
  int size_;
  std::vector<std::vector<int>> adjacencyMatrix_;
  int currentVertex_;
  std::vector<std::vector<double>> pheromone_;
  std::vector<std::vector<AntsPath>> ants_;

  void CheckVertex(int start_vertex, int size);
  int FindMinPath(std::vector<int> distance, std::vector<visitStatus> visits,
                  int size);
  std::set<std::string> FromVectorToSet(std::vector<std::string> vertices);
  void antsCalculating();
  bool GetNextVertex(double random, std::vector<double> probability);
  std::vector<double> countProbability(std::vector<visitStatus> visits);
  double GetRandomChoice();
  void checkTmpResult(std::vector<visitStatus> visits, int startVertex);
  void ChangePheromone();
  void GetAnswer();
};

#endif