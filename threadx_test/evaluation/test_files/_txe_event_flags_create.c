#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_EVENT_FLAGS_GROUP *group_ptr;
klee_make_symbolic_controllable(&*group_ptr, sizeof(*group_ptr), "*group_ptr", true);
CHAR *name_ptr;
klee_make_symbolic_controllable(&*name_ptr, sizeof(*name_ptr), "*name_ptr", true);
UINT event_control_block_size;
klee_make_symbolic_controllable(&event_control_block_size, sizeof(event_control_block_size), "event_control_block_size", true);
m__txe_event_flags_create(*group_ptr, *name_ptr, event_control_block_size);

return 0;
}