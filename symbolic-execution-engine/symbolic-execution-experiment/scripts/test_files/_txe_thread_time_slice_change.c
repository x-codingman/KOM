#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_THREAD *thread_ptr;
klee_make_symbolic_controllable(&*thread_ptr, sizeof(*thread_ptr), "*thread_ptr", true);
ULONG new_time_slice;
klee_make_symbolic_controllable(&new_time_slice, sizeof(new_time_slice), "new_time_slice", true);
ULONG *old_time_slice;
klee_make_symbolic_controllable(&*old_time_slice, sizeof(*old_time_slice), "*old_time_slice", true);
m__txe_thread_time_slice_change(*thread_ptr, new_time_slice, *old_time_slice);

return 0;
}