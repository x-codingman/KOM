#include "tx_api.h"
#include "klee/klee.h"
#include "klee_help.h"

extern TX_THREAD *    _tx_thread_current_ptr;

UCHAR                   pool_start[9120];

int main()
{
    klee_make_symbolic_controllable(&_tx_thread_current_ptr, sizeof(_tx_thread_current_ptr), "_tx_thread_current_ptr", false);
    _txm_module_kernel_call_dispatcher=_txm_module_manager_kernel_dispatch;
    TX_MUTEX * KLEE_TX_mutex_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_mutex_ptr, sizeof(KLEE_TX_mutex_ptr), "KLEE_TX_mutex_ptr", true);
    CHAR ** KLEE_TX_name;
    klee_make_symbolic_controllable(&KLEE_TX_name, sizeof(KLEE_TX_name), "KLEE_TX_name", true);
    ULONG * KLEE_TX_count;
    klee_make_symbolic_controllable(&KLEE_TX_count, sizeof(KLEE_TX_count), "KLEE_TX_count", true);
    TX_THREAD ** KLEE_TX_owner;
    klee_make_symbolic_controllable(&KLEE_TX_owner, sizeof(KLEE_TX_owner), "KLEE_TX_owner", true);
    TX_THREAD ** KLEE_TX_first_suspended;
    klee_make_symbolic_controllable(&KLEE_TX_first_suspended, sizeof(KLEE_TX_first_suspended), "KLEE_TX_first_suspended", true);
    ULONG * KLEE_TX_suspended_count;
    klee_make_symbolic_controllable(&KLEE_TX_suspended_count, sizeof(KLEE_TX_suspended_count), "KLEE_TX_suspended_count", true);
    TX_MUTEX ** KLEE_TX_next_mutex;
    klee_make_symbolic_controllable(&KLEE_TX_next_mutex, sizeof(KLEE_TX_next_mutex), "KLEE_TX_next_mutex", true);
    m_txe_mutex_info_get(KLEE_TX_mutex_ptr, KLEE_TX_name, KLEE_TX_count, KLEE_TX_owner, KLEE_TX_first_suspended, KLEE_TX_suspended_count, KLEE_TX_next_mutex);
}
