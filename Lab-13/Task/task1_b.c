#include <stdio.h>
#include <omp.h>

int main() {
    int r1, c1, r2, c2;

    // Input matrix dimensions
    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    // Check multiplication compatibility
    if (c1 != r2) {
        printf("Matrix multiplication not possible. Columns of A must equal rows of B.\n");
        return 0;
    }

    int A[100][100], B[100][100], C[100][100];

    // Input Matrix A
    printf("\nEnter elements of Matrix A:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Input Matrix B
    printf("\nEnter elements of Matrix B:\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // ------------------------------------
    //      SERIAL MULTIPLICATION
    // ------------------------------------
    double serial_start = omp_get_wtime();

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            int sum = 0;
            for (int k = 0; k < c1; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    double serial_end = omp_get_wtime();

    // ------------------------------------
    //     PARALLEL MULTIPLICATION (OMP)
    // ------------------------------------
    double parallel_start = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            int sum = 0;
            for (int k = 0; k < c1; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    double parallel_end = omp_get_wtime();

    // ------------------------------------
    //            OUTPUT RESULT
    // ------------------------------------
    printf("\nResultant Matrix (A x B):\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // ------------------------------------
    //           TIME COMPARISON
    // ------------------------------------
    printf("\n--- Time Used ---\n");
    printf("Serial multiplication time   = %f seconds\n", serial_end - serial_start);
    printf("Parallel multiplication time = %f seconds\n", parallel_end - parallel_start);

    return 0;
}

