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
    VOID (*queue_send_notify)(TX_QUEUE *notify_queue_ptr);
    klee_make_symbolic_controllable(&queue_send_notify, sizeof(queue_send_notify), "queue_send_notify", true);
    m_txe_queue_send_notify(KLEE_TX_queue_ptr, queue_send_notify);
}
