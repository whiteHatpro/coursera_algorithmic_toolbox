#include <iostream>
#include <vector>

using std::vector;
long long merge_and_count_split_inversions(vector<int> &arr, vector<int> &aux, size_t low, size_t mid, size_t high)
{
  int k = low, i = low, j = mid + 1;
  int inversionCount = 0;

  // While there are elements in the left and right runs
  while (i <= mid && j <= high)
  {
    if (arr[i] <= arr[j])
    {
      aux[k++] = arr[i++];
    }
    else
    {
      aux[k++] = arr[j++];
      inversionCount += (mid - i + 1); // NOTE
    }
  }

  // Copy remaining elements
  while (i <= mid)
    aux[k++] = arr[i++];

  // Don't need to copy second half

  // copy back to the original array to reflect sorted order
  for (int i = low; i <= high; i++)
    arr[i] = aux[i];

  return inversionCount;
}

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right)
{
  long long number_of_inversions = 0;
  if (right == left)
  {
    return 0;
  }
  size_t mid = left + ((right - left) / 2);
  number_of_inversions += get_number_of_inversions(a, b, left, mid);
  number_of_inversions += get_number_of_inversions(a, b, mid + 1, right);
  number_of_inversions += merge_and_count_split_inversions(a, b, left, mid, right);
  return number_of_inversions;
}

int main()
{
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> a[i];
  }
  vector<int> b = a;
  std::cout << get_number_of_inversions(a, b, 0, a.size() - 1) << '\n';
}

/**
 * #include <stdio.h>
// Merge two sorted subarrays arr[low .. mid] and arr[mid + 1 .. high]
int Merge(int arr[], int aux[], int low, int mid, int high)
{
  int k = low, i = low, j = mid + 1;
  int inversionCount = 0;
  // While there are elements in the left and right runs
  while (i <= mid && j <= high)
  {
    if (arr[i] <= arr[j])
    {
      aux[k++] = arr[i++];
    }
    else
    {
      aux[k++] = arr[j++];
      inversionCount += (mid - i + 1); // NOTE
    }
  }
  // Copy remaining elements
  while (i <= mid)
    aux[k++] = arr[i++];
  // Don't need to copy second half
  // copy back to the original array to reflect sorted order
  for (int i = low; i <= high; i++)
    arr[i] = aux[i];
  return inversionCount;
}
// Sort array arr [low..high] using auxiliary array aux
int MergeSort(int arr[], int aux[], int low, int high)
{
  // Base case
  if (high == low) // if run size == 1
    return 0;
  // find mid point
  int mid = (low + ((high - low) >> 1));
  printf("mid is:%d\n", mid);
  int inversionCount = 0;
  // recursively split runs into two halves until run size == 1,
  // then merge them and return back up the call chain
  // split / merge left  half
  inversionCount += MergeSort(arr, aux, low, mid);
  // split / merge right half
  inversionCount += MergeSort(arr, aux, mid + 1, high);
  // merge the two half runs
  inversionCount += Merge(arr, aux, low, mid, high);
  return inversionCount;
}
int main()
{
  int arr[] = {2, 3, 9, 2, 9};
  int N = sizeof(arr) / sizeof(arr[0]);
  int aux[N];
  for (int i = 0; i < N; i++)
    aux[i] = arr[i];
  // get inversion count by performing merge sort on arr
  printf("Inversion count is %d", MergeSort(arr, aux, 0, N - 1));
  return 0;
}
*/