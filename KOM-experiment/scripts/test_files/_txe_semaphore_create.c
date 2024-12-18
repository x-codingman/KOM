#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_SEMAPHORE *semaphore_ptr;
klee_make_symbolic_controllable(&*semaphore_ptr, sizeof(*semaphore_ptr), "*semaphore_ptr", true);
CHAR *name_ptr;
klee_make_symbolic_controllable(&*name_ptr, sizeof(*name_ptr), "*name_ptr", true);
ULONG initial_count;
klee_make_symbolic_controllable(&initial_count, sizeof(initial_count), "initial_count", true);
UINT semaphore_control_block_size;
klee_make_symbolic_controllable(&semaphore_control_block_size, sizeof(semaphore_control_block_size), "semaphore_control_block_size", true);
m__txe_semaphore_create(*semaphore_ptr, *name_ptr, initial_count, semaphore_control_block_size);

return 0;
}