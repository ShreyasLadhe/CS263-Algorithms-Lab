#include <iostream>

using namespace std;

int indeqval(int test[], int left, int right) {
    if (left <= right) {
        int mid = left + (right - left) / 2;

        if (test[mid] == mid) {
            return mid; 
        } else if (test[mid] < mid) {
            return indeqval(test, mid + 1, right);
        } else {
            return indeqval(test, left, mid - 1);
        }
    }

    return -1;
}

int indeqval(int test[], int n) {
    return indeqval(test, 0, n - 1);
}

int main() {
    int test[] = {-10, -5, 0, 3, 7, 9, 12, 7};
    int n = sizeof(test) / sizeof(test[0]);

    int result = indeqval(test, n);

    if (result != -1) {
        cout << "There exists an index " << result << " such that " << result << " = test[" << result << "]." << endl;
    } else {
        cout << "No such index exists." << endl;
    }

    return 0;
}
