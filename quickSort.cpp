#include <iostream>
#include <vector>

using namespace std;

// Partition the array and return the index of the pivot element
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // Choose the rightmost element as the pivot
    int i = low - 1;        // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If the current element is smaller than or equal to the pivot
        if (arr[j] <= pivot) {
            i++;

            // Swap arr[i] and arr[j]
            swap(arr[i], arr[j]);
        }
    }

    // Swap arr[i + 1] and arr[high] to place the pivot in the correct position
    swap(arr[i + 1], arr[high]);

    return i + 1;  // Return the index of the pivot element
}

// Quick Sort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Find the partitioning index
        int pivotIndex = partition(arr, low, high);

        // Recursively sort the subarrays before and after the partition
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    cout << "Original Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Perform Quick Sort
    quickSort(arr, 0, arr.size() - 1);

    cout << "Sorted Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
