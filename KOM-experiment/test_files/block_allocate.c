#include "tx_api.h"
#include "klee/klee.h"
#include "klee_help.h"

extern TX_THREAD *    _tx_thread_current_ptr;

UCHAR                   pool_start[9120];

int main()
{
    klee_make_symbolic_controllable(&_tx_thread_current_ptr, sizeof(_tx_thread_current_ptr), "_tx_thread_current_ptr", false);
    _txm_module_kernel_call_dispatcher=_txm_module_manager_kernel_dispatch;
    TX_BLOCK_POOL * KLEE_TX_pool_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_pool_ptr, sizeof(KLEE_TX_pool_ptr), "KLEE_TX_pool_ptr", true);
    VOID ** KLEE_TX_block_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_block_ptr, sizeof(KLEE_TX_block_ptr), "KLEE_TX_block_ptr", true);
    ULONG KLEE_TX_wait_option;
    klee_make_symbolic_controllable(&KLEE_TX_wait_option, sizeof(KLEE_TX_wait_option), "KLEE_TX_wait_option", true);
    m_txe_block_allocate(KLEE_TX_pool_ptr, KLEE_TX_block_ptr, KLEE_TX_wait_option);
}
