#pragma once

#include <iostream>
#include <vector>

class Graph
{

  const size_t testMatrixSize = 6;
  const int MAX = 200;

public:
  Graph();
  Graph(std::vector< std::vector<int> > matrix);
  ~Graph();

  size_t get_matrix_size();
  void debug_test_matrix_output();

  // public variables
  std::vector< std::vector<int> > matrix;
};