#include "stdio.h"
#include "stdint.h"

#include "test_api.h"
#include "klee/klee.h"

void test_api_1(test_structure_1_t * test_ptr_1);

int main(){
    test_structure_1_t *  test_ptr_1;
    klee_make_symbolic_controllable(&test_ptr_1, sizeof(test_ptr_1), "test_ptr_1", 1);
    test_api_1(test_ptr_1);
}

// void test_api_1(test_structure_1_t * test_ptr_1){
//     if(test_ptr_1 > ATTACK_CAPABILITY_REGION_END || test_ptr_1 < ATTACK_CAPABILITY_REGION_START){
//         if(test_ptr_1->a == 0){
//             *(test_ptr_1->p)=0;
//         }
//     }
// }

void test_api_1(test_structure_1_t * test_ptr_1){
    if(test_ptr_1 > ATTACK_CAPABILITY_REGION_END || test_ptr_1 < ATTACK_CAPABILITY_REGION_START){
        if(test_ptr_1->a == 0){
            test_ptr_1->p->p->a=0;
        }
    }
}