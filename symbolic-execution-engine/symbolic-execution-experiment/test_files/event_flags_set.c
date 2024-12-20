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
    ULONG KLEE_TX_flags_to_set;
    klee_make_symbolic_controllable(&KLEE_TX_flags_to_set, sizeof(KLEE_TX_flags_to_set), "KLEE_TX_flags_to_set", true);
    UINT KLEE_TX_set_option;
    klee_make_symbolic_controllable(&KLEE_TX_set_option, sizeof(KLEE_TX_set_option), "KLEE_TX_set_option", true);
    m_txe_event_flags_set(KLEE_TX_group_ptr, KLEE_TX_flags_to_set, KLEE_TX_set_option);
}
