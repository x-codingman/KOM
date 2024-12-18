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
    CHAR ** KLEE_TX_name;
    klee_make_symbolic_controllable(&KLEE_TX_name, sizeof(KLEE_TX_name), "KLEE_TX_name", true);
    ULONG * KLEE_TX_available_blocks;
    klee_make_symbolic_controllable(&KLEE_TX_available_blocks, sizeof(KLEE_TX_available_blocks), "KLEE_TX_available_blocks", true);
    ULONG * KLEE_TX_total_blocks;
    klee_make_symbolic_controllable(&KLEE_TX_total_blocks, sizeof(KLEE_TX_total_blocks), "KLEE_TX_total_blocks", true);
    TX_THREAD ** KLEE_TX_first_suspended;
    klee_make_symbolic_controllable(&KLEE_TX_first_suspended, sizeof(KLEE_TX_first_suspended), "KLEE_TX_first_suspended", true);
    ULONG * KLEE_TX_suspended_count;
    klee_make_symbolic_controllable(&KLEE_TX_suspended_count, sizeof(KLEE_TX_suspended_count), "KLEE_TX_suspended_count", true);
    TX_BLOCK_POOL ** KLEE_TX_next_pool;
    klee_make_symbolic_controllable(&KLEE_TX_next_pool, sizeof(KLEE_TX_next_pool), "KLEE_TX_next_pool", true);
    m_txe_block_pool_info_get(KLEE_TX_pool_ptr, KLEE_TX_name, KLEE_TX_available_blocks, KLEE_TX_total_blocks, KLEE_TX_first_suspended, KLEE_TX_suspended_count, KLEE_TX_next_pool);
}
