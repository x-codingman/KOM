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
    CHAR * KLEE_TX_name_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_name_ptr, sizeof(KLEE_TX_name_ptr), "KLEE_TX_name_ptr", true);
    VOID (*expiration_function)(ULONG input);
    klee_make_symbolic_controllable(&expiration_function, sizeof(expiration_function), "expiration_function", true);
    ULONG KLEE_TX_expiration_input;
    klee_make_symbolic_controllable(&KLEE_TX_expiration_input, sizeof(KLEE_TX_expiration_input), "KLEE_TX_expiration_input", true);
    ULONG KLEE_TX_initial_ticks;
    klee_make_symbolic_controllable(&KLEE_TX_initial_ticks, sizeof(KLEE_TX_initial_ticks), "KLEE_TX_initial_ticks", true);
    ULONG KLEE_TX_reschedule_ticks;
    klee_make_symbolic_controllable(&KLEE_TX_reschedule_ticks, sizeof(KLEE_TX_reschedule_ticks), "KLEE_TX_reschedule_ticks", true);
    UINT KLEE_TX_auto_activate;
    klee_make_symbolic_controllable(&KLEE_TX_auto_activate, sizeof(KLEE_TX_auto_activate), "KLEE_TX_auto_activate", true);
    UINT KLEE_TX_timer_control_block_size;
    klee_make_symbolic_controllable(&KLEE_TX_timer_control_block_size, sizeof(KLEE_TX_timer_control_block_size), "KLEE_TX_timer_control_block_size", true);
    m_txe_timer_create(KLEE_TX_timer_ptr, KLEE_TX_name_ptr, expiration_function, KLEE_TX_expiration_input, KLEE_TX_initial_ticks, KLEE_TX_reschedule_ticks, KLEE_TX_auto_activate, KLEE_TX_timer_control_block_size);
}
