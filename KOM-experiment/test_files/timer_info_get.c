#include "tx_api.h"
#include "klee/klee.h"
#include "klee_help.h"

extern TX_THREAD *    _tx_thread_current_ptr;

UCHAR                   pool_start[9120];

int main()
{
    klee_make_symbolic_controllable(&_tx_thread_current_ptr, sizeof(_tx_thread_current_ptr), "_tx_thread_current_ptr", false);
    _txm_module_kernel_call_dispatcher=_txm_module_manager_kernel_dispatch;
    TX_TIMER * KLEE_TX_timer_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_timer_ptr, sizeof(KLEE_TX_timer_ptr), "KLEE_TX_timer_ptr", true);
    CHAR ** KLEE_TX_name;
    klee_make_symbolic_controllable(&KLEE_TX_name, sizeof(KLEE_TX_name), "KLEE_TX_name", true);
    UINT * KLEE_TX_active;
    klee_make_symbolic_controllable(&KLEE_TX_active, sizeof(KLEE_TX_active), "KLEE_TX_active", true);
    ULONG * KLEE_TX_remaining_ticks;
    klee_make_symbolic_controllable(&KLEE_TX_remaining_ticks, sizeof(KLEE_TX_remaining_ticks), "KLEE_TX_remaining_ticks", true);
    ULONG * KLEE_TX_reschedule_ticks;
    klee_make_symbolic_controllable(&KLEE_TX_reschedule_ticks, sizeof(KLEE_TX_reschedule_ticks), "KLEE_TX_reschedule_ticks", true);
    TX_TIMER ** KLEE_TX_next_timer;
    klee_make_symbolic_controllable(&KLEE_TX_next_timer, sizeof(KLEE_TX_next_timer), "KLEE_TX_next_timer", true);
    m_txe_timer_info_get(KLEE_TX_timer_ptr, KLEE_TX_name, KLEE_TX_active, KLEE_TX_remaining_ticks, KLEE_TX_reschedule_ticks, KLEE_TX_next_timer);
}
