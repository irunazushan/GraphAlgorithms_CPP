#include "s21_graph_algorithms.h"

std::string *GraphAlgorithms::DepthFirstSearch(Graph &graph, int start_vertex) {
  std::vector<std::string> vertexes = graph.GetVertices();
  int size = static_cast<int>(vertexes.size());
  CheckVertex(start_vertex, size);
  std::string *result = new std::string[size];
  std::vector<std::vector<int>> adjacencyMatrix = graph.GetAdjacencyMatrix();
  std::vector<visitStatus> visits(size);
  Stack<int> stack;
  stack.push(start_vertex - 1);
  visits[start_vertex - 1] = Grey;
  for (int n = 0; stack.size() > 0; n++) {
    int element = stack.top();
    stack.pop();
    result[n] = vertexes[element];
    visits[element] = Black;
    for (int i = size - 1; i >= 0; i--) {
      if (adjacencyMatrix[element][i] && visits[i] == White) {
        stack.push(i);
        visits[i] = Grey;
      }
    }
  }
  return result;
}

std::string *GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                 int start_vertex) {
  std::vector<std::string> vertexes = graph.GetVertices();
  int size = static_cast<int>(vertexes.size());
  CheckVertex(start_vertex, size);
  std::string *result = new std::string[size];
  std::vector<std::vector<int>> adjacencyMatrix = graph.GetAdjacencyMatrix();
  std::vector<visitStatus> visits(size);
  Queue<int> queue;
  queue.push(start_vertex - 1);
  visits[start_vertex - 1] = Grey;
  for (int n = 0; queue.size() > 0; n++) {
    int element = queue.front();
    queue.pop();
    result[n] = vertexes[element];
    visits[element] = Black;
    for (int i = 0; i < size; i++) {
      if (adjacencyMatrix[element][i] && visits[i] == White) {
        queue.push(i);
        visits[i] = Grey;
      }
    }
  }
  return result;
}

void GraphAlgorithms::CheckVertex(int start_vertex, int size) {
  if (start_vertex < 1 || start_vertex > size) {
    throw std::out_of_range("ERROR: The start_vertex is wrong!");
  }
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  int size = static_cast<int>(graph.GetVertices().size());
  std::vector<visitStatus> visits(size);
  std::vector<int> distance;
  distance.resize(size, INT_MAX);
  CheckVertex(vertex1, size);
  CheckVertex(vertex2, size);
  std::vector<std::vector<int>> adjacencyMatrix = graph.GetAdjacencyMatrix();
  int n = vertex1 - 1;
  distance[n] = 0;
  visits[n] = Black;
  while (visits[vertex2 - 1] == White) {
    for (int i = 0; i < size; i++) {
      if (adjacencyMatrix[n][i] > 0 &&
          distance[n] + adjacencyMatrix[n][i] < distance[i]) {
        distance[i] = distance[n] + adjacencyMatrix[n][i];
      }
    }
    n = FindMinPath(distance, visits, size);
    visits[n] = Black;
  }
  return distance[vertex2 - 1];
}

int GraphAlgorithms::FindMinPath(std::vector<int> distance,
                                 std::vector<visitStatus> visits, int size) {
  int min = INT_MAX;
  int element = -1;
  for (int i = 0; i < size; i++) {
    if (distance[i] < min && visits[i] == White) {
      element = i;
      min = distance[i];
    }
  }
  return element;
}

std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  std::vector<std::vector<int>> result = graph.GetAdjacencyMatrix();
  int size = static_cast<int>(graph.GetVertices().size());
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (result[i][j] == 0 && i != j) {
        result[i][j] = INT_MAX;
      }
    }
  }
  for (int k = 0; k < size; k++) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (result[i][k] != INT_MAX && result[k][j] != INT_MAX) {
          result[i][j] = std::min(result[i][j], result[i][k] + result[k][j]);
        }
      }
    }
  }
  return result;
}

std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  std::set<std::string> unused = FromVectorToSet(graph.GetVertices());
  std::set<std::string> used;
  std::vector<std::vector<int>> adjacencyMatrix = graph.GetAdjacencyMatrix();
  size_t size = adjacencyMatrix.size();
  std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));
  std::string element = graph.GetVertices()[0];
  used.insert(element);
  unused.erase(element);
  while (!unused.empty()) {
    int minWeight = INT_MAX;
    int minWeightIndex = -1;
    int indexOfUsed = -1;
    for (const auto &el : used) {
      int indexOfElement = graph.GetVertexIndex(el);
      for (size_t i = 0; i < size; ++i) {
        int currWeight = adjacencyMatrix[indexOfElement][i];
        if (currWeight != 0 && currWeight < minWeight &&
            used.find(graph.GetVertices()[i]) == used.end()) {
          minWeight = currWeight;
          minWeightIndex = i;
          indexOfUsed = indexOfElement;
        }
      }
    }
    if (minWeight != -1) {
      result[indexOfUsed][minWeightIndex] = minWeight;
      result[minWeightIndex][indexOfUsed] = minWeight;
      element = graph.GetVertices()[minWeightIndex];
      used.insert(element);
      unused.erase(element);
    } else {
      break;
    }
  }
  return result;
}

std::set<std::string> GraphAlgorithms::FromVectorToSet(
    std::vector<std::string> vertices) {
  std::set<std::string> result;
  for (auto el : vertices) {
    result.insert(el);
  }
  return result;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  size_ = static_cast<int>(graph.GetVertices().size());
  answer_.distance = INFINITY;
  adjacencyMatrix_ = graph.GetAdjacencyMatrix();
  antsCalculating();
  for (int n = 0; n < 200; n++) {
    pheromone_.clear();
    pheromone_.resize(size_, std::vector<double>(size_));
    for (int i = 0; i < size_; i++) {
      currentVertex_ = i;
      tmpResult_.push_back(i);
      std::vector<visitStatus> visits(size_, White);
      bool flagEnd = false;
      visits[currentVertex_] = Black;
      while (!flagEnd) {
        flagEnd = GetNextVertex(GetRandomChoice(), countProbability(visits));
        if (flagEnd) {
          checkTmpResult(visits, i);
          tmpResult_.clear();
        } else
          visits[currentVertex_] = Black;
      }
    }
    ChangePheromone();
  }
  if (answer_.distance == INFINITY) {
    throw std::string{"ERROR: There is no any path!"};
  }
  GetAnswer();
  return answer_;
}

void GraphAlgorithms::antsCalculating() {
  ants_.clear();
  ants_.resize(size_, std::vector<AntsPath>(size_));
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      if (adjacencyMatrix_[i][j]) {
        ants_[i][j].edgeConst = (double)10 / adjacencyMatrix_[i][j];
      }
    }
  }
}

bool GraphAlgorithms::GetNextVertex(double random,
                                    std::vector<double> probability) {
  double tmp = 0;
  for (int i = 0; i < size_; i++) {
    tmp += probability[i];
    if (random <= tmp) {
      currentVertex_ = i;
      tmpResult_.push_back(i);
      return 0;
    }
  }
  return 1;
}

double GraphAlgorithms::GetRandomChoice() {
  std::uniform_real_distribution<> dist(0.0, 1.0);
  std::default_random_engine re(
      std::chrono::system_clock::now().time_since_epoch().count());
  return dist(re);
}

std::vector<double> GraphAlgorithms::countProbability(
    std::vector<visitStatus> visits) {
  double total = 0;
  std::vector<double> probability(size_);
  for (int i = 0; i < size_; i++) {
    if (ants_[currentVertex_][i].edgeConst && visits[i] == White) {
      total += (pow(ants_[currentVertex_][i].pheromone, A) *
                pow(ants_[currentVertex_][i].edgeConst, B));
    }
  }
  for (int i = 0; i < size_; i++) {
    if (visits[i] == White && total) {
      probability[i] = (pow(ants_[currentVertex_][i].pheromone, A) *
                        pow(ants_[currentVertex_][i].edgeConst, B)) /
                       total;
    }
  }
  return probability;
}

void GraphAlgorithms::checkTmpResult(std::vector<visitStatus> visits,
                                     int startVertex) {
  if (std::find(visits.begin(), visits.end(), White) == visits.end() &&
      adjacencyMatrix_[currentVertex_][startVertex]) {
    tmpResult_.push_back(startVertex);
    double distance = 0;
    for (int i = 0; i < size_; i++) {
      distance += adjacencyMatrix_[tmpResult_[i]][tmpResult_[i + 1]];
    }
    for (int i = 0; i < size_; i++) {
      pheromone_[tmpResult_[i]][tmpResult_[i + 1]] += Q / distance;
    }
    if (distance < answer_.distance) {
      answer_.distance = distance;
      answer_.path = tmpResult_;
    }
  }
}

void GraphAlgorithms::GetAnswer() {
  for (int i = 0; i <= size_; i++) {
    answer_.path[i]++;
  }
}

void GraphAlgorithms::ChangePheromone() {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      ants_[i][j].pheromone *= K;
    }
  }
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      ants_[i][j].pheromone += pheromone_[i][j];
    }
  }
}
