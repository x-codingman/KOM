#include "stdio.h"

#define ATTACK_CAPABILITY_REGION_START 0x80000000
#define ATTACK_CAPABILITY_REGION_END 0x8fffffff

// typedef struct test_structure_1{
//     int a;
//     int *p;
// } test_structure_1_t;

typedef struct test_structure_1{
    int a;
    struct test_structure_1 *p;
} test_structure_1_t;


typedef struct test_structure_2{
    int a;
    int b;
    int c;
    int *p;
} test_structure_2_t;


