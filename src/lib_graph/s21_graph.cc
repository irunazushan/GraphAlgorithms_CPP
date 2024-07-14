#include "s21_graph.h"

void Graph::PrintAdjacencyMatrix() const {
  std::cout << "   ";
  printVertices();
  std::cout << "   ";
  for (int i = 0; i < static_cast<int>(vertices_.size()); ++i) {
    std::cout << "__";
  }
  std::cout << "\n";
  int i = 0;
  for (const auto& row : adjacencyMatrix_) {
    std::cout << vertices_[i++] << " |";
    for (int val : row) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
}

void Graph::printVertices() const {
  for (auto el : vertices_) {
    std::cout << el << " ";
  }
  std::cout << std::endl;
}

void Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream infile(filename);
  if (!infile) {
    throw std::string{"ERROR: Unable to open file"};
  }

  std::string line;
  adjacencyMatrix_.clear();
  vertices_.clear();

  bool firstLine = true;
  std::string arrow;
  while (std::getline(infile, line)) {
    line.erase(0, line.find_first_not_of(" \t"));
    if (firstLine) {
      isDirected_ = (line.find("digraph") == 0);
      arrow = isDirected_ ? "->" : "--";
      size_t start = line.find_first_of(" \t") + 1;
      size_t end = line.find_first_of("{", start) - 1;
      graphName_ = (line.substr(start, end - start));
      firstLine = false;
    } else {
      if (line == "}") {
        break;
      }
      LoadVertices(line, arrow);
    }
  }
}

void Graph::LoadVertices(const std::string& line, const std::string& arrow) {
  if (line.find(arrow) != std::string::npos) {
    int i = 0;
    std::string vertex1 = ExtractVertex(line, 0, FindArrow(line, arrow, 1));
    while (true) {
      std::string vertex2 =
          ExtractVertex(line, FindArrow(line, arrow, i + 1) + arrow.length(),
                        (FindArrow(line, arrow, i + 2)));
      int index1 = GetVertexIndex(vertex1);
      int index2 = GetVertexIndex(vertex2);
      CheckMatrixSize(std::max(index1, index2) + 1);
      int weight = 1;
      if (line.find("[") != std::string::npos) {
        weight = SetWeight(line);
        if (weight == -1) {
          throw std::string{"ERROR: Invalid argument"};
        }
      }
      adjacencyMatrix_[index1][index2] = weight;
      if (!isDirected_) {
        adjacencyMatrix_[index2][index1] = weight;
      }
      ++i;
      if (line[FindArrow(line, arrow, i + 1)] == ';' ||
          line[FindArrow(line, arrow, i + 1)] == '[')
        break;
      else
        vertex1 = vertex2;
    }
  }
}

int Graph::SetWeight(const std::string& str) {
  size_t startPos = str.find("[weight=") + 8;
  size_t endPos = str.find("]", startPos);
  std::string weightStr = str.substr(startPos, endPos - startPos);
  try {
    int weight = std::stoi(weightStr);
    return weight;
  } catch (const std::invalid_argument&) {
    return -1;
  }
}

size_t Graph::FindArrow(const std::string& str, const std::string& delim,
                        size_t n) {
  size_t pos = 0;
  size_t count = 0;

  while (count < n) {
    pos = str.find(delim, pos);
    if (pos == std::string::npos) {
      if (str.find("[") != std::string::npos) {
        return str.find("[");
      } else {
        return str.find(";");
      }
    }
    ++pos;
    ++count;
  }
  return pos - 1;
}

std::string Graph::ExtractVertex(const std::string& line,
                                 const size_t startVertex,
                                 const size_t endVertex) {
  std::string vertex = line.substr(startVertex, endVertex - startVertex);
  vertex.erase(std::remove_if(vertex.begin(), vertex.end(), ::isspace),
               vertex.end());
  return vertex;
}

int Graph::GetVertexIndex(const std::string& vertex) {
  auto it = std::find(vertices_.begin(), vertices_.end(), vertex);
  if (it == vertices_.end()) {
    vertices_.push_back(vertex);
    return vertices_.size() - 1;
  }
  return std::distance(vertices_.begin(), it);
}

void Graph::CheckMatrixSize(size_t size) {
  if (adjacencyMatrix_.size() < size) {
    adjacencyMatrix_.resize(size, std::vector<int>(size, 0));
    for (auto& row : adjacencyMatrix_) {
      row.resize(size, 0);
    }
  }
}

void Graph::ExportGraphToDot(std::string filename) {
  std::ofstream outfile(filename);
  if (!outfile) {
    std::cerr << "Unable to open file " << filename << std::endl;
    return;
  }

  outfile << (isDirected_ ? "digraph " : "graph ") << graphName_ << " {"
          << std::endl;
  std::string arrow = isDirected_ ? " -> " : " -- ";
  for (size_t i = 0; i < adjacencyMatrix_.size(); ++i) {
    size_t startIndex = isDirected_ ? 0 : i;
    for (size_t j = startIndex; j < adjacencyMatrix_[i].size(); ++j) {
      if (adjacencyMatrix_[i][j] == 1) {
        outfile << "\t" << vertices_[i] << arrow << vertices_[j] << ";"
                << std::endl;
      } else if (adjacencyMatrix_[i][j] > 1) {
        outfile << "\t" << vertices_[i] << arrow << vertices_[j]
                << " [weight=" << adjacencyMatrix_[i][j] << "];" << std::endl;
      }
    }
  }

  outfile << "}" << std::endl;
}

bool Graph::IsDirected() const { return isDirected_; }

std::string Graph::GetGraphName() const { return graphName_; }

const std::vector<std::string>& Graph::GetVertices() const { return vertices_; }

const std::vector<std::vector<int>>& Graph::GetAdjacencyMatrix() const {
  return adjacencyMatrix_;
}
