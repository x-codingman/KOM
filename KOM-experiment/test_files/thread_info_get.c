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
    CHAR ** KLEE_TX_name;
    klee_make_symbolic_controllable(&KLEE_TX_name, sizeof(KLEE_TX_name), "KLEE_TX_name", true);
    UINT * KLEE_TX_state;
    klee_make_symbolic_controllable(&KLEE_TX_state, sizeof(KLEE_TX_state), "KLEE_TX_state", true);
    ULONG * KLEE_TX_run_count;
    klee_make_symbolic_controllable(&KLEE_TX_run_count, sizeof(KLEE_TX_run_count), "KLEE_TX_run_count", true);
    UINT * KLEE_TX_priority;
    klee_make_symbolic_controllable(&KLEE_TX_priority, sizeof(KLEE_TX_priority), "KLEE_TX_priority", true);
    UINT * KLEE_TX_preemption_threshold;
    klee_make_symbolic_controllable(&KLEE_TX_preemption_threshold, sizeof(KLEE_TX_preemption_threshold), "KLEE_TX_preemption_threshold", true);
    ULONG * KLEE_TX_time_slice;
    klee_make_symbolic_controllable(&KLEE_TX_time_slice, sizeof(KLEE_TX_time_slice), "KLEE_TX_time_slice", true);
    TX_THREAD ** KLEE_TX_next_thread;
    klee_make_symbolic_controllable(&KLEE_TX_next_thread, sizeof(KLEE_TX_next_thread), "KLEE_TX_next_thread", true);
    TX_THREAD ** KLEE_TX_next_suspended_thread;
    klee_make_symbolic_controllable(&KLEE_TX_next_suspended_thread, sizeof(KLEE_TX_next_suspended_thread), "KLEE_TX_next_suspended_thread", true);
    m_txe_thread_info_get(KLEE_TX_thread_ptr, KLEE_TX_name, KLEE_TX_state, KLEE_TX_run_count, KLEE_TX_priority, KLEE_TX_preemption_threshold, KLEE_TX_time_slice, KLEE_TX_next_thread, KLEE_TX_next_suspended_thread);
}
