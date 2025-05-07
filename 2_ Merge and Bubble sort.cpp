#include <iostream>
#include <omp.h>

using namespace std;

// Swap utility
void swap(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

// ----------- Parallel Bubble Sort -----------
void bubbleSortParallel(int arr[], int n)
{
  for (int i = 0; i < n - 1; ++i)
  {
    bool swapped = false;
#pragma omp parallel for shared(arr) reduction(| : swapped)
    for (int j = 0; j < n - i - 1; ++j)
    {
      if (arr[j] > arr[j + 1])
      {
        swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }
    if (!swapped)
      break;
  }
}

// ----------- Merge Utility -----------
void merge(int arr[], int left, int mid, int right)
{
  int n1 = mid - left + 1, n2 = right - mid;
  int leftArr[n1], rightArr[n2];

  for (int i = 0; i < n1; ++i)
    leftArr[i] = arr[left + i];
  for (int j = 0; j < n2; ++j)
    rightArr[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2)
  {
    if (leftArr[i] <= rightArr[j])
      arr[k++] = leftArr[i++];
    else
      arr[k++] = rightArr[j++];
  }

  while (i < n1)
    arr[k++] = leftArr[i++];
  while (j < n2)
    arr[k++] = rightArr[j++];
}

// ----------- Parallel Merge Sort -----------
void mergeSortParallel(int arr[], int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;

#pragma omp parallel sections
    {
#pragma omp section
      mergeSortParallel(arr, left, mid);

#pragma omp section
      mergeSortParallel(arr, mid + 1, right);
    }

    merge(arr, left, mid, right);
  }
}

// ----------- Main Program -----------
int main()
{
  int N;
  cout << "Enter the size of the array: ";
  cin >> N;

  int original[N], arr1[N], arr2[N];

  cout << "Enter " << N << " elements: ";
  for (int i = 0; i < N; ++i)
  {
    cin >> original[i];
    arr1[i] = original[i];
    arr2[i] = original[i];
  }

  // Run both sorts
  bubbleSortParallel(arr1, N);
  mergeSortParallel(arr2, 0, N - 1);

  // Output results
  cout << "\nSorted array using Parallel Bubble Sort:\n";
  for (int i = 0; i < N; ++i)
    cout << arr1[i] << " ";

  cout << "\n\nSorted array using Parallel Merge Sort:\n";
  for (int i = 0; i < N; ++i)
    cout << arr2[i] << " ";

  cout << endl;
  return 0;
}
