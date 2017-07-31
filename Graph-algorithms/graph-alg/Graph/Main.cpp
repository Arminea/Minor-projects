#include "stdafx.h"

#include "Graph.h"
#include "Dijkstra.h"

int _tmain(int argc, _TCHAR* argv[])
{

  Graph graph;

  Dijkstra dijkstra;
  dijkstra.set_graph(&graph);
  dijkstra.compute_paths(0, 6);


  std::cin.get();
  return 0;
}

