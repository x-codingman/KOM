#include "tx_api.h"
#include "klee/klee.h"
#include "klee_help.h"

extern TX_THREAD *    _tx_thread_current_ptr;

UCHAR                   pool_start[9120];

int main()
{
    klee_make_symbolic_controllable(&_tx_thread_current_ptr, sizeof(_tx_thread_current_ptr), "_tx_thread_current_ptr", false);
    _txm_module_kernel_call_dispatcher=_txm_module_manager_kernel_dispatch;
    TX_THREAD * KLEE_TX_thread_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_thread_ptr, sizeof(KLEE_TX_thread_ptr), "KLEE_TX_thread_ptr", true);
    CHAR * KLEE_TX_name_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_name_ptr, sizeof(KLEE_TX_name_ptr), "KLEE_TX_name_ptr", true);
    VOID (*entry_function)(ULONG entry_input);
    klee_make_symbolic_controllable(&entry_function, sizeof(entry_function), "entry_function", true);
    ULONG KLEE_TX_entry_input;
    klee_make_symbolic_controllable(&KLEE_TX_entry_input, sizeof(KLEE_TX_entry_input), "KLEE_TX_entry_input", true);
    VOID * KLEE_TX_stack_start;
    klee_make_symbolic_controllable(&KLEE_TX_stack_start, sizeof(KLEE_TX_stack_start), "KLEE_TX_stack_start", true);
    ULONG KLEE_TX_stack_size;
    klee_make_symbolic_controllable(&KLEE_TX_stack_size, sizeof(KLEE_TX_stack_size), "KLEE_TX_stack_size", true);
    UINT KLEE_TX_priority;
    klee_make_symbolic_controllable(&KLEE_TX_priority, sizeof(KLEE_TX_priority), "KLEE_TX_priority", true);
    UINT KLEE_TX_preempt_threshold;
    klee_make_symbolic_controllable(&KLEE_TX_preempt_threshold, sizeof(KLEE_TX_preempt_threshold), "KLEE_TX_preempt_threshold", true);
    ULONG KLEE_TX_time_slice;
    klee_make_symbolic_controllable(&KLEE_TX_time_slice, sizeof(KLEE_TX_time_slice), "KLEE_TX_time_slice", true);
    UINT KLEE_TX_auto_start;
    klee_make_symbolic_controllable(&KLEE_TX_auto_start, sizeof(KLEE_TX_auto_start), "KLEE_TX_auto_start", true);
    UINT KLEE_TX_thread_control_block_size;
    klee_make_symbolic_controllable(&KLEE_TX_thread_control_block_size, sizeof(KLEE_TX_thread_control_block_size), "KLEE_TX_thread_control_block_size", true);
    m_txe_thread_create(KLEE_TX_thread_ptr, KLEE_TX_name_ptr, entry_function, KLEE_TX_entry_input, KLEE_TX_stack_start, KLEE_TX_stack_size, KLEE_TX_priority, KLEE_TX_preempt_threshold, KLEE_TX_time_slice, KLEE_TX_auto_start, KLEE_TX_thread_control_block_size);
}
