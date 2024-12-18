#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_THREAD *thread_ptr;
klee_make_symbolic_controllable(&*thread_ptr, sizeof(*thread_ptr), "*thread_ptr", true);
CHAR *name_ptr;
klee_make_symbolic_controllable(&*name_ptr, sizeof(*name_ptr), "*name_ptr", true);
ULONG entry_input;
klee_make_symbolic_controllable(&entry_input, sizeof(entry_input), "entry_input", true);
ULONG stack_size;
klee_make_symbolic_controllable(&stack_size, sizeof(stack_size), "stack_size", true);
UINT priority;
klee_make_symbolic_controllable(&priority, sizeof(priority), "priority", true);
UINT preempt_threshold;
klee_make_symbolic_controllable(&preempt_threshold, sizeof(preempt_threshold), "preempt_threshold", true);
ULONG time_slice;
klee_make_symbolic_controllable(&time_slice, sizeof(time_slice), "time_slice", true);
UINT auto_start;
klee_make_symbolic_controllable(&auto_start, sizeof(auto_start), "auto_start", true);
UINT thread_control_block_size;
klee_make_symbolic_controllable(&thread_control_block_size, sizeof(thread_control_block_size), "thread_control_block_size", true);
m__txe_thread_create(*thread_ptr, *name_ptr, , entry_input, , stack_size, priority, preempt_threshold, time_slice, auto_start, thread_control_block_size);

return 0;
}