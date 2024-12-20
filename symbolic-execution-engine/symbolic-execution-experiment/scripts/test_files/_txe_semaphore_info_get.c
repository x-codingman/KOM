#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_SEMAPHORE *semaphore_ptr;
klee_make_symbolic_controllable(&*semaphore_ptr, sizeof(*semaphore_ptr), "*semaphore_ptr", true);
CHAR **name;
klee_make_symbolic_controllable(&**name, sizeof(**name), "**name", true);
ULONG *current_value;
klee_make_symbolic_controllable(&*current_value, sizeof(*current_value), "*current_value", true);
TX_THREAD **first_suspended;
klee_make_symbolic_controllable(&**first_suspended, sizeof(**first_suspended), "**first_suspended", true);
ULONG *suspended_count;
klee_make_symbolic_controllable(&*suspended_count, sizeof(*suspended_count), "*suspended_count", true);
TX_SEMAPHORE **next_semaphore;
klee_make_symbolic_controllable(&**next_semaphore, sizeof(**next_semaphore), "**next_semaphore", true);
m__txe_semaphore_info_get(*semaphore_ptr, **name, *current_value, **first_suspended, *suspended_count, **next_semaphore);

return 0;
}