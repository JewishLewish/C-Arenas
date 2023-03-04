#include "regional.c"

//This function (if used malloc) would leak
//However, since we are using regional. We can put all the leaks in one container
void *leaking(region *r) {
    int *a = (int *)region_alloc(r, sizeof(int));
    *a = 42;
    int *b = (int *)region_alloc(r, sizeof(int));
    *b = 32;

    return a;
}

int main() {
    //Method 1, make your own region
    region *r = create_region(sizeof(int)*2);

    int *a = (int *)leaking(r);
    printf("%d\n",*a);
    free_region(r);

    //Method 2, using region_run which would output a value that is NOT in the region.
    //This can allow the variable you want to be controlled by you while all the leaks can be taken care of
    //EXPERIMENTAL
    int *b = (int *)region_run(sizeof(int)*2, leaking);
    printf("%d\n",*b);
    free(b);

    return 0;
}