#include <iostream>

using namespace std;

int checkcount(int test[], int temp[], int left, int mid, int right) {
    int inv = 0;

    int i = left;       
    int j = mid + 1;    
    int k = left;       

    while (i <= mid && j <= right) {
        if (test[i] <= test[j]) {
            temp[k++] = test[i++];
        } else {
            temp[k++] = test[j++];
            inv += mid - i + 1;
        }
    }
    
    while (i <= mid) {
        temp[k++] = test[i++];
    }

    while (j <= right) {
        temp[k++] = test[j++];
    }

    for (int l = left; l <= right; ++l) {
        test[l] = temp[l];
    }

    return inv;
}

int merge(int test[], int temp[], int left, int right) {
    int inv = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;

        inv += merge(test, temp, left, mid);
        inv += merge(test, temp, mid + 1, right);

        inv += checkcount(test, temp, left, mid, right);
    }

    return inv;
}

int countinv(int test[], int n) {
    int temp[n];
    return merge(test, temp, 0, n - 1);
}

int main() {
    int test[] = {1, 2, 3, 0, 5, 6};
    int n = sizeof(test) / sizeof(test[0]);
    int inv = countinv(test, n);
    cout << "Number of inv: " << inv << endl;
    return 0;
}
