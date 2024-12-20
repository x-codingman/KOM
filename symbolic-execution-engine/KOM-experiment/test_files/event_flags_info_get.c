#include "tx_api.h"
#include "klee/klee.h"
#include "klee_help.h"

extern TX_THREAD *    _tx_thread_current_ptr;

UCHAR                   pool_start[9120];

int main()
{
    klee_make_symbolic_controllable(&_tx_thread_current_ptr, sizeof(_tx_thread_current_ptr), "_tx_thread_current_ptr", false);
    _txm_module_kernel_call_dispatcher=_txm_module_manager_kernel_dispatch;
    TX_EVENT_FLAGS_GROUP * KLEE_TX_group_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_group_ptr, sizeof(KLEE_TX_group_ptr), "KLEE_TX_group_ptr", true);
    CHAR ** KLEE_TX_name;
    klee_make_symbolic_controllable(&KLEE_TX_name, sizeof(KLEE_TX_name), "KLEE_TX_name", true);
    ULONG * KLEE_TX_current_flags;
    klee_make_symbolic_controllable(&KLEE_TX_current_flags, sizeof(KLEE_TX_current_flags), "KLEE_TX_current_flags", true);
    TX_THREAD ** KLEE_TX_first_suspended;
    klee_make_symbolic_controllable(&KLEE_TX_first_suspended, sizeof(KLEE_TX_first_suspended), "KLEE_TX_first_suspended", true);
    ULONG * KLEE_TX_suspended_count;
    klee_make_symbolic_controllable(&KLEE_TX_suspended_count, sizeof(KLEE_TX_suspended_count), "KLEE_TX_suspended_count", true);
    TX_EVENT_FLAGS_GROUP ** KLEE_TX_next_group;
    klee_make_symbolic_controllable(&KLEE_TX_next_group, sizeof(KLEE_TX_next_group), "KLEE_TX_next_group", true);
    m_txe_event_flags_info_get(KLEE_TX_group_ptr, KLEE_TX_name, KLEE_TX_current_flags, KLEE_TX_first_suspended, KLEE_TX_suspended_count, KLEE_TX_next_group);
}
