#include <iostream>
#include <stdio.h>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;

void sbubbleSort(vector<int>& arr) {
  int n = arr.size();
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}
void pbubbleSort(vector<int>& arr) {
  int n = arr.size();
  #pragma omp parallel for
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main() {
     //omp_set_num_threads(8);
  int n;
  cout << "Enter the number of elements: ";
  cin >> n;

  vector<int> arr(n);

  for (int i = 0; i < n; i++) {
    cout << "Enter element " << i + 1 << ": ";
    cin >> arr[i];
  }

  cout << "Unsorted array: ";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  // Bubble sort.
  cout << "Sequential bubble sort: ";
  auto start = std::chrono::high_resolution_clock::now();
  sbubbleSort(arr);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  cout << elapsed.count() << " seconds" << endl;
  
  cout << "Sorted array: ";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  // Parallel bubble sort.
  cout << "Parallel bubble sort: ";
  start = std::chrono::high_resolution_clock::now();
  #pragma omp parallel
  pbubbleSort(arr);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  cout << elapsed.count() << " seconds" << endl;
 #pragma omp master
        {
            printf_s("%d\n", omp_get_max_threads( ));
        }

  return 0;
}