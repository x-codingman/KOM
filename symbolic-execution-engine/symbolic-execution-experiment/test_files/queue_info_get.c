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
    CHAR ** KLEE_TX_name;
    klee_make_symbolic_controllable(&KLEE_TX_name, sizeof(KLEE_TX_name), "KLEE_TX_name", true);
    ULONG * KLEE_TX_enqueued;
    klee_make_symbolic_controllable(&KLEE_TX_enqueued, sizeof(KLEE_TX_enqueued), "KLEE_TX_enqueued", true);
    ULONG * KLEE_TX_available_storage;
    klee_make_symbolic_controllable(&KLEE_TX_available_storage, sizeof(KLEE_TX_available_storage), "KLEE_TX_available_storage", true);
    TX_THREAD ** KLEE_TX_first_suspended;
    klee_make_symbolic_controllable(&KLEE_TX_first_suspended, sizeof(KLEE_TX_first_suspended), "KLEE_TX_first_suspended", true);
    ULONG * KLEE_TX_suspended_count;
    klee_make_symbolic_controllable(&KLEE_TX_suspended_count, sizeof(KLEE_TX_suspended_count), "KLEE_TX_suspended_count", true);
    TX_QUEUE ** KLEE_TX_next_queue;
    klee_make_symbolic_controllable(&KLEE_TX_next_queue, sizeof(KLEE_TX_next_queue), "KLEE_TX_next_queue", true);
    m_txe_queue_info_get(KLEE_TX_queue_ptr, KLEE_TX_name, KLEE_TX_enqueued, KLEE_TX_available_storage, KLEE_TX_first_suspended, KLEE_TX_suspended_count, KLEE_TX_next_queue);
}
