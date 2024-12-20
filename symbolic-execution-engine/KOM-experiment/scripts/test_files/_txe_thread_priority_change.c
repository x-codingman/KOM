#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_THREAD *thread_ptr;
klee_make_symbolic_controllable(&*thread_ptr, sizeof(*thread_ptr), "*thread_ptr", true);
UINT new_priority;
klee_make_symbolic_controllable(&new_priority, sizeof(new_priority), "new_priority", true);
UINT *old_priority;
klee_make_symbolic_controllable(&*old_priority, sizeof(*old_priority), "*old_priority", true);
m__txe_thread_priority_change(*thread_ptr, new_priority, *old_priority);

return 0;
}