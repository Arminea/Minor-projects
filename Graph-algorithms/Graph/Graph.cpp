#include "stdafx.h"

#include "Graph.h"

Graph::Graph()
{
  // initialize test matrix
  std::vector<int> row0 = { 0, 5, 2, 0, 0, 0 };
  std::vector<int> row1 = { 5, 0, 3, 6, 1, 4 };
  std::vector<int> row2 = { 2, 3, 0, 0, 1, 0 };
  std::vector<int> row3 = { 0, 6, 0, 0, 3, 2 };
  std::vector<int> row4 = { 0, 1, 1, 3, 0, 6 };
  std::vector<int> row5 = { 0, 4, 0, 2, 6, 0 };

  matrix.push_back(row0);
  matrix.push_back(row1);
  matrix.push_back(row2);
  matrix.push_back(row3);
  matrix.push_back(row4);
  matrix.push_back(row5);
}

Graph::Graph(std::vector< std::vector<int> > matrix)
{
}

Graph::~Graph()
{
}

// ******************************** GETTERS ***********************
size_t Graph::get_matrix_size() {
  return matrix.size();
}

// ******************************** DEBUG ***********************
void Graph::debug_test_matrix_output() {
  for (int i = 0; i < matrix.size(); i++)
  {
    for (int j = 0; j < matrix[i].size(); j++)
    {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}
