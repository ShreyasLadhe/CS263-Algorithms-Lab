#include <iostream>

using namespace std;

struct Activity {
    int start, finish;
};

void merge(Activity arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Activity L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i].finish <= R[j].finish) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Activity arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void printMaxActivities(Activity arr[], int n) {
    mergeSort(arr, 0, n - 1);

    cout << "Following activities are selected:\n";

    int i = 0;
    cout << "(" << arr[i].start << ", " << arr[i].finish << ")";

    for (int j = 1; j < n; j++) {
        if (arr[j].start >= arr[i].finish) {
            cout << ", (" << arr[j].start << ", " << arr[j].finish << ")";
            i = j;
        }
    }
}

int main() {
    Activity arr[] = { { 5, 9 }, { 1, 2 }, { 3, 4 }, { 0, 6 }, { 5, 7 }, { 8, 9 } };
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printMaxActivities(arr, n);
    return 0;
}
