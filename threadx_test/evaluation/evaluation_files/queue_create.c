#include "tx_api.h"
#include "klee/klee.h"
#include "klee_help.h"

extern TX_THREAD *    _tx_thread_current_ptr;

UCHAR                   pool_start[9120];

int main()
{
    klee_make_symbolic_controllable(&_tx_thread_current_ptr, sizeof(_tx_thread_current_ptr), "_tx_thread_current_ptr", false);
    _txm_module_kernel_call_dispatcher=_txm_module_manager_kernel_dispatch;
    TX_QUEUE * KLEE_TX_queue_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_queue_ptr, sizeof(KLEE_TX_queue_ptr), "KLEE_TX_queue_ptr", true);
    CHAR * KLEE_TX_name_ptr;
    klee_make_symbolic_controllable(&KLEE_TX_name_ptr, sizeof(KLEE_TX_name_ptr), "KLEE_TX_name_ptr", true);
    UINT KLEE_TX_message_size;
    klee_make_symbolic_controllable(&KLEE_TX_message_size, sizeof(KLEE_TX_message_size), "KLEE_TX_message_size", true);
    VOID * KLEE_TX_queue_start;
    klee_make_symbolic_controllable(&KLEE_TX_queue_start, sizeof(KLEE_TX_queue_start), "KLEE_TX_queue_start", true);
    ULONG KLEE_TX_queue_size;
    klee_make_symbolic_controllable(&KLEE_TX_queue_size, sizeof(KLEE_TX_queue_size), "KLEE_TX_queue_size", true);
    UINT KLEE_TX_queue_control_block_size;
    klee_make_symbolic_controllable(&KLEE_TX_queue_control_block_size, sizeof(KLEE_TX_queue_control_block_size), "KLEE_TX_queue_control_block_size", true);
    m_txe_queue_create(KLEE_TX_queue_ptr, KLEE_TX_name_ptr, KLEE_TX_message_size, KLEE_TX_queue_start, KLEE_TX_queue_size, KLEE_TX_queue_control_block_size);
}
