#include "regional.c"
#include <time.h>

//Testing if the Regional Memory Management System Works

//Benchmarking
#define NUM_VARS 1000000

double Cmallocandfree() {
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

    return time_spent;
}

double Mymallocandfree() {
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

    return time_spent;
}

double average(double (*func)(), int num_runs) {
    double sum = 0;
    int i;
    for (i = 0; i < num_runs; i++) {
        sum += (*func)();
    }
    return sum / num_runs;
}


int main() {
    double Inc;
    int Sample = 90;
    double Ctime = average(&Cmallocandfree, Sample);
    double Rtime = average(&Mymallocandfree, Sample);

    printf("Benchmark: Allocate 1,000,000 Times With Arrays\n");
    printf("-----------------------------------------------\n");
    printf("C's Method\n Time taken: %f seconds\n", Ctime);
    printf("Regional's Method\n Time taken: %f seconds\n", Rtime);
    printf("-----------------------------------------------\n");
    Inc = Ctime/Rtime;
    printf("Regional Memory Manager is %.2f%% faster", Inc);
    return 0;
}
