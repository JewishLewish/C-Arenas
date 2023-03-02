#include "regional.c"
#include <time.h>

//Testing if the Regional Memory Management System Works
int test() {
    region *r = create_region(sizeof(int)*2);

    int *y = (int *)region_alloc(r, sizeof(int));
    *y = 42;

    int x;
    region_clone(&x, y, r);

    free_region(r);

    printf("%d\n", x);
}

//Benchmarking
#define NUM_VARS 1000000

int Cmallocandfree() {
    int **vars = malloc(sizeof(int*) * NUM_VARS);

    clock_t start = clock();

    for (int i = 0; i < NUM_VARS; i++) {
        vars[i] = malloc(sizeof(int));
        *vars[i] = i;
    }

    for (int i = 0; i < NUM_VARS; i++) {
        free(vars[i]);
    }

    free(vars);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_spent);

    return 0;
}

int Mymallocandfree() {
    region *r = create_region(sizeof(int*) * NUM_VARS + sizeof(int) * NUM_VARS);

    int **vars = (int **)region_alloc(r, sizeof(int*) * NUM_VARS);

    clock_t start = clock();

    for (int i = 0; i < NUM_VARS; i++) {
        vars[i] = (int *)region_alloc(r, sizeof(int));
        *vars[i] = i;
    }

    free_region(r);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_spent);

    return 0;
}


int main() {
    Cmallocandfree();
    Mymallocandfree();
    return 0;
}
