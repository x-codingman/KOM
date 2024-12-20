#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_EVENT_FLAGS_GROUP *group_ptr;
klee_make_symbolic_controllable(&*group_ptr, sizeof(*group_ptr), "*group_ptr", true);
ULONG requested_flags;
klee_make_symbolic_controllable(&requested_flags, sizeof(requested_flags), "requested_flags", true);
UINT get_option;
klee_make_symbolic_controllable(&get_option, sizeof(get_option), "get_option", true);
ULONG *actual_flags_ptr;
klee_make_symbolic_controllable(&*actual_flags_ptr, sizeof(*actual_flags_ptr), "*actual_flags_ptr", true);
ULONG wait_option;
klee_make_symbolic_controllable(&wait_option, sizeof(wait_option), "wait_option", true);
m__txe_event_flags_get(*group_ptr, requested_flags, get_option, *actual_flags_ptr, wait_option);

return 0;
}