#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_SEMAPHORE *semaphore_ptr;
klee_make_symbolic_controllable(&*semaphore_ptr, sizeof(*semaphore_ptr), "*semaphore_ptr", true);
m__txe_semaphore_delete(*semaphore_ptr);

return 0;
}