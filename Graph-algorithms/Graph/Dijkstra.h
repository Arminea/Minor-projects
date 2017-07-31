#pragma once

#include "Graph.h"

class Dijkstra
{
public:
  // functions
  Dijkstra();
  ~Dijkstra();

  void set_graph(Graph *graph);
  void compute_paths(int source, int target);

  // variables
  Graph *m_graph;
  size_t m_graph_size;
  
private:
  int min_distance(std::vector<int> min_dist, std::vector<bool> active);
  void debug_print_solution(std::vector<int> min_dist);
};

