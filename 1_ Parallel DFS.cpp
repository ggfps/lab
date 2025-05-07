#include <iostream>
#include <omp.h>

using namespace std;

const int MAX_NODES = 100;

int adj[MAX_NODES][MAX_NODES]; // Adjacency matrix
int adjSize[MAX_NODES];        // Number of neighbors for each node
bool visited[MAX_NODES];       // Visited array

void parallel_DFS(int node)
{
// Mark as visited
#pragma omp critical
  {
    if (visited[node])
      return;
    visited[node] = true;
    cout << node << " ";
  }

// Parallel exploration of neighbors
#pragma omp parallel for
  for (int i = 0; i < adjSize[node]; ++i)
  {
    int neighbor = adj[node][i];
    if (!visited[neighbor])
    {
      parallel_DFS(neighbor);
    }
  }
}

int main()
{
  int total_nodes = 5;

  // Initialize adjacency list manually (undirected graph)
  adj[0][0] = 1;
  adj[0][1] = 2;
  adjSize[0] = 2;
  adj[1][0] = 0;
  adj[1][1] = 3;
  adjSize[1] = 2;
  adj[2][0] = 0;
  adj[2][1] = 4;
  adjSize[2] = 2;
  adj[3][0] = 1;
  adjSize[3] = 1;
  adj[4][0] = 2;
  adjSize[4] = 1;

  // Initialize visited array
  for (int i = 0; i < total_nodes; ++i)
    visited[i] = false;

  cout << "Parallel DFS traversal: ";
  parallel_DFS(0);
  cout << endl;

  return 0;
}
