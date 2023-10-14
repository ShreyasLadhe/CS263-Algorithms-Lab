#include <iostream>
using namespace std;

int max_ele(int arr[], int low, int high) {
    if (low == high) {
        return arr[low];
    }

    if (low + 1 == high) {
        return max(arr[low], arr[high]);
    }

    int mid = low + (high - low) / 2;

    if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
        return arr[mid];
    } else if (arr[mid] > arr[mid - 1] && arr[mid] < arr[mid + 1]) {
        return max_ele(arr, mid + 1, high);
    } else {
        return max_ele(arr, low, mid - 1);
    }
}

int main() {
    int arr[] = {1, 3, 8, 12, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxElement = max_ele(arr, 0, n - 1);
    cout << "The maximum element in the bitonic array is: " << maxElement << endl;
    return 0;
}
