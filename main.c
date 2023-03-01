#include "regional.c"

int test() {
    region *r = create_region(sizeof(int)*2);

    int *y = (int *)region_alloc(r, sizeof(int));
    *y = 42;

    int x;
    memcpy(&x, get_from_region(r, (size_t)y - (size_t)r->start, sizeof(int)), sizeof(int));

    free_region(r);
}

int main() {
    region *r = create_region(sizeof(int));

    int *p = (int *)region_alloc(r, sizeof(int));
    int q = *p;
    q = 20;
    
    printf("%d\n",q);

    free_region(r);
    return 0;
}
