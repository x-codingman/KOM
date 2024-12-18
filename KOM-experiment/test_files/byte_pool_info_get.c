#include "tx_api.h"
#include "klee/klee.h"
#include "klee_help.h"

extern TX_THREAD *    _tx_thread_current_ptr;

UCHAR                   pool_start[9120];

int main()
{
    klee_make_symbolic_controllable(&_tx_thread_current_ptr, sizeof(_tx_thread_current_ptr), "_tx_thread_current_ptr", false);
    _txm_module_kernel_call_dispatcher=_txm_module_manager_kernel_dispatch;
    TX_BYTE_POOL * KLEE_TX_pool_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_pool_ptr, sizeof(KLEE_TX_pool_ptr), "KLEE_TX_pool_ptr", true);
    CHAR ** KLEE_TX_name;
    klee_make_symbolic_controllable(&KLEE_TX_name, sizeof(KLEE_TX_name), "KLEE_TX_name", true);
    ULONG * KLEE_TX_available_bytes;
    klee_make_symbolic_controllable(&KLEE_TX_available_bytes, sizeof(KLEE_TX_available_bytes), "KLEE_TX_available_bytes", true);
    ULONG * KLEE_TX_fragments;
    klee_make_symbolic_controllable(&KLEE_TX_fragments, sizeof(KLEE_TX_fragments), "KLEE_TX_fragments", true);
    TX_THREAD ** KLEE_TX_first_suspended;
    klee_make_symbolic_controllable(&KLEE_TX_first_suspended, sizeof(KLEE_TX_first_suspended), "KLEE_TX_first_suspended", true);
    ULONG * KLEE_TX_suspended_count;
    klee_make_symbolic_controllable(&KLEE_TX_suspended_count, sizeof(KLEE_TX_suspended_count), "KLEE_TX_suspended_count", true);
    TX_BYTE_POOL ** KLEE_TX_next_pool;
    klee_make_symbolic_controllable(&KLEE_TX_next_pool, sizeof(KLEE_TX_next_pool), "KLEE_TX_next_pool", true);
    m_txe_byte_pool_info_get(KLEE_TX_pool_ptr, KLEE_TX_name, KLEE_TX_available_bytes, KLEE_TX_fragments, KLEE_TX_first_suspended, KLEE_TX_suspended_count, KLEE_TX_next_pool);
}
