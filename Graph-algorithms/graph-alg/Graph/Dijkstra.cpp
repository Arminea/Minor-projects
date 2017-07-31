#include "stdafx.h"
#include "Dijkstra.h"


Dijkstra::Dijkstra()
{
}

Dijkstra::~Dijkstra()
{
}

void Dijkstra::set_graph(Graph *graph) {
  m_graph = graph;
  m_graph_size = m_graph->get_matrix_size();

  m_graph->debug_test_matrix_output();
}

void Dijkstra::compute_paths(int source, int target) {

  std::vector<int> min_dist(m_graph_size, INT_MAX); // vector of distances
  min_dist[source] = 0;

  std::vector<bool> active(m_graph_size, false); // if the vertex is included is the shortest path
  

  for (int count = 0; count < m_graph_size; count++) {
    int u = min_distance(min_dist, active);

    active[u] = true;

    for (int v = 0; v < m_graph_size; v++) {
      if (active[v] == false && m_graph->matrix[u][v] && min_dist[u] != INT_MAX && min_dist[u] + m_graph->matrix[u][v] < min_dist[v])
        min_dist[v] = min_dist[u] + m_graph->matrix[u][v];
    }
  }

  debug_print_solution(min_dist);
}

int Dijkstra::min_distance(std::vector<int> min_dist, std::vector<bool> active) {
  int min = INT_MAX;
  int min_index;

  for (int v = 0; v < m_graph_size; v++) {
    if (active[v] == false && min_dist[v] <= min) {
      min = min_dist[v];
      min_index = v;
    }
  }

  return min_index;
}

void Dijkstra::debug_print_solution(std::vector<int> min_dist) {
  printf("Vertex Distance from Source\n");
  for (int i = 0; i < m_graph_size; i++)
    printf("To node %d is a path size %d\n", i, min_dist[i]);
}
