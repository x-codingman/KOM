#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_BLOCK_POOL *pool_ptr;
klee_make_symbolic_controllable(&*pool_ptr, sizeof(*pool_ptr), "*pool_ptr", true);
CHAR **name;
klee_make_symbolic_controllable(&**name, sizeof(**name), "**name", true);
ULONG *available_blocks;
klee_make_symbolic_controllable(&*available_blocks, sizeof(*available_blocks), "*available_blocks", true);
ULONG *total_blocks;
klee_make_symbolic_controllable(&*total_blocks, sizeof(*total_blocks), "*total_blocks", true);
TX_THREAD **first_suspended;
klee_make_symbolic_controllable(&**first_suspended, sizeof(**first_suspended), "**first_suspended", true);
ULONG *suspended_count;
klee_make_symbolic_controllable(&*suspended_count, sizeof(*suspended_count), "*suspended_count", true);
TX_BLOCK_POOL **next_pool;
klee_make_symbolic_controllable(&**next_pool, sizeof(**next_pool), "**next_pool", true);
m__txe_block_pool_info_get(*pool_ptr, **name, *available_blocks, *total_blocks, **first_suspended, *suspended_count, **next_pool);

return 0;
}