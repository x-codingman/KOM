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
    CHAR * KLEE_TX_name_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_name_ptr, sizeof(KLEE_TX_name_ptr), "KLEE_TX_name_ptr", true);
    UINT KLEE_TX_inherit;
    klee_make_symbolic_controllable(&KLEE_TX_inherit, sizeof(KLEE_TX_inherit), "KLEE_TX_inherit", true);
    UINT KLEE_TX_mutex_control_block_size;
    klee_make_symbolic_controllable(&KLEE_TX_mutex_control_block_size, sizeof(KLEE_TX_mutex_control_block_size), "KLEE_TX_mutex_control_block_size", true);
    m_txe_mutex_create(KLEE_TX_mutex_ptr, KLEE_TX_name_ptr, KLEE_TX_inherit, KLEE_TX_mutex_control_block_size);
}
