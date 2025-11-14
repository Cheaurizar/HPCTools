Clément Cros, Olivier Tamon

gcc-8.4.0
| Matrix size | O0        | O2-novec  | O3-vec    | Ofast-vec | Ref |
| ----------- | --------- | --------- | --------- | --------- | --- |
| 1024x1024   | 6860 ms   | 1356 ms   | 875 ms    | 937 ms    |     |
| 2048x2048   | 54886 ms  | 16548 ms  | 12919 ms  | 15869 ms  |     |
| 4096x4096   | 437662 ms | 129050 ms | 117672 ms | 108054 ms |     |

gcc-10.1.0
| Matrix size | O0        | O2-novec  | O3-vec    | Ofast-vec | Ref |
| ----------- | --------- | --------- | --------- | --------- | --- |
| 1024x1024   |  7127 ms  | 1356 ms   | 871 ms    | 937 ms    |     |
| 2048x2048   | 54886 ms  | 16548 ms  | 12919 ms  | 15869 ms  |     |
| 4096x4096   | 435385 ms | 127736 ms | 110880 ms | 115617 ms |     |

gcc-11.4.0
| Matrix size | O0        | O2-novec  | O3-vec    | Ofast-vec | Ref |
| ----------- | --------- | --------- | --------- | --------- | --- |
| 1024x1024   | 6646 ms   | 1392 ms   | 941 ms    | 878 ms    |     |
| 2048x2048   | 54348 ms  | 15771 ms  | 13131 ms  | 13878 ms  |     |
| 4096x4096   | 422109 ms | 125705 ms | 109615 ms | 108625 ms |     |

In terms of program performance, we can observe a significant improvement between the O0 and O2 optimization levels for all matrix sizes and all GCC versions. This is expected since O0 is unoptimized. 
Then, between O2 and O3, we notice a smaller but still measurable improvement, explained by the vectorization of some loops. 
The performance gain could have been greater if we had managed to help the optimizer vectorize the main loop.

For Ofast, however, on small matrices (1024, 2048), we actually observe a slight increase in execution time, and for larger matrices, a very small reduction or stagnation.

Next, the program's performance does not seem to be strongly correlated with the compiler version. In some tests, we can see slight improvements or stagnation, but nothing significant.

Automatic vectorization succeeded on all loops except three:

The outermost loop that covers the whole function is not vectorizable because it contains the other two non-vectorizable loops.

The loop used to find the pivot in a row cannot be vectorized due to the condition if (fabs(a[i*n + k]) > maxval).

The main computation loop cannot be vectorized because of the condition if (i == k).

The third loop is the main reason why the performance difference between O3 and O2 is so small, as it is the most important loop in terms of computation.

Finally, regarding cache performance, we chose to traverse the matrix elements following the row-major principle to minimize cache misses except during the pivot search. 
However, this loop has a relatively low cost, especially for large matrices. For the main computation loop, the row-major order is respected to optimize performance.
