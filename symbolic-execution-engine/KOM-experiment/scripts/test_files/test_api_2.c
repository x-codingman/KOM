#include "stdio.h"
#include "stdint.h"

#include "test_api.h"
#include "klee/klee.h"
void test_api_2(test_structure_2_t * test_ptr_2,int b, int c);
int main(){
    test_structure_2_t *  test_ptr_2;
    int test_b,test_c;
    klee_make_symbolic_controllable(&test_ptr_2, sizeof(test_ptr_2), "test_ptr_2", 1);
    klee_make_symbolic_controllable(&test_b, sizeof(test_b), "test_b", 1);
    klee_make_symbolic_controllable(&test_c, sizeof(test_c), "test_c", 1);
    test_api_2(test_ptr_2,test_b,test_c);
}

void test_api_2(test_structure_2_t * test_ptr_2, int b, int c){
    if(test_ptr_2 > ATTACK_CAPABILITY_REGION_END || test_ptr_2 < ATTACK_CAPABILITY_REGION_START){
        test_ptr_2->b = b;
        test_ptr_2->c = c;
    }
}