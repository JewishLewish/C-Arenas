# C-Arenas
Region-based memory management for C


# Advantages

## Faster Array Memory Freeing
Code used: https://github.com/JewishLewish/C-Arenas/blob/main/benchmark_array_allocs.c
```C
Benchmark: Allocate 1,000,000 Times With Arrays
Sample count: 90
-----------------------------------------------
C's Method
 Time taken: 0.064878 seconds
Regional's Method
 Time taken: 0.006144 seconds
-----------------------------------------------
Regional Memory Manager is 10.56% faster
```
