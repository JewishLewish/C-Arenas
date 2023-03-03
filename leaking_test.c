#include "regional.c"

void *leaking(region *r) {
    int *a = (int *)region_alloc(r, sizeof(int));
    *a = 42;
    int *b = (int *)region_alloc(r, sizeof(int));
    *b = 32;

    return a;
}

int main() {
    region *r = create_region(sizeof(int)*2);

    int *a = (int *)leaking(r);
    printf("%d\n",*a);
    free_region(r);

    int *b = (int *)region_run(sizeof(int)*2, leaking);
    printf("%d\n",*b);

    return 0;
}