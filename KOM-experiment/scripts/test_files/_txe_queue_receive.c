#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_QUEUE *queue_ptr;
klee_make_symbolic_controllable(&*queue_ptr, sizeof(*queue_ptr), "*queue_ptr", true);
ULONG wait_option;
klee_make_symbolic_controllable(&wait_option, sizeof(wait_option), "wait_option", true);
m__txe_queue_receive(*queue_ptr, , wait_option);

return 0;
}