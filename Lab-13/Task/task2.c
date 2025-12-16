#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define TERMS 150

int main(void) {
    long double x;
    long double fact[TERMS];
    long double pwr[TERMS];
    long double s = 0.0L;

    printf("Exponential [PROMPT] Enter the value of x (0 to 100): ");
    if (scanf("%Lf", &x) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    // Parallel compute powers and factorials in separate sections
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // compute pwr[k] = x^k iteratively (more accurate + faster)
            pwr[0] = 1.0L;
            for (int k = 1; k < TERMS; ++k) {
                pwr[k] = pwr[k-1] * x;
            }
        }

        #pragma omp section
        {
            // compute factorials iteratively: fact[n] = n!
            fact[0] = 1.0L;
            for (int n = 1; n < TERMS; ++n) {
                fact[n] = fact[n-1] * (long double)n;
            }
        }
    } // implicit barrier: both sections done here

    // Compute the series sum in parallel with reduction to avoid races
    s = 0.0L;
    #pragma omp parallel for reduction(+:s)
    for (int t = 0; t < TERMS; ++t) {
        s += pwr[t] / fact[t];
    }

    printf("\nExponential [INFO] exp(%.6Lf) ≈ %.12Lf\n\n", x, s);
    return 0;
}

