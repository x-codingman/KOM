#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_THREAD *thread_ptr;
klee_make_symbolic_controllable(&*thread_ptr, sizeof(*thread_ptr), "*thread_ptr", true);
UINT new_threshold;
klee_make_symbolic_controllable(&new_threshold, sizeof(new_threshold), "new_threshold", true);
UINT *old_threshold;
klee_make_symbolic_controllable(&*old_threshold, sizeof(*old_threshold), "*old_threshold", true);
m__txe_thread_preemption_change(*thread_ptr, new_threshold, *old_threshold);

return 0;
}