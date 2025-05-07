#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

int main()
{
  int n;
  cout << "Enter number of elements: ";
  cin >> n;

  int arr[1000]; // Assuming max 1000 elements
  cout << "Enter elements: ";
  for (int i = 0; i < n; i++)
    cin >> arr[i];

  int min_val = INT_MAX, max_val = INT_MIN, sum = 0;

#pragma omp parallel for reduction(min : min_val) reduction(max : max_val) reduction(+ : sum)
  for (int i = 0; i < n; i++)
  {
    if (arr[i] < min_val)
      min_val = arr[i];
    if (arr[i] > max_val)
      max_val = arr[i];
    sum += arr[i];
  }

  double avg = (double)sum / n;

  cout << "Minimum: " << min_val << "\n";
  cout << "Maximum: " << max_val << "\n";
  cout << "Sum: " << sum << "\n";
  cout << "Average: " << avg << "\n";

  return 0;
}
