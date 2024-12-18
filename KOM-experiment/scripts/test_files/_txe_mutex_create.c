#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_MUTEX *mutex_ptr;
klee_make_symbolic_controllable(&*mutex_ptr, sizeof(*mutex_ptr), "*mutex_ptr", true);
CHAR *name_ptr;
klee_make_symbolic_controllable(&*name_ptr, sizeof(*name_ptr), "*name_ptr", true);
UINT inherit;
klee_make_symbolic_controllable(&inherit, sizeof(inherit), "inherit", true);
UINT mutex_control_block_size;
klee_make_symbolic_controllable(&mutex_control_block_size, sizeof(mutex_control_block_size), "mutex_control_block_size", true);
m__txe_mutex_create(*mutex_ptr, *name_ptr, inherit, mutex_control_block_size);

return 0;
}