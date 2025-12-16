#include <stdio.h>
#include <omp.h>

int main() {
    int rows, cols;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    int A[100][100], B[100][100], C[100][100];

    // Input Matrix A
    printf("\nEnter elements of Matrix A:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Input Matrix B
    printf("\nEnter elements of Matrix B:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // ------------------------------------
    //           SERIAL ADDITION
    // ------------------------------------
    double serial_start = omp_get_wtime();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    double serial_end = omp_get_wtime();

    // ------------------------------------
    //          PARALLEL ADDITION
    // ------------------------------------
    double parallel_start = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    double parallel_end = omp_get_wtime();

    // ------------------------------------
    //            OUTPUT RESULT
    // ------------------------------------
    printf("\nResultant Matrix (A + B):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // ------------------------------------
    //         TIME OUTPUT
    // ------------------------------------
    printf("\n--- Time Comparison ---\n");
    printf("Serial execution time   = %f seconds\n", serial_end - serial_start);
    printf("Parallel execution time = %f seconds\n", parallel_end - parallel_start);

    return 0;
}

