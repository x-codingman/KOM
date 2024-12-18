#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_BYTE_POOL *pool_ptr;
klee_make_symbolic_controllable(&*pool_ptr, sizeof(*pool_ptr), "*pool_ptr", true);
m__txe_byte_pool_prioritize(*pool_ptr);

return 0;
}