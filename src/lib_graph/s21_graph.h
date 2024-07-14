#ifndef S21_GRAPH_H_
#define S21_GRAPH_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

class Graph {
 public:
  void PrintAdjacencyMatrix() const;
  void printVertices() const;
  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(std::string filename);
  bool IsDirected() const;
  std::string GetGraphName() const;
  const std::vector<std::string>& GetVertices() const;
  const std::vector<std::vector<int>>& GetAdjacencyMatrix() const;
  int GetVertexIndex(const std::string& vertex);

 private:
  std::vector<std::vector<int>> adjacencyMatrix_;
  std::vector<std::string> vertices_;
  std::string graphName_ = "";
  bool isDirected_;

  void LoadVertices(const std::string& line, const std::string& arrow);
  size_t FindArrow(const std::string& str, const std::string& delim, size_t n);
  int SetWeight(const std::string& str);
  std::string ExtractVertex(const std::string& line, const size_t startVertex,
                            const size_t endVertex);
  void CheckMatrixSize(size_t size);
};

#endif