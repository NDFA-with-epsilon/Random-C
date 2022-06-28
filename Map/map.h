#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define MAP_SIZE (int)10
typedef struct _pair
{   
    uintptr_t key;
    uint32_t val;
    struct _pair* next;
    int index;
}pair;

#endif
