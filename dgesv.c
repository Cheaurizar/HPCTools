#include "dgesv.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//NAME : TAMON OLIVIER
//NAME : CROS CLEMENT
// Solve A * X = B using Gauss-Jordan elimination
// A: n x n matrix 
// B: n x nrhs matrix 
int my_dgesv(int n, int nrhs, double *a, double *b) {
    int i, j, k, col;

    for (k = 0; k < n; k++) {
        //Partial pivoting: find row with largest value in column k
        int pivot = k;
        double maxval = fabs(a[k*n + k]);
        for (i = k+1; i < n; i++) {
            if (fabs(a[i*n + k]) > maxval) {
                maxval = fabs(a[i*n + k]);
                pivot = i;
            }
        }

        // If pivot is too small -> matrix is singular
        if (fabs(a[pivot*n + k]) < 1e-12) {
            fprintf(stderr, "Matrix is singular or nearly singular!\n");
            return -1;
        }

        // Swap rows in A
        if (pivot != k) {
            for (j = 0; j < n; j++) {
                double tmp = a[k*n + j];
                a[k*n + j] = a[pivot*n + j];
                a[pivot*n + j] = tmp;
            }
            // Swap rows in B
            for (col = 0; col < nrhs; col++) {
                double tmp = b[k*nrhs + col];
                b[k*nrhs + col] = b[pivot*nrhs + col];
                b[pivot*nrhs + col] = tmp;
            }
        }

        // Normalize pivot row so that pivot element becomes 1
        double pivotval = a[k*n + k];
        for (j = 0; j < n; j++) {
            a[k*n + j] /= pivotval;
        }
        for (col = 0; col < nrhs; col++) {
            b[k*nrhs + col] /= pivotval;
        }

        // Eliminate pivot column from all other rows
        for (i = 0; i < n; i++) {
            if (i == k) continue;
            double factor = a[i*n + k];
            if (fabs(factor) > 1e-15) {
                for (j = 0; j < n; j++) {
                    a[i*n + j] -= factor * a[k*n + j];
                }
                for (col = 0; col < nrhs; col++) {
                    b[i*nrhs + col] -= factor * b[k*nrhs + col];
                }
            }
        }
    }

    return 0; // success
}

