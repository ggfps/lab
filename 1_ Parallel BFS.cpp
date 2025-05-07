#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

const int MAX_NODES = 100;
int adj[MAX_NODES][MAX_NODES]; // Adjacency matrix
int children_count[MAX_NODES]; // Number of children for each node

void parallel_BFS(int root, int total_nodes)
{
  queue<int> currentLevel;
  currentLevel.push(root);

  while (!currentLevel.empty())
  {
    int level_size = currentLevel.size();
    queue<int> nextLevel;

#pragma omp parallel
    {
#pragma omp for
      for (int i = 0; i < level_size; ++i)
      {
        int current;

#pragma omp critical
        {
          if (!currentLevel.empty())
          {
            current = currentLevel.front();
            currentLevel.pop();
          }
          else
          {
            current = -1;
          }
        }

        if (current != -1)
        {
#pragma omp critical
          cout << current << " ";

          for (int j = 0; j < children_count[current]; ++j)
          {
#pragma omp critical
            nextLevel.push(adj[current][j]);
          }
        }
      }
    }

    swap(currentLevel, nextLevel);
  }
}

int main()
{
  int total_nodes = 7;

  // Build tree:
  // 1 -> 2, 3
  // 2 -> 4, 5
  // 3 -> 6, 7
  adj[1][0] = 2;
  adj[1][1] = 3;
  children_count[1] = 2;
  adj[2][0] = 4;
  adj[2][1] = 5;
  children_count[2] = 2;
  adj[3][0] = 6;
  adj[3][1] = 7;
  children_count[3] = 2;

  cout << "Parallel BFS traversal: ";
  parallel_BFS(1, total_nodes);
  cout << endl;

  return 0;
}
