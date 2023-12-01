#include <iostream>
#include <vector>

using namespace std;

// Iterative Binary Search
int iterativeBinarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;  // Element not found
}

// Recursive Binary Search
int recursiveBinarySearch(const vector<int>& arr, int target, int left, int right) {
    if (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            return recursiveBinarySearch(arr, target, mid + 1, right);
        else
            return recursiveBinarySearch(arr, target, left, mid - 1);
    }

    return -1;  // Element not found
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target = 7;

    // Iterative Binary Search
    int iterativeResult = iterativeBinarySearch(arr, target);
    if (iterativeResult != -1)
        cout << "Iterative Binary Search: Element found at index " << iterativeResult << endl;
    else
        cout << "Iterative Binary Search: Element not found" << endl;

    // Recursive Binary Search
    int recursiveResult = recursiveBinarySearch(arr, target, 0, arr.size() - 1);
    if (recursiveResult != -1)
        cout << "Recursive Binary Search: Element found at index " << recursiveResult << endl;
    else
        cout << "Recursive Binary Search: Element not found" << endl;

    return 0;
}
