#include "regional.c"

int test() {
    region *r = create_region(sizeof(int)*2);

    int *y = (int *)region_alloc(r, sizeof(int));
    *y = 42;

    int x;
    region_clone(&x, y, r);

    free_region(r);

    printf("%d\n", x);
}

int main() {
    test();
    return 0;
}
