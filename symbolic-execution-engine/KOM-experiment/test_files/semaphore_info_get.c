#include "tx_api.h"
#include "klee/klee.h"
#include "klee_help.h"

extern TX_THREAD *    _tx_thread_current_ptr;

UCHAR                   pool_start[9120];

int main()
{
    klee_make_symbolic_controllable(&_tx_thread_current_ptr, sizeof(_tx_thread_current_ptr), "_tx_thread_current_ptr", false);
    _txm_module_kernel_call_dispatcher=_txm_module_manager_kernel_dispatch;
    TX_SEMAPHORE * KLEE_TX_semaphore_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_semaphore_ptr, sizeof(KLEE_TX_semaphore_ptr), "KLEE_TX_semaphore_ptr", true);
    CHAR ** KLEE_TX_name;
    klee_make_symbolic_controllable(&KLEE_TX_name, sizeof(KLEE_TX_name), "KLEE_TX_name", true);
    ULONG * KLEE_TX_current_value;
    klee_make_symbolic_controllable(&KLEE_TX_current_value, sizeof(KLEE_TX_current_value), "KLEE_TX_current_value", true);
    TX_THREAD ** KLEE_TX_first_suspended;
    klee_make_symbolic_controllable(&KLEE_TX_first_suspended, sizeof(KLEE_TX_first_suspended), "KLEE_TX_first_suspended", true);
    ULONG * KLEE_TX_suspended_count;
    klee_make_symbolic_controllable(&KLEE_TX_suspended_count, sizeof(KLEE_TX_suspended_count), "KLEE_TX_suspended_count", true);
    TX_SEMAPHORE ** KLEE_TX_next_semaphore;
    klee_make_symbolic_controllable(&KLEE_TX_next_semaphore, sizeof(KLEE_TX_next_semaphore), "KLEE_TX_next_semaphore", true);
    m_txe_semaphore_info_get(KLEE_TX_semaphore_ptr, KLEE_TX_name, KLEE_TX_current_value, KLEE_TX_first_suspended, KLEE_TX_suspended_count, KLEE_TX_next_semaphore);
}
