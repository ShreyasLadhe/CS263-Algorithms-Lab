#include <stdio.h>
#include <stdlib.h>

void add(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int modsize = n / 2;

    int **A11 = (int **)malloc(modsize * sizeof(int *));
    int **A12 = (int **)malloc(modsize * sizeof(int *));
    int **A21 = (int **)malloc(modsize * sizeof(int *));
    int **A22 = (int **)malloc(modsize * sizeof(int *));
    int **B11 = (int **)malloc(modsize * sizeof(int *));
    int **B12 = (int **)malloc(modsize * sizeof(int *));
    int **B21 = (int **)malloc(modsize * sizeof(int *));
    int **B22 = (int **)malloc(modsize * sizeof(int *));
    int **C11 = (int **)malloc(modsize * sizeof(int *));
    int **C12 = (int **)malloc(modsize * sizeof(int *));
    int **C21 = (int **)malloc(modsize * sizeof(int *));
    int **C22 = (int **)malloc(modsize * sizeof(int *));
    int **P1 = (int **)malloc(modsize * sizeof(int *));
    int **P2 = (int **)malloc(modsize * sizeof(int *));
    int **P3 = (int **)malloc(modsize * sizeof(int *));
    int **P4 = (int **)malloc(modsize * sizeof(int *));
    int **P5 = (int **)malloc(modsize * sizeof(int *));
    int **P6 = (int **)malloc(modsize * sizeof(int *));
    int **P7 = (int **)malloc(modsize * sizeof(int *));
    int **temp1 = (int **)malloc(modsize * sizeof(int *));
    int **temp2 = (int **)malloc(modsize * sizeof(int *));

    for (int i = 0; i < modsize; i++) {
        A11[i] = (int *)malloc(modsize * sizeof(int));
        A12[i] = (int *)malloc(modsize * sizeof(int));
        A21[i] = (int *)malloc(modsize * sizeof(int));
        A22[i] = (int *)malloc(modsize * sizeof(int));
        B11[i] = (int *)malloc(modsize * sizeof(int));
        B12[i] = (int *)malloc(modsize * sizeof(int));
        B21[i] = (int *)malloc(modsize * sizeof(int));
        B22[i] = (int *)malloc(modsize * sizeof(int));
        C11[i] = (int *)malloc(modsize * sizeof(int));
        C12[i] = (int *)malloc(modsize * sizeof(int));
        C21[i] = (int *)malloc(modsize * sizeof(int));
        C22[i] = (int *)malloc(modsize * sizeof(int));
        P1[i] = (int *)malloc(modsize * sizeof(int));
        P2[i] = (int *)malloc(modsize * sizeof(int));
        P3[i] = (int *)malloc(modsize * sizeof(int));
        P4[i] = (int *)malloc(modsize * sizeof(int));
        P5[i] = (int *)malloc(modsize * sizeof(int));
        P6[i] = (int *)malloc(modsize * sizeof(int));
        P7[i] = (int *)malloc(modsize * sizeof(int));
        temp1[i] = (int *)malloc(modsize * sizeof(int));
        temp2[i] = (int *)malloc(modsize * sizeof(int));
    }

    for (int i = 0; i < modsize; i++) {
        for (int j = 0; j < modsize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + modsize];
            A21[i][j] = A[i + modsize][j];
            A22[i][j] = A[i + modsize][j + modsize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + modsize];
            B21[i][j] = B[i + modsize][j];
            B22[i][j] = B[i + modsize][j + modsize];
        }
    }

    add(A11, A22, temp1, modsize);
    add(B11, B22, temp2, modsize);
    strassen(temp1, temp2, P1, modsize);

    add(A21, A22, temp1, modsize);
    strassen(temp1, B11, P2, modsize);
    
    subtract(B12, B22, temp1, modsize);
    strassen(A11, temp1, P3, modsize);

    subtract(B21, B11, temp1, modsize);
    strassen(A22, temp1, P4, modsize);

    add(A11, A12, temp1, modsize);
    strassen(temp1, B22, P5, modsize);

    subtract(A21, A11, temp1, modsize);
    add(B11, B12, temp2, modsize);
    strassen(temp1, temp2, P6, modsize);

    subtract(A12, A22, temp1, modsize);
    add(B21, B22, temp2, modsize);
    strassen(temp1, temp2, P7, modsize);

    add(P1, P4, temp1, modsize);
    subtract(temp1, P5, temp2, modsize);
    add(temp2, P7, C11, modsize);

    add(P3, P5, C12, modsize);

    add(P2, P4, C21, modsize);

    add(P1, P3, temp1, modsize);
    subtract(temp1, P2, temp2, modsize);
    add(temp2, P6, C22, modsize);

    for (int i = 0; i < modsize; i++) {
        for (int j = 0; j < modsize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + modsize] = C12[i][j];
            C[i + modsize][j] = C21[i][j];
            C[i + modsize][j + modsize] = C22[i][j];
        }
    }
}

int main() {
    int n;
    printf("Enter the size of matrices: ");
    scanf("%d", &n);

    int **A = (int **)malloc(n * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        B[i] = (int *)malloc(n * sizeof(int));
        C[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter matrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    strassen(A, B, C, n);

    printf("Result matrix C:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}