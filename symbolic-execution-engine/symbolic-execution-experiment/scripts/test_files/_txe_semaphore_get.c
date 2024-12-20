#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_SEMAPHORE *semaphore_ptr;
klee_make_symbolic_controllable(&*semaphore_ptr, sizeof(*semaphore_ptr), "*semaphore_ptr", true);
ULONG wait_option;
klee_make_symbolic_controllable(&wait_option, sizeof(wait_option), "wait_option", true);
m__txe_semaphore_get(*semaphore_ptr, wait_option);

return 0;
}