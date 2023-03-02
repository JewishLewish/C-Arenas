#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct region {
  void *start;
  size_t size;
  void *current;
} region;

region *create_region(size_t size) {
  region *r = (region *)malloc(sizeof(region));
  r->start = malloc(size);
  r->size = size;
  r->current = r->start;
  return r;
}

void *region_alloc(region *r, size_t size) {
  if (r->current + size > r->start + r->size) {
    return NULL; // Out of memory
  }
  void *p = r->current;
  r->current += size;
  return p;
}

void free_region(region *r) {
    free(r->start);
    free(r);
}

void *get_from_region(region *r, size_t offset, size_t size) {
    if (offset < 0 || offset + size > r->size) {
        return NULL; // Out of memory
    }
    return (char *)r->start + offset;
}

void region_clone(void *_Dst, void *y, region *r) {
    size_t offset = (size_t)y - (size_t)r->start;
    memcpy(_Dst, (char*)r->start + offset, sizeof(int));
}