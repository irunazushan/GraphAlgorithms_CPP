#include "console_interface.h"

void GraphInterface::run() {
  char keyword;
  while (keyword != 'q') {
    ShowMenu();
    std::cin >> keyword;
    switch (keyword) {
      case '1':
        LoadGraph();
        break;
      case '2':
        TraverseIn(true);
        break;
      case '3':
        TraverseIn(false);
        break;
      case '4':
        FindShortestBtwTwoVertices();
        break;
      case '5':
        FindShortestBtwAllPairVertices();
        break;
      case '6':
        FindMinimumSpanningTree();
        break;
      case '7':
        SolveSalesmanProblem();
        break;
    }
  }
}

void GraphInterface::PrintMatrix(std::vector<std::vector<int>> matrix,
                                 std::vector<std::string> vertices) {
  std::cout << "   ";
  for (auto el : vertices) {
    std::cout << el << " ";
  }
  std::cout << std::endl;
  std::cout << "   ";
  for (int i = 0; i < static_cast<int>(vertices.size()); ++i) {
    std::cout << "__";
  }
  std::cout << "\n";
  int i = 0;
  for (const auto& row : matrix) {
    std::cout << vertices[i++] << " |";
    for (int val : row) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
}

void GraphInterface::LoadGraph() {
  std::cout << "Write file name:" << std::endl;
  std::string fileName;
  std::cin >> fileName;
  try {
    graph_.LoadGraphFromFile(fileName);
    std::cout << "\nAdjacency matrix of the graph from: " << fileName
              << std::endl;
    graph_.PrintAdjacencyMatrix();
  } catch (std::string error_message) {
    std::cout << error_message << std::endl;
  }
}

void GraphInterface::TraverseIn(bool isBFS) {
  if (CheckValidity()) {
    return;
  }
  size_t numOfVertices = graph_.GetVertices().size();
  std::cout << "select start index of the vertex from 1 to " << numOfVertices
            << std::endl;
  int startVertex;
  std::cin >> startVertex;
  if (static_cast<size_t>(startVertex) > numOfVertices || startVertex < 1) {
    std::cout << "ERROR: incorrect vertex's index" << std::endl;
    return;
  }
  std::string* result;
  if (isBFS) {
    result = algorithm_.BreadthFirstSearch(graph_, startVertex);
  } else {
    result = algorithm_.DepthFirstSearch(graph_, startVertex);
  }
  std::cout << "Your result:" << std::endl;

  for (size_t i = 0; i < numOfVertices; ++i) {
    std::cout << result[i] << " ";
  }
  std::cout << std::endl;
  delete[] result;
}

void GraphInterface::FindShortestBtwTwoVertices() {
  if (CheckValidity()) {
    return;
  }
  size_t numOfVertices = graph_.GetVertices().size();
  std::cout
      << "select index of the first vertex and the second vertex from 1 to "
      << numOfVertices << std::endl;
  int vertex1;
  int vertex2;
  std::cin >> vertex1;
  std::cin >> vertex2;
  if (static_cast<size_t>(vertex1) > numOfVertices || vertex1 < 1 ||
      static_cast<size_t>(vertex2) > numOfVertices || vertex2 < 1) {
    std::cout << "ERROR: incorrect vertex's index" << std::endl;
    return;
  }

  int shortestPath =
      algorithm_.GetShortestPathBetweenVertices(graph_, vertex1, vertex2);
  std::cout << "The shortest path between " << vertex1 << " and " << vertex2
            << " is: " << shortestPath << std::endl;
}

void GraphInterface::FindShortestBtwAllPairVertices() {
  if (CheckValidity()) {
    return;
  }
  auto result = algorithm_.GetShortestPathsBetweenAllVertices(graph_);
  std::cout << "The shortest path between all pair of vertices:" << std::endl;
  PrintMatrix(result, graph_.GetVertices());
}

void GraphInterface::FindMinimumSpanningTree() {
  if (CheckValidity()) {
    return;
  }
  auto result = algorithm_.GetLeastSpanningTree(graph_);
  std::cout << "The minimum spanning tree in the graph:" << std::endl;
  PrintMatrix(result, graph_.GetVertices());
}

void GraphInterface::ShowMenu() {
  std::cout << "\nAlgorithm menu:\n";
  std::cout << "1. Load graph from file" << std::endl;
  std::cout << "2. Traverse the graph in breadth" << std::endl;
  std::cout << "3. Traverse the graph in depth and print" << std::endl;
  std::cout << "4. Find the sortest path between two vertices" << std::endl;
  std::cout << "5. Find the sortest path between all pairs of vertices"
            << std::endl;
  std::cout << "6. Search for the minimum spanning tree" << std::endl;
  std::cout << "7. Solve the Salesman problem" << std::endl;
  std::cout << "q. Quit from menu" << std::endl;
  std::cout << std::endl;
}

void GraphInterface::SolveSalesmanProblem() {
  if (CheckValidity()) {
    return;
  }
  try {
    auto result = algorithm_.SolveTravelingSalesmanProblem(graph_);
    std::cout << "The length of the route: " << result.distance << std::endl;
    auto route = result.path;
    for (size_t i = 0; i < route.size(); ++i) {
      std::string delimiter = i == route.size() - 1 ? "\n" : " - ";
      std::cout << route[i] << delimiter;
    }
  } catch (std::string ex) {
    std::cout << ex << std::endl;
  }
}

int GraphInterface::CheckValidity() {
  int isOk = 0;
  if (graph_.GetGraphName() == "") {
    std::cout << "ERROR: you don't choose graph, please select 1. and try again"
              << std::endl;
    isOk = 1;
  }
  return isOk;
}