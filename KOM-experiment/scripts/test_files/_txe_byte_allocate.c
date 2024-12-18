#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_BYTE_POOL *pool_ptr;
klee_make_symbolic_controllable(&*pool_ptr, sizeof(*pool_ptr), "*pool_ptr", true);
ULONG memory_size;
klee_make_symbolic_controllable(&memory_size, sizeof(memory_size), "memory_size", true);
ULONG wait_option;
klee_make_symbolic_controllable(&wait_option, sizeof(wait_option), "wait_option", true);
m__txe_byte_allocate(*pool_ptr, , memory_size, wait_option);

return 0;
}