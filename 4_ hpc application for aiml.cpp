#include <iostream>
#include <omp.h>
using namespace std;

#define N 3 // Size of matrix (3x3 for simplicity)

int main()
{
  int A[N][N] = {{1, 2, 3},
                 {4, 5, 6},
                 {7, 8, 9}};
  int B[N][N] = {{9, 8, 7},
                 {6, 5, 4},
                 {3, 2, 1}};
  int C[N][N] = {0}; // Result matrix

// Parallel matrix multiplication using OpenMP
#pragma omp parallel for collapse(2)
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      for (int k = 0; k < N; k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  cout << "Result of Matrix Multiplication (C = A x B):\n";
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
      cout << C[i][j] << " ";
    cout << endl;
  }

  return 0;
}
