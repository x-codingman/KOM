#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_QUEUE *queue_ptr;
klee_make_symbolic_controllable(&*queue_ptr, sizeof(*queue_ptr), "*queue_ptr", true);
m__txe_queue_flush(*queue_ptr);

return 0;
}