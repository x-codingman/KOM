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
    UINT KLEE_TX_new_threshold;
    klee_make_symbolic_controllable(&KLEE_TX_new_threshold, sizeof(KLEE_TX_new_threshold), "KLEE_TX_new_threshold", true);
    UINT * KLEE_TX_old_threshold;
    klee_make_symbolic_controllable(&KLEE_TX_old_threshold, sizeof(KLEE_TX_old_threshold), "KLEE_TX_old_threshold", true);
    m_txe_thread_preemption_change(KLEE_TX_thread_ptr, KLEE_TX_new_threshold, KLEE_TX_old_threshold);
}
