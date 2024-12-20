#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_QUEUE *queue_ptr;
klee_make_symbolic_controllable(&*queue_ptr, sizeof(*queue_ptr), "*queue_ptr", true);
CHAR *name_ptr;
klee_make_symbolic_controllable(&*name_ptr, sizeof(*name_ptr), "*name_ptr", true);
UINT message_size;
klee_make_symbolic_controllable(&message_size, sizeof(message_size), "message_size", true);
ULONG queue_size;
klee_make_symbolic_controllable(&queue_size, sizeof(queue_size), "queue_size", true);
UINT queue_control_block_size;
klee_make_symbolic_controllable(&queue_control_block_size, sizeof(queue_control_block_size), "queue_control_block_size", true);
m__txe_queue_create(*queue_ptr, *name_ptr, message_size, , queue_size, queue_control_block_size);

return 0;
}