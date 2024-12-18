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
    CHAR * KLEE_TX_name_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_name_ptr, sizeof(KLEE_TX_name_ptr), "KLEE_TX_name_ptr", true);
    ULONG KLEE_TX_initial_count;
    klee_make_symbolic_controllable(&KLEE_TX_initial_count, sizeof(KLEE_TX_initial_count), "KLEE_TX_initial_count", true);
    UINT KLEE_TX_semaphore_control_block_size;
    klee_make_symbolic_controllable(&KLEE_TX_semaphore_control_block_size, sizeof(KLEE_TX_semaphore_control_block_size), "KLEE_TX_semaphore_control_block_size", true);
    m_txe_semaphore_create(KLEE_TX_semaphore_ptr, KLEE_TX_name_ptr, KLEE_TX_initial_count, KLEE_TX_semaphore_control_block_size);
}
