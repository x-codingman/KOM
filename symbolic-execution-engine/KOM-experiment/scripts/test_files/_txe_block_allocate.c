#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_BLOCK_POOL *pool_ptr;
klee_make_symbolic_controllable(&*pool_ptr, sizeof(*pool_ptr), "*pool_ptr", true);
ULONG wait_option;
klee_make_symbolic_controllable(&wait_option, sizeof(wait_option), "wait_option", true);
m__txe_block_allocate(*pool_ptr, , wait_option);

return 0;
}